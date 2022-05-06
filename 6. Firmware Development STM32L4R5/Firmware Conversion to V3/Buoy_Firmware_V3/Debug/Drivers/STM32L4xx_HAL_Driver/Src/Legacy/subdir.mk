################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.c 

OBJS += \
./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.o 

C_DEPS += \
./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.o Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.su: ../Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.c Drivers/STM32L4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L4R5xx -DUSE_HAL_DRIVER -DDEBUG -c -I../src -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Src/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Inc" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/Sensor_API" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src-2f-Legacy

clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.d ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.o ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.su

.PHONY: clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src-2f-Legacy

