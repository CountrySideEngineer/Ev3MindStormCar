################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UTEST_IO.cpp 

C_SRCS += \
/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/IO/IO_Motor.c \
../src/UTEST_IO_Stub.c 

OBJS += \
./src/IO_Motor.o \
./src/UTEST_IO.o \
./src/UTEST_IO_Stub.o 

CPP_DEPS += \
./src/UTEST_IO.d 

C_DEPS += \
./src/IO_Motor.d \
./src/UTEST_IO_Stub.d 


# Each subdirectory must supply rules for building sources it contributes
src/IO_Motor.o: /Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/dev/sdk/Ev3Car/src/IO/IO_Motor.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/UTEST_IO/src/UTEST_IO.hpp" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -I/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/../../dev/sdk/Ev3Car/src -I"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/tools/include/ev3api_utest_typedef.h" -include"/Volumes/USB_DEV/ev3_toppers_app/Ev3MindStormCar/test/utest/UTEST_IO/src/UTEST_IO.hpp" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


