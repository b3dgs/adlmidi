################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portaudio/src/hostapi/alsa/pa_linux_alsa.c 

OBJS += \
./portaudio/src/hostapi/alsa/pa_linux_alsa.o 

C_DEPS += \
./portaudio/src/hostapi/alsa/pa_linux_alsa.d 


# Each subdirectory must supply rules for building sources it contributes
portaudio/src/hostapi/alsa/%.o: ../portaudio/src/hostapi/alsa/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -D_GLIBCXX_USE_CXX11_ABI=0 -DADLMIDI_USE_DOSBOX_OPL -DADLMIDI_DISABLE_CPP_EXTRAS -DPA_USE_ALSA=1 -I"/home/djthunder/eclipse-workspace/adlmidi/portaudio/src/os/unix" -I"/home/djthunder/eclipse-workspace/adlmidi/src" -I"/home/djthunder/eclipse-workspace/adlmidi/portaudio/include" -I"/home/djthunder/eclipse-workspace/adlmidi/portaudio/src/common" -O3 -c -fmessage-length=0 -Wno-deprecated-declarations -Wno-implicit-function-declaration -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


