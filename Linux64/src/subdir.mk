################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/adldata.cpp \
../src/adlmidi.cpp \
../src/adlmidi_load.cpp \
../src/adlmidi_midiplay.cpp \
../src/adlmidi_opl3.cpp \
../src/adlmidi_private.cpp \
../src/dbopl.cpp 

C_SRCS += \
../src/adlmidi_mus2mid.c \
../src/adlmidi_xmi2mid.c 

OBJS += \
./src/adldata.o \
./src/adlmidi.o \
./src/adlmidi_load.o \
./src/adlmidi_midiplay.o \
./src/adlmidi_mus2mid.o \
./src/adlmidi_opl3.o \
./src/adlmidi_private.o \
./src/adlmidi_xmi2mid.o \
./src/dbopl.o 

CPP_DEPS += \
./src/adldata.d \
./src/adlmidi.d \
./src/adlmidi_load.d \
./src/adlmidi_midiplay.d \
./src/adlmidi_opl3.d \
./src/adlmidi_private.d \
./src/dbopl.d 

C_DEPS += \
./src/adlmidi_mus2mid.d \
./src/adlmidi_xmi2mid.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D_LINUX -DADLMIDI_USE_DOSBOX_OPL -D_GLIBCXX_USE_CXX11_ABI=0 -DADLMIDI_DISABLE_CPP_EXTRAS -DPA_USE_ALSA=1 -I"$(abspath $(CURDIR)/../portaudio/include") -I"$(abspath $(CURDIR)/..") -I"$(abspath $(CURDIR)/../include") -I"$(abspath $(CURDIR)/../src") -I"$(abspath $(CURDIR)/../portaudio/src/os/unix") -I"$(abspath $(CURDIR)/../portaudio/src/common") -O3 -c -fmessage-length=0 -Wno-write-strings -Wno-deprecated-declarations -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -D_GLIBCXX_USE_CXX11_ABI=0 -DADLMIDI_USE_DOSBOX_OPL -DADLMIDI_DISABLE_CPP_EXTRAS -DPA_USE_ALSA=1 -I"$(abspath $(CURDIR)/../portaudio/src/os/unix") -I"$(abspath $(CURDIR)/../src") -I"$(abspath $(CURDIR)/../portaudio/include") -I"$(abspath $(CURDIR)/../portaudio/src/common") -O3 -c -fmessage-length=0 -Wno-deprecated-declarations -Wno-implicit-function-declaration -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


