################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Sharc_Frame.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

CPP_SRCS += \
../Core/Src/main.cpp 

C_DEPS += \
./Core/Src/Sharc_Frame.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 

OBJS += \
./Core/Src/Sharc_Frame.o \
./Core/Src/main.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

CPP_DEPS += \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/Sensor_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Middlewares" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/GPS_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/Include" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/GCC" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32L4R5xx -c -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/Include" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/Sensor_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Middlewares" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/GPS_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/GCC" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Sharc_Frame.d ./Core/Src/Sharc_Frame.o ./Core/Src/Sharc_Frame.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

