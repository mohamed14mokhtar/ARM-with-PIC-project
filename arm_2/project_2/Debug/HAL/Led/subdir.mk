################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Led/led.c \
../HAL/Led/led_cfg.c 

OBJS += \
./HAL/Led/led.o \
./HAL/Led/led_cfg.o 

C_DEPS += \
./HAL/Led/led.d \
./HAL/Led/led_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Led/%.o HAL/Led/%.su HAL/Led/%.cyclo: ../HAL/Led/%.c HAL/Led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/mokhtar/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/Common" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/Keypad" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/Led" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/LCD" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/servo_motor" -I"F:/ARM_projects/Arm_pic/arm_2/project_2/HAL/ultrasonic" -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-Led

clean-HAL-2f-Led:
	-$(RM) ./HAL/Led/led.cyclo ./HAL/Led/led.d ./HAL/Led/led.o ./HAL/Led/led.su ./HAL/Led/led_cfg.cyclo ./HAL/Led/led_cfg.d ./HAL/Led/led_cfg.o ./HAL/Led/led_cfg.su

.PHONY: clean-HAL-2f-Led

