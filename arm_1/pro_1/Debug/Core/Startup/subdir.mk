################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f401rctx.s 

OBJS += \
./Core/Startup/startup_stm32f401rctx.o 

S_DEPS += \
./Core/Startup/startup_stm32f401rctx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/Bluetooth_module" -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/Common" -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/Keypad" -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/LCD" -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/Led" -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/servo_motor" -I"F:/ARM_projects/Arm_pic/arm_1/pro_1/HAL/ultrasonic" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f401rctx.d ./Core/Startup/startup_stm32f401rctx.o

.PHONY: clean-Core-2f-Startup

