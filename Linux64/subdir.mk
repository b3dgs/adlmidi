################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../adlmidi_player.cpp 

OBJS += \
./adlmidi_player.o 

CPP_DEPS += \
./adlmidi_player.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D_LINUX -DADLMIDI_USE_DOSBOX_OPL -D_GLIBCXX_USE_CXX11_ABI=0 -DADLMIDI_DISABLE_CPP_EXTRAS -DPA_USE_ALSA=1 -I"$(abspath $(CURDIR)/../portaudio/include") -I"$(abspath $(CURDIR)/..") -I"$(abspath $(CURDIR)/../include") -I"$(abspath $(CURDIR)/../src") -I"$(abspath $(CURDIR)/../portaudio/src/os/unix") -I"$(abspath $(CURDIR)/../portaudio/src/common") -O3 -c -fmessage-length=0 -Wno-write-strings -Wno-deprecated-declarations -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


