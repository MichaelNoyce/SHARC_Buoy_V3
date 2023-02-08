################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/App/fatfs.c 

C_DEPS += \
./FATFS/App/fatfs.d 

OBJS += \
./FATFS/App/fatfs.o 


# Each subdirectory must supply rules for building sources it contributes
FATFS/App/%.o FATFS/App/%.su: ../FATFS/App/%.c FATFS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/Sensor_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Middlewares" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/GPS_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/GCC" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS-2f-App

clean-FATFS-2f-App:
	-$(RM) ./FATFS/App/fatfs.d ./FATFS/App/fatfs.o ./FATFS/App/fatfs.su

.PHONY: clean-FATFS-2f-App

