################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Sensor_API/DATAFLASH.c \
../Drivers/Sensor_API/HAL_BMP280.c \
../Drivers/Sensor_API/HAL_GPS.c \
../Drivers/Sensor_API/HAL_INA219.c \
../Drivers/Sensor_API/HAL_Iridium.c \
../Drivers/Sensor_API/HAL_MPU6050.c 

OBJS += \
./Drivers/Sensor_API/DATAFLASH.o \
./Drivers/Sensor_API/HAL_BMP280.o \
./Drivers/Sensor_API/HAL_GPS.o \
./Drivers/Sensor_API/HAL_INA219.o \
./Drivers/Sensor_API/HAL_Iridium.o \
./Drivers/Sensor_API/HAL_MPU6050.o 

C_DEPS += \
./Drivers/Sensor_API/DATAFLASH.d \
./Drivers/Sensor_API/HAL_BMP280.d \
./Drivers/Sensor_API/HAL_GPS.d \
./Drivers/Sensor_API/HAL_INA219.d \
./Drivers/Sensor_API/HAL_Iridium.d \
./Drivers/Sensor_API/HAL_MPU6050.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Sensor_API/%.o Drivers/Sensor_API/%.su: ../Drivers/Sensor_API/%.c Drivers/Sensor_API/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx -c -I../src -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/STM32L4xx_HAL_Driver/Src/Legacy" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Inc" -I"C:/Users/mpnoy/OneDrive/Documents/Masters 2021/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/Firmware Conversion to V3/Buoy_Firmware_V3/Drivers/Sensor_API" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Sensor_API

clean-Drivers-2f-Sensor_API:
	-$(RM) ./Drivers/Sensor_API/DATAFLASH.d ./Drivers/Sensor_API/DATAFLASH.o ./Drivers/Sensor_API/DATAFLASH.su ./Drivers/Sensor_API/HAL_BMP280.d ./Drivers/Sensor_API/HAL_BMP280.o ./Drivers/Sensor_API/HAL_BMP280.su ./Drivers/Sensor_API/HAL_GPS.d ./Drivers/Sensor_API/HAL_GPS.o ./Drivers/Sensor_API/HAL_GPS.su ./Drivers/Sensor_API/HAL_INA219.d ./Drivers/Sensor_API/HAL_INA219.o ./Drivers/Sensor_API/HAL_INA219.su ./Drivers/Sensor_API/HAL_Iridium.d ./Drivers/Sensor_API/HAL_Iridium.o ./Drivers/Sensor_API/HAL_Iridium.su ./Drivers/Sensor_API/HAL_MPU6050.d ./Drivers/Sensor_API/HAL_MPU6050.o ./Drivers/Sensor_API/HAL_MPU6050.su

.PHONY: clean-Drivers-2f-Sensor_API

