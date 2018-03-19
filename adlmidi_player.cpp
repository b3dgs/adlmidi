#include "adlmidi_player.h"

#ifdef _WIN32
#include <crtdefs.h>
#endif

#include <cstdlib>
#include <ctime>

#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdarg.h>
#include <cstdio>
#include <vector> // vector
#include <deque>  // deque
#include <cmath>  // exp, log, ceil

#include <assert.h>

#if defined(_WIN32) || defined(__DJGPP__)
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned Uint32;
#endif

#include <deque>
#include <algorithm>
#include <portaudio.h>

#include <signal.h>

#include "adlmidi.h"
#include "adlmidi.hpp"

#ifndef __DJGPP__

static const unsigned long PCM_RATE = 48000;
static const unsigned MaxSamplesAtTime = 512; // 512=dbopl limitation
#else // DJGPP
static const unsigned MaxCards = 1;
static const unsigned OPLBase = 0x388;
#endif
static bool ReverbIsOn = true;

static ADL_MIDIPlayer *myDevice;
static PaStream *stream;
static int initiated = 0;
static int played = 0;
static int lastVolume = 100;
static int bank = 0;

#ifndef __DJGPP__
struct Reverb /* This reverb implementation is based on Freeverb impl. in Sox */
{
    float feedback, hf_damping, gain;

    struct FilterArray
    {
        struct Filter
        {
            std::vector<float> Ptr;
            size_t pos;
            float Store;

            void Create(size_t size)
            {
                Ptr.resize(size);
                pos = 0;
                Store = 0.f;
            }

            float Update(float a, float b)
            {
                Ptr[pos] = a;
                if (!pos)
                    pos = Ptr.size() - 1;
                else
                    --pos;
                return b;
            }

            float ProcessComb(float input, const float feedback, const float hf_damping)
            {
                Store = Ptr[pos] + (Store - Ptr[pos]) * hf_damping;
                return Update(input + feedback * Store, Ptr[pos]);
            }

            float ProcessAllPass(float input)
            {
                return Update(input + Ptr[pos] * .5f, Ptr[pos] - input);
            }
        } comb[8], allpass[4];

        void Create(double rate, double scale, double offset)
        {
            /* Filter delay lengths in samples (44100Hz sample-rate) */
            static const int comb_lengths[8] = { 1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617 };
            static const int allpass_lengths[4] = { 225, 341, 441, 556 };
            double r = rate * (1 / 44100.0); // Compensate for actual sample-rate
            const int stereo_adjust = 12;

            for (size_t i = 0; i < 8; ++i, offset = -offset)
                comb[i].Create(scale * r * (comb_lengths[i] + stereo_adjust * offset) + .5);

            for (size_t i = 0; i < 4; ++i, offset = -offset)
                allpass[i].Create(r * (allpass_lengths[i] + stereo_adjust * offset) + .5);
        }

        void Process(size_t length,
                     const std::deque<float> &input,
                     std::vector<float> &output,
                     const float feedback,
                     const float hf_damping,
                     const float gain)
        {
            for (size_t a = 0; a < length; ++a)
            {
                float out = 0, in = input[a];

                for (size_t i = 8; i-- > 0;)
                    out += comb[i].ProcessComb(in, feedback, hf_damping);

                for (size_t i = 4; i-- > 0;)
                    out += allpass[i].ProcessAllPass(out);

                output[a] = out * gain;
            }
        }
    } chan[2];

    std::vector<float> out[2];
    std::deque<float> input_fifo;

    void Create(double sample_rate_Hz, double wet_gain_dB, double room_scale, double reverberance, double fhf_damping, /* 0..1 */
                double pre_delay_s, double stereo_depth, size_t buffer_size)
    {
        size_t delay = pre_delay_s * sample_rate_Hz + .5;
        double scale = room_scale * .9 + .1;
        double depth = stereo_depth;
        double a = -1 / std::log(1 - .3); // Set minimum feedback
        double b = 100 / (std::log(1 - .98) * a + 1); // Set maximum feedback
        feedback = 1 - std::exp((reverberance * 100.0 - b) / (a * b));
        hf_damping = fhf_damping * .3 + .2;
        gain = std::exp(wet_gain_dB * (std::log(10.0) * 0.05)) * .015;
        input_fifo.insert(input_fifo.end(), delay, 0.f);

        for (size_t i = 0; i <= std::ceil(depth); ++i)
        {
            chan[i].Create(sample_rate_Hz, scale, i * depth);
            out[i].resize(buffer_size);
        }
    }
    void Process(size_t length)
    {
        for (size_t i = 0; i < 2; ++i)
            if (!out[i].empty())
                chan[i].Process(length, input_fifo, out[i], feedback, hf_damping, gain);

        input_fifo.erase(input_fifo.begin(), input_fifo.begin() + length);
    }
};
static struct MyReverbData
{
    bool wetonly;
    Reverb chan[2];

    MyReverbData() :
                    wetonly(false)
    {
        for (size_t i = 0; i < 2; ++i)
            chan[i].Create(PCM_RATE, 6.0,   // wet_gain_dB  (-10..10)
                           .7,              // room_scale   (0..1)
                           .6,              // reverberance (0..1)
                           .8,              // hf_damping   (0..1)
                           .000,            // pre_delay_s  (0.. 0.5)
                           1,               // stereo_depth (0..1)
                           MaxSamplesAtTime);
    }
} reverb_data;

struct FourChars
{
    char ret[4];

    FourChars(const char *s)
    {
        for (unsigned c = 0; c < 4; ++c)
            ret[c] = s[c];
    }
    FourChars(unsigned w) // Little-endian
    {
        for (unsigned c = 0; c < 4; ++c)
            ret[c] = (w >> (c * 8)) & 0xFF;
    }
};

static int callback(const void *input,
                    void *output,
                    unsigned long sampleCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    short samples[1024];

    size_t got = (size_t) adl_play(myDevice, 1024, samples);
    unsigned long count = got / 2;

    if (got <= 0)
    {
        return 0;
    }

    // Attempt to filter out the DC component. However, avoid doing
    // sudden changes to the offset, for it can be audible.
    double average[2] = { 0, 0 };
    for (unsigned w = 0; w < 2; ++w)
        for (unsigned long p = 0; p < count; ++p)
            average[w] += samples[p * 2 + w];

    static float prev_avg_flt[2] = { 0, 0 };
    float average_flt[2] = { prev_avg_flt[0] = (float) ((double(prev_avg_flt[0]) + average[0] * 0.04 / double(count))
                                                        / 1.04),
                             prev_avg_flt[1] = (float) ((double(prev_avg_flt[1]) + average[1] * 0.04 / double(count))
                                                        / 1.04) };

    const size_t pos = 0;

    short int* buffer = (short int*) output;
    float vol = lastVolume / 100.0f;

    if (ReverbIsOn)
    {
        // Convert input to float format
        std::vector<float> dry[2];
        for (unsigned w = 0; w < 2; ++w)
        {
            dry[w].resize(count);
            float a = average_flt[w];
            for (unsigned long p = 0; p < count; ++p)
            {
                int s = samples[p * 2 + w];
                dry[w][p] = (s - a) * double(0.3 / 32768.0);
            }
            // ^  Note: ftree-vectorize causes an error in this loop on g++-4.4.5
            reverb_data.chan[w].input_fifo.insert(reverb_data.chan[w].input_fifo.end(), dry[w].begin(), dry[w].end());
        }
        // Reverbify it
        for (unsigned w = 0; w < 2; ++w)
            reverb_data.chan[w].Process(count);

        // Convert to signed 16-bit int format and put to playback queue
        for (unsigned long p = 0; p < count; ++p)
            for (unsigned w = 0; w < 2; ++w)
            {
                float out = ((1 - reverb_data.wetonly) * dry[w][p]
                             + .5 * (reverb_data.chan[0].out[w][p] + reverb_data.chan[1].out[w][p]))
                            * 32768.0f
                            + average_flt[w];
                buffer[pos + p * 2 + w] = (out < -32768.f ? -32768 : out > 32767.f ? 32767 : out) * vol;
            }
    }
    else
    {
        for (unsigned long p = 0; p < count; ++p)
            for (unsigned w = 0; w < 2; ++w)
                buffer[pos + p * 2 + w] = samples[p * 2 + w] * vol;
    }

    return 0;
}
#endif /* not DJGPP */

void adlPlay(const char *file)
{
    if (initiated)
    {
        adlStop();
    }
    initiated = 1;

#ifndef __DJGPP__
    std::srand((unsigned int) std::time(0));
#endif

#ifndef __DJGPP__
    myDevice = adl_init(PCM_RATE);
#else
    myDevice = adl_init(48000);
#endif

    int loopEnabled = 1;
    // adl_setPercMode(myDevice, 1);
    // adl_setHVibrato(myDevice, 1);
    // adl_setHTremolo(myDevice, 1);
    // adl_setScaleModulators(myDevice, 1);
    ReverbIsOn = false;

    if (adl_setBank(myDevice, bank) < 0)
    {
        // Error
    }

    // Open external bank file (WOPL format is supported)
    // adl_openBankFile(myDevice, argv[2])

    adl_setLoopEnabled(myDevice, loopEnabled);

    // adl_setNumChips(myDevice, (int)numChips) < 0;
    // adl_setNumFourOpsChn(myDevice, (int)numFourOps) < 0;

    if (adl_openFile(myDevice, file) == 0
        && Pa_Initialize() == paNoError
        && Pa_OpenDefaultStream(&stream, 0, 2, paInt16, PCM_RATE, MaxSamplesAtTime, callback, 0) == paNoError
        && Pa_StartStream(stream) == paNoError)
    {
        played = 1;
    }
    else
    {
        adlStop();
    }
}

void adlSetBank(int bankId)
{
    bank = bankId;
}

void adlSetVolume(int volume)
{
    lastVolume = volume;
    if (lastVolume < 0)
    {
        lastVolume = 0;
    }
    if (lastVolume > 127)
    {
        lastVolume = 127;
    }
}

void adlPause()
{
    if (played != 0)
    {
        Pa_StopStream(stream);
    }
}

void adlResume()
{
    if (played != 0)
    {
        Pa_StartStream(stream);
    }
}

void adlStop()
{
    if (played != 0)
    {
        adl_panic(myDevice);

#ifdef __DJGPP__

        unsigned TimerPeriod = 0x1234DDul / NewTimerFreq;
        //disable();
        outportb(0x43, 0x34);
        outportb(0x40, TimerPeriod & 0xFF);
        outportb(0x40, TimerPeriod >> 8);
        //enable();
        unsigned long BIOStimer_begin = BIOStimer;

#endif

#ifdef __DJGPP__
        double tick_delay = 0.0;
#endif

#ifdef __DJGPP__
        // Fix the skewed clock and reset BIOS tick rate
        _farpokel(_dos_ds, 0x46C, BIOStimer_begin +
                        (BIOStimer - BIOStimer_begin)
                        * (0x1234DD / 65536.0) / NewTimerFreq);
        //disable();
        outportb(0x43, 0x34);
        outportb(0x40, 0);
        outportb(0x40, 0);
        //enable();

        clrscr();
#endif /* djgpp */

        Pa_AbortStream(stream);
        Pa_Terminate();
        adl_close(myDevice);
        played = 0;
    }
}

int adlSeek()
{
    if (myDevice)
        return adl_positionTell(myDevice);
    else
        return -1;
}

