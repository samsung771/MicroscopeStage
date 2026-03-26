################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/USBX/UX\ Device\ CoreStack/subdir.mk
-include Middlewares/USBX/UX\ Device\ Controllers/subdir.mk
-include Middlewares/USBX/UX\ Device\ Class\ CDC\ ACM/subdir.mk
-include Middlewares/USBX/Core\ System/subdir.mk
-include Middlewares/ThreadX/Core/subdir.mk
-include Drivers/STM32C0xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/USBX/App/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include Application/User/AZURE_RTOS/App/subdir.mk
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


BUILD_ARTIFACT_NAME := Ux_Device_CDC_ACM
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Ux_Device_CDC_ACM.elf \

MAP_FILES += \
Ux_Device_CDC_ACM.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Ux_Device_CDC_ACM.list \


# All Target
all: main-build

# Main-build Target
main-build: Ux_Device_CDC_ACM.elf secondary-outputs

# Tool invocations
Ux_Device_CDC_ACM.elf Ux_Device_CDC_ACM.map: $(OBJS) $(USER_OBJS) C:\Users\samdl\STM32CubeIDE\workspace_1.19.0\Ux_Device_CDC_ACM\STM32CubeIDE\STM32C071RBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Ux_Device_CDC_ACM.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\samdl\STM32CubeIDE\workspace_1.19.0\Ux_Device_CDC_ACM\STM32CubeIDE\STM32C071RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Ux_Device_CDC_ACM.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Ux_Device_CDC_ACM.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Ux_Device_CDC_ACM.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Ux_Device_CDC_ACM.elf Ux_Device_CDC_ACM.list Ux_Device_CDC_ACM.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
