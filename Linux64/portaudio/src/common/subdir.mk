################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portaudio/src/common/pa_allocation.c \
../portaudio/src/common/pa_converters.c \
../portaudio/src/common/pa_cpuload.c \
../portaudio/src/common/pa_debugprint.c \
../portaudio/src/common/pa_dither.c \
../portaudio/src/common/pa_front.c \
../portaudio/src/common/pa_process.c \
../portaudio/src/common/pa_ringbuffer.c \
../portaudio/src/common/pa_stream.c \
../portaudio/src/common/pa_trace.c 

OBJS += \
./portaudio/src/common/pa_allocation.o \
./portaudio/src/common/pa_converters.o \
./portaudio/src/common/pa_cpuload.o \
./portaudio/src/common/pa_debugprint.o \
./portaudio/src/common/pa_dither.o \
./portaudio/src/common/pa_front.o \
./portaudio/src/common/pa_process.o \
./portaudio/src/common/pa_ringbuffer.o \
./portaudio/src/common/pa_stream.o \
./portaudio/src/common/pa_trace.o 

C_DEPS += \
./portaudio/src/common/pa_allocation.d \
./portaudio/src/common/pa_converters.d \
./portaudio/src/common/pa_cpuload.d \
./portaudio/src/common/pa_debugprint.d \
./portaudio/src/common/pa_dither.d \
./portaudio/src/common/pa_front.d \
./portaudio/src/common/pa_process.d \
./portaudio/src/common/pa_ringbuffer.d \
./portaudio/src/common/pa_stream.d \
./portaudio/src/common/pa_trace.d 


# Each subdirectory must supply rules for building sources it contributes
portaudio/src/common/%.o: ../portaudio/src/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -D_GLIBCXX_USE_CXX11_ABI=0 -DADLMIDI_USE_DOSBOX_OPL -DADLMIDI_DISABLE_CPP_EXTRAS -DPA_USE_ALSA=1 -I"$(abspath $(CURDIR)/../portaudio/src/os/unix") -I"$(abspath $(CURDIR)/../src") -I"$(abspath $(CURDIR)/../portaudio/include") -I"$(abspath $(CURDIR)/../portaudio/src/common") -O3 -c -fmessage-length=0 -Wno-deprecated-declarations -Wno-implicit-function-declaration -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


