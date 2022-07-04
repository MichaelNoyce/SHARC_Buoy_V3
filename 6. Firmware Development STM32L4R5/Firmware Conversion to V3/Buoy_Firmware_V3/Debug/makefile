################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include Drivers/Sensor_API/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/Legacy/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BUOY_FIRMWARE_V3_Initial
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BUOY_FIRMWARE_V3_Initial.elf \

MAP_FILES += \
BUOY_FIRMWARE_V3_Initial.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BUOY_FIRMWARE_V3_Initial.list \


# All Target
all: main-build

# Main-build Target
main-build: BUOY_FIRMWARE_V3_Initial.elf secondary-outputs

# Tool invocations
BUOY_FIRMWARE_V3_Initial.elf BUOY_FIRMWARE_V3_Initial.map: $(OBJS) $(USER_OBJS) C:\Users\mpnoy\OneDrive\Documents\Masters\ 2021\SHARC_Buoy_V3\6.\ Firmware\ Development\ STM32L4R5\Firmware\ Conversion\ to\ V3\Buoy_Firmware_V3\STM32L4R5ZITXP_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -u _printf_float -o "BUOY_FIRMWARE_V3_Initial.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\mpnoy\OneDrive\Documents\Masters 2021\SHARC_Buoy_V3\6. Firmware Development STM32L4R5\Firmware Conversion to V3\Buoy_Firmware_V3\STM32L4R5ZITXP_FLASH.ld" --specs=nosys.specs -Wl,-Map="BUOY_FIRMWARE_V3_Initial.map" -Wl,--gc-sections -static  -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BUOY_FIRMWARE_V3_Initial.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BUOY_FIRMWARE_V3_Initial.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BUOY_FIRMWARE_V3_Initial.elf BUOY_FIRMWARE_V3_Initial.list BUOY_FIRMWARE_V3_Initial.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
