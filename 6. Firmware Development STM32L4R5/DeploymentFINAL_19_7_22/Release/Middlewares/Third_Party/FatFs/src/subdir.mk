################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FatFs/src/diskio.c \
../Middlewares/Third_Party/FatFs/src/ff.c \
../Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
../Middlewares/Third_Party/FatFs/src/ffunicode.c 

C_DEPS += \
./Middlewares/Third_Party/FatFs/src/diskio.d \
./Middlewares/Third_Party/FatFs/src/ff.d \
./Middlewares/Third_Party/FatFs/src/ff_gen_drv.d \
./Middlewares/Third_Party/FatFs/src/ffunicode.d 

OBJS += \
./Middlewares/Third_Party/FatFs/src/diskio.o \
./Middlewares/Third_Party/FatFs/src/ff.o \
./Middlewares/Third_Party/FatFs/src/ff_gen_drv.o \
./Middlewares/Third_Party/FatFs/src/ffunicode.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FatFs/src/%.o Middlewares/Third_Party/FatFs/src/%.su: ../Middlewares/Third_Party/FatFs/src/%.c Middlewares/Third_Party/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/Sensor_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Middlewares" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/GPS_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/GCC" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FatFs-2f-src

clean-Middlewares-2f-Third_Party-2f-FatFs-2f-src:
	-$(RM) ./Middlewares/Third_Party/FatFs/src/diskio.d ./Middlewares/Third_Party/FatFs/src/diskio.o ./Middlewares/Third_Party/FatFs/src/diskio.su ./Middlewares/Third_Party/FatFs/src/ff.d ./Middlewares/Third_Party/FatFs/src/ff.o ./Middlewares/Third_Party/FatFs/src/ff.su ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.d ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.o ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.su ./Middlewares/Third_Party/FatFs/src/ffunicode.d ./Middlewares/Third_Party/FatFs/src/ffunicode.o ./Middlewares/Third_Party/FatFs/src/ffunicode.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FatFs-2f-src

