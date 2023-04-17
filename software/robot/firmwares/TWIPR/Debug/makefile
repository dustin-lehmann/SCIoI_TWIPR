################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32_core_cpp_lib/utils/subdir.mk
-include stm32_core_cpp_lib/sensors/IMU/subdir.mk
-include stm32_core_cpp_lib/robot/simplexmotion_motors/subdir.mk
-include stm32_core_cpp_lib/memory/fram/subdir.mk
-include stm32_core_cpp_lib/memory/eeprom/subdir.mk
-include stm32_core_cpp_lib/hardware/board_hardware/subdir.mk
-include stm32_core_cpp_lib/hardware/UART/subdir.mk
-include stm32_core_cpp_lib/hardware/SPI/subdir.mk
-include stm32_core_cpp_lib/hardware/RS485/subdir.mk
-include stm32_core_cpp_lib/hardware/PWM/subdir.mk
-include stm32_core_cpp_lib/hardware/LED/subdir.mk
-include stm32_core_cpp_lib/ext/madgwick_ahrs/subdir.mk
-include stm32_core_cpp_lib/control/state_feedback/subdir.mk
-include stm32_core_cpp_lib/communication/uart_interface/subdir.mk
-include stm32_core_cpp_lib/communication/modbus_rtu/subdir.mk
-include robot-control_std_lib/subdir.mk
-include firmware/safety/subdir.mk
-include firmware/estimation/subdir.mk
-include firmware/errors/subdir.mk
-include firmware/drive/subdir.mk
-include firmware/core/subdir.mk
-include firmware/control/subdir.mk
-include firmware/communication/modules/subdir.mk
-include firmware/communication/messages/subdir.mk
-include firmware/communication/subdir.mk
-include firmware/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := RC_v3_H743_TWIPR-Simple_firmware
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RC_v3_H743_TWIPR-Simple_firmware.elf \

MAP_FILES += \
RC_v3_H743_TWIPR-Simple_firmware.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
RC_v3_H743_TWIPR-Simple_firmware.list \


# All Target
all: main-build

# Main-build Target
main-build: RC_v3_H743_TWIPR-Simple_firmware.elf secondary-outputs

# Tool invocations
RC_v3_H743_TWIPR-Simple_firmware.elf RC_v3_H743_TWIPR-Simple_firmware.map: $(OBJS) $(USER_OBJS) C:\work_dir\projects\testbed\software\robots\software_board\robots\TWIPR\STM32H743VITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "RC_v3_H743_TWIPR-Simple_firmware.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\work_dir\projects\testbed\software\robots\software_board\robots\TWIPR\STM32H743VITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="RC_v3_H743_TWIPR-Simple_firmware.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

RC_v3_H743_TWIPR-Simple_firmware.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "RC_v3_H743_TWIPR-Simple_firmware.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) RC_v3_H743_TWIPR-Simple_firmware.elf RC_v3_H743_TWIPR-Simple_firmware.list RC_v3_H743_TWIPR-Simple_firmware.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
