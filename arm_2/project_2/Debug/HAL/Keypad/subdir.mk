################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Keypad/keypad.c \
../HAL/Keypad/keypad_cfg.c 

OBJS += \
./HAL/Keypad/keypad.o \
./HAL/Keypad/keypad_cfg.o 

C_DEPS += \
./HAL/Keypad/keypad.d \
./HAL/Keypad/keypad_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Keypad/%.o HAL/Keypad/%.su HAL/Keypad/%.cyclo: ../HAL/Keypad/%.c HAL/Keypad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/Common" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/Keypad" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/Led" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/LCD" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/servo_motor" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/ultrasonic" -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-Keypad

clean-HAL-2f-Keypad:
	-$(RM) ./HAL/Keypad/keypad.cyclo ./HAL/Keypad/keypad.d ./HAL/Keypad/keypad.o ./HAL/Keypad/keypad.su ./HAL/Keypad/keypad_cfg.cyclo ./HAL/Keypad/keypad_cfg.d ./HAL/Keypad/keypad_cfg.o ./HAL/Keypad/keypad_cfg.su

.PHONY: clean-HAL-2f-Keypad

