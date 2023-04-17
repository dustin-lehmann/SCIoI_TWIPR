################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h743vitx.s 

S_DEPS += \
./Core/Startup/startup_stm32h743vitx.d 

OBJS += \
./Core/Startup/startup_stm32h743vitx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -DRCSTD_CONFIG_BOARD_REV_3 -c -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h743vitx.d ./Core/Startup/startup_stm32h743vitx.o

.PHONY: clean-Core-2f-Startup

