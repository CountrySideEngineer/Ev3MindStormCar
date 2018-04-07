################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UTEST_CLC.cpp \
../src/UTEST_CLC_MotorHysteresis.cpp \
../src/UTEST_CLC_TargetMotorPower.cpp 

C_SRCS += \
/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/CLC/CLC_DistAve.c \
/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/CLC/CLC_MotorHysteresis.c \
/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/CLC/CLC_TargetMotorPower.c 

OBJS += \
./src/CLC_DistAve.o \
./src/CLC_MotorHysteresis.o \
./src/CLC_TargetMotorPower.o \
./src/UTEST_CLC.o \
./src/UTEST_CLC_MotorHysteresis.o \
./src/UTEST_CLC_TargetMotorPower.o 

CPP_DEPS += \
./src/UTEST_CLC.d \
./src/UTEST_CLC_MotorHysteresis.d \
./src/UTEST_CLC_TargetMotorPower.d 

C_DEPS += \
./src/CLC_DistAve.d \
./src/CLC_MotorHysteresis.d \
./src/CLC_TargetMotorPower.d 


# Each subdirectory must supply rules for building sources it contributes
src/CLC_DistAve.o: /Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/CLC/CLC_DistAve.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/google_test/include" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/CLC_MotorHysteresis.o: /Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/CLC/CLC_MotorHysteresis.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/google_test/include" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/CLC_TargetMotorPower.o: /Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/CLC/CLC_TargetMotorPower.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/google_test/include" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/google_test/include" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


