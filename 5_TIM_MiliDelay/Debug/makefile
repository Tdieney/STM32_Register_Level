################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Peripherals/Src/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
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


BUILD_ARTIFACT_NAME := 5_TIM_MiliDelay
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
5_TIM_MiliDelay.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
5_TIM_MiliDelay.list \

OBJCOPY_HEX += \
5_TIM_MiliDelay.hex \

OBJCOPY_BIN += \
5_TIM_MiliDelay.bin \


# All Target
all: main-build

# Main-build Target
main-build: 5_TIM_MiliDelay.elf secondary-outputs

# Tool invocations
5_TIM_MiliDelay.elf: $(OBJS) $(USER_OBJS) E:\Downloads\TAI\ LIEU\ HCMUTE\VXLNC\STM32\SelfTaught\STM32\ Getting\ Started\ -\ 2\ Level\STM32F1_CubeIDE_RegCode\5_TIM_MiliDelay\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "5_TIM_MiliDelay.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Downloads\TAI LIEU HCMUTE\VXLNC\STM32\SelfTaught\STM32 Getting Started - 2 Level\STM32F1_CubeIDE_RegCode\5_TIM_MiliDelay\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="5_TIM_MiliDelay.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

5_TIM_MiliDelay.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "5_TIM_MiliDelay.list"
	@echo 'Finished building: $@'
	@echo ' '

5_TIM_MiliDelay.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "5_TIM_MiliDelay.hex"
	@echo 'Finished building: $@'
	@echo ' '

5_TIM_MiliDelay.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "5_TIM_MiliDelay.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
