################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../firmware/communication/modules/twipr_spi_communication.cpp \
../firmware/communication/modules/twipr_uart_communication.cpp 

OBJS += \
./firmware/communication/modules/twipr_spi_communication.o \
./firmware/communication/modules/twipr_uart_communication.o 

CPP_DEPS += \
./firmware/communication/modules/twipr_spi_communication.d \
./firmware/communication/modules/twipr_uart_communication.d 


# Each subdirectory must supply rules for building sources it contributes
firmware/communication/modules/%.o firmware/communication/modules/%.su firmware/communication/modules/%.cyclo: ../firmware/communication/modules/%.cpp firmware/communication/modules/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-firmware-2f-communication-2f-modules

clean-firmware-2f-communication-2f-modules:
	-$(RM) ./firmware/communication/modules/twipr_spi_communication.cyclo ./firmware/communication/modules/twipr_spi_communication.d ./firmware/communication/modules/twipr_spi_communication.o ./firmware/communication/modules/twipr_spi_communication.su ./firmware/communication/modules/twipr_uart_communication.cyclo ./firmware/communication/modules/twipr_uart_communication.d ./firmware/communication/modules/twipr_uart_communication.o ./firmware/communication/modules/twipr_uart_communication.su

.PHONY: clean-firmware-2f-communication-2f-modules
