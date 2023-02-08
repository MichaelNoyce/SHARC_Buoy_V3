################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Sensor_API/HAL_BMP280.c \
../Drivers/Sensor_API/HAL_ICM20649.c \
../Drivers/Sensor_API/HAL_INA219.c \
../Drivers/Sensor_API/HAL_Iridium.c \
../Drivers/Sensor_API/HAL_SD.c \
../Drivers/Sensor_API/WaveFunctions.c 

C_DEPS += \
./Drivers/Sensor_API/HAL_BMP280.d \
./Drivers/Sensor_API/HAL_ICM20649.d \
./Drivers/Sensor_API/HAL_INA219.d \
./Drivers/Sensor_API/HAL_Iridium.d \
./Drivers/Sensor_API/HAL_SD.d \
./Drivers/Sensor_API/WaveFunctions.d 

OBJS += \
./Drivers/Sensor_API/HAL_BMP280.o \
./Drivers/Sensor_API/HAL_ICM20649.o \
./Drivers/Sensor_API/HAL_INA219.o \
./Drivers/Sensor_API/HAL_Iridium.o \
./Drivers/Sensor_API/HAL_SD.o \
./Drivers/Sensor_API/WaveFunctions.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Sensor_API/%.o Drivers/Sensor_API/%.su: ../Drivers/Sensor_API/%.c Drivers/Sensor_API/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/Sensor_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Middlewares" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/GPS_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/GCC" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Sensor_API

clean-Drivers-2f-Sensor_API:
	-$(RM) ./Drivers/Sensor_API/HAL_BMP280.d ./Drivers/Sensor_API/HAL_BMP280.o ./Drivers/Sensor_API/HAL_BMP280.su ./Drivers/Sensor_API/HAL_ICM20649.d ./Drivers/Sensor_API/HAL_ICM20649.o ./Drivers/Sensor_API/HAL_ICM20649.su ./Drivers/Sensor_API/HAL_INA219.d ./Drivers/Sensor_API/HAL_INA219.o ./Drivers/Sensor_API/HAL_INA219.su ./Drivers/Sensor_API/HAL_Iridium.d ./Drivers/Sensor_API/HAL_Iridium.o ./Drivers/Sensor_API/HAL_Iridium.su ./Drivers/Sensor_API/HAL_SD.d ./Drivers/Sensor_API/HAL_SD.o ./Drivers/Sensor_API/HAL_SD.su ./Drivers/Sensor_API/WaveFunctions.d ./Drivers/Sensor_API/WaveFunctions.o ./Drivers/Sensor_API/WaveFunctions.su

.PHONY: clean-Drivers-2f-Sensor_API

