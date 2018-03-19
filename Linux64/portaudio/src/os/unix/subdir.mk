################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portaudio/src/os/unix/pa_unix_hostapis.c \
../portaudio/src/os/unix/pa_unix_util.c 

OBJS += \
./portaudio/src/os/unix/pa_unix_hostapis.o \
./portaudio/src/os/unix/pa_unix_util.o 

C_DEPS += \
./portaudio/src/os/unix/pa_unix_hostapis.d \
./portaudio/src/os/unix/pa_unix_util.d 


# Each subdirectory must supply rules for building sources it contributes
portaudio/src/os/unix/%.o: ../portaudio/src/os/unix/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -D_GLIBCXX_USE_CXX11_ABI=0 -DADLMIDI_USE_DOSBOX_OPL -DADLMIDI_DISABLE_CPP_EXTRAS -DPA_USE_ALSA=1 -I"$(abspath $(CURDIR)/../portaudio/src/os/unix") -I"$(abspath $(CURDIR)/../src") -I"$(abspath $(CURDIR)/../portaudio/include") -I"$(abspath $(CURDIR)/../portaudio/src/common") -O3 -c -fmessage-length=0 -Wno-deprecated-declarations -Wno-implicit-function-declaration -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


