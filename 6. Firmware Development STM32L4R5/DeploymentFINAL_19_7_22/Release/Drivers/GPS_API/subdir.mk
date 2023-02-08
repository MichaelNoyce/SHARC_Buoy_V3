################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/GPS_API/M9N_Base.cpp \
../Drivers/GPS_API/M9N_C_API.cpp \
../Drivers/GPS_API/M9N_STM32.cpp \
../Drivers/GPS_API/NMEA_PUBX.cpp \
../Drivers/GPS_API/NMEA_Standard.cpp \
../Drivers/GPS_API/StaticString.cpp \
../Drivers/GPS_API/UART.cpp \
../Drivers/GPS_API/UBX.cpp \
../Drivers/GPS_API/UBX_ACK.cpp \
../Drivers/GPS_API/UBX_CFG.cpp 

OBJS += \
./Drivers/GPS_API/M9N_Base.o \
./Drivers/GPS_API/M9N_C_API.o \
./Drivers/GPS_API/M9N_STM32.o \
./Drivers/GPS_API/NMEA_PUBX.o \
./Drivers/GPS_API/NMEA_Standard.o \
./Drivers/GPS_API/StaticString.o \
./Drivers/GPS_API/UART.o \
./Drivers/GPS_API/UBX.o \
./Drivers/GPS_API/UBX_ACK.o \
./Drivers/GPS_API/UBX_CFG.o 

CPP_DEPS += \
./Drivers/GPS_API/M9N_Base.d \
./Drivers/GPS_API/M9N_C_API.d \
./Drivers/GPS_API/M9N_STM32.d \
./Drivers/GPS_API/NMEA_PUBX.d \
./Drivers/GPS_API/NMEA_Standard.d \
./Drivers/GPS_API/StaticString.d \
./Drivers/GPS_API/UART.d \
./Drivers/GPS_API/UBX.d \
./Drivers/GPS_API/UBX_ACK.d \
./Drivers/GPS_API/UBX_CFG.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GPS_API/%.o Drivers/GPS_API/%.su: ../Drivers/GPS_API/%.cpp Drivers/GPS_API/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32L4R5xx -c -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/Include" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/Sensor_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Middlewares" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/GPS_API" -I"C:/Users/uctsh/Documents/SHARCRepo/SHARC_Buoy_V3/6. Firmware Development STM32L4R5/DeploymentFINAL_19_7_22/Drivers/CMSIS/DSP/GCC" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-GPS_API

clean-Drivers-2f-GPS_API:
	-$(RM) ./Drivers/GPS_API/M9N_Base.d ./Drivers/GPS_API/M9N_Base.o ./Drivers/GPS_API/M9N_Base.su ./Drivers/GPS_API/M9N_C_API.d ./Drivers/GPS_API/M9N_C_API.o ./Drivers/GPS_API/M9N_C_API.su ./Drivers/GPS_API/M9N_STM32.d ./Drivers/GPS_API/M9N_STM32.o ./Drivers/GPS_API/M9N_STM32.su ./Drivers/GPS_API/NMEA_PUBX.d ./Drivers/GPS_API/NMEA_PUBX.o ./Drivers/GPS_API/NMEA_PUBX.su ./Drivers/GPS_API/NMEA_Standard.d ./Drivers/GPS_API/NMEA_Standard.o ./Drivers/GPS_API/NMEA_Standard.su ./Drivers/GPS_API/StaticString.d ./Drivers/GPS_API/StaticString.o ./Drivers/GPS_API/StaticString.su ./Drivers/GPS_API/UART.d ./Drivers/GPS_API/UART.o ./Drivers/GPS_API/UART.su ./Drivers/GPS_API/UBX.d ./Drivers/GPS_API/UBX.o ./Drivers/GPS_API/UBX.su ./Drivers/GPS_API/UBX_ACK.d ./Drivers/GPS_API/UBX_ACK.o ./Drivers/GPS_API/UBX_ACK.su ./Drivers/GPS_API/UBX_CFG.d ./Drivers/GPS_API/UBX_CFG.o ./Drivers/GPS_API/UBX_CFG.su

.PHONY: clean-Drivers-2f-GPS_API

