################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/startup_stm32l4r5zitxp.s 

C_SRCS += \
../src/Sharc_Frame.c \
../src/main.c \
../src/stm32l4xx_hal_msp.c \
../src/stm32l4xx_it.c \
../src/syscalls.c \
../src/system_stm32l4xx.c 

OBJS += \
./src/Sharc_Frame.o \
./src/main.o \
./src/startup_stm32l4r5zitxp.o \
./src/stm32l4xx_hal_msp.o \
./src/stm32l4xx_it.o \
./src/syscalls.o \
./src/system_stm32l4xx.o 

S_DEPS += \
./src/startup_stm32l4r5zitxp.d 

C_DEPS += \
./src/Sharc_Frame.d \
./src/main.d \
./src/stm32l4xx_hal_msp.d \
./src/stm32l4xx_it.d \
./src/syscalls.d \
./src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L4R5xx -DUSE_HAL_DRIVER -DDEBUG -c -I../src -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Src/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Inc" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/Sensor_API" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"
src/%.o: ../src/%.s src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DSTM32L4R5xx -c -I../src -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Src/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Inc" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/Sensor_API" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-src

clean-src:
	-$(RM) ./src/Sharc_Frame.d ./src/Sharc_Frame.o ./src/Sharc_Frame.su ./src/main.d ./src/main.o ./src/main.su ./src/startup_stm32l4r5zitxp.d ./src/startup_stm32l4r5zitxp.o ./src/stm32l4xx_hal_msp.d ./src/stm32l4xx_hal_msp.o ./src/stm32l4xx_hal_msp.su ./src/stm32l4xx_it.d ./src/stm32l4xx_it.o ./src/stm32l4xx_it.su ./src/syscalls.d ./src/syscalls.o ./src/syscalls.su ./src/system_stm32l4xx.d ./src/system_stm32l4xx.o ./src/system_stm32l4xx.su

.PHONY: clean-src

