################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/cobs.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_bytes.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_debug.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_errors.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_math.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_utils_BufferQueue.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_utils_functionpointer.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_utils_gpio.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/elapsedMillis.cpp 

OBJS += \
./stm32_core_cpp_lib/utils/cobs.o \
./stm32_core_cpp_lib/utils/core_bytes.o \
./stm32_core_cpp_lib/utils/core_debug.o \
./stm32_core_cpp_lib/utils/core_errors.o \
./stm32_core_cpp_lib/utils/core_math.o \
./stm32_core_cpp_lib/utils/core_utils_BufferQueue.o \
./stm32_core_cpp_lib/utils/core_utils_functionpointer.o \
./stm32_core_cpp_lib/utils/core_utils_gpio.o \
./stm32_core_cpp_lib/utils/elapsedMillis.o 

CPP_DEPS += \
./stm32_core_cpp_lib/utils/cobs.d \
./stm32_core_cpp_lib/utils/core_bytes.d \
./stm32_core_cpp_lib/utils/core_debug.d \
./stm32_core_cpp_lib/utils/core_errors.d \
./stm32_core_cpp_lib/utils/core_math.d \
./stm32_core_cpp_lib/utils/core_utils_BufferQueue.d \
./stm32_core_cpp_lib/utils/core_utils_functionpointer.d \
./stm32_core_cpp_lib/utils/core_utils_gpio.d \
./stm32_core_cpp_lib/utils/elapsedMillis.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_core_cpp_lib/utils/cobs.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/cobs.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_bytes.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_bytes.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_debug.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_debug.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_errors.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_errors.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_math.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_math.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_utils_BufferQueue.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_utils_BufferQueue.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_utils_functionpointer.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_utils_functionpointer.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/core_utils_gpio.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/core_utils_gpio.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/utils/elapsedMillis.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils/elapsedMillis.cpp stm32_core_cpp_lib/utils/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/drive" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/errors" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/logging" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/modules" -I"C:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication/messages" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/utils" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/hardware/UART" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32_core_cpp_lib-2f-utils

clean-stm32_core_cpp_lib-2f-utils:
	-$(RM) ./stm32_core_cpp_lib/utils/cobs.cyclo ./stm32_core_cpp_lib/utils/cobs.d ./stm32_core_cpp_lib/utils/cobs.o ./stm32_core_cpp_lib/utils/cobs.su ./stm32_core_cpp_lib/utils/core_bytes.cyclo ./stm32_core_cpp_lib/utils/core_bytes.d ./stm32_core_cpp_lib/utils/core_bytes.o ./stm32_core_cpp_lib/utils/core_bytes.su ./stm32_core_cpp_lib/utils/core_debug.cyclo ./stm32_core_cpp_lib/utils/core_debug.d ./stm32_core_cpp_lib/utils/core_debug.o ./stm32_core_cpp_lib/utils/core_debug.su ./stm32_core_cpp_lib/utils/core_errors.cyclo ./stm32_core_cpp_lib/utils/core_errors.d ./stm32_core_cpp_lib/utils/core_errors.o ./stm32_core_cpp_lib/utils/core_errors.su ./stm32_core_cpp_lib/utils/core_math.cyclo ./stm32_core_cpp_lib/utils/core_math.d ./stm32_core_cpp_lib/utils/core_math.o ./stm32_core_cpp_lib/utils/core_math.su ./stm32_core_cpp_lib/utils/core_utils_BufferQueue.cyclo ./stm32_core_cpp_lib/utils/core_utils_BufferQueue.d ./stm32_core_cpp_lib/utils/core_utils_BufferQueue.o ./stm32_core_cpp_lib/utils/core_utils_BufferQueue.su ./stm32_core_cpp_lib/utils/core_utils_functionpointer.cyclo ./stm32_core_cpp_lib/utils/core_utils_functionpointer.d ./stm32_core_cpp_lib/utils/core_utils_functionpointer.o ./stm32_core_cpp_lib/utils/core_utils_functionpointer.su ./stm32_core_cpp_lib/utils/core_utils_gpio.cyclo ./stm32_core_cpp_lib/utils/core_utils_gpio.d ./stm32_core_cpp_lib/utils/core_utils_gpio.o ./stm32_core_cpp_lib/utils/core_utils_gpio.su ./stm32_core_cpp_lib/utils/elapsedMillis.cyclo ./stm32_core_cpp_lib/utils/elapsedMillis.d ./stm32_core_cpp_lib/utils/elapsedMillis.o ./stm32_core_cpp_lib/utils/elapsedMillis.su

.PHONY: clean-stm32_core_cpp_lib-2f-utils
