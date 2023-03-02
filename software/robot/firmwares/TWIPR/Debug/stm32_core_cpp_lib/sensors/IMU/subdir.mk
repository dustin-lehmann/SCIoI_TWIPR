################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/sensors/IMU/bmi160.cpp \
C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.cpp 

OBJS += \
./stm32_core_cpp_lib/sensors/IMU/bmi160.o \
./stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.o 

CPP_DEPS += \
./stm32_core_cpp_lib/sensors/IMU/bmi160.d \
./stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_core_cpp_lib/sensors/IMU/bmi160.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/sensors/IMU/bmi160.cpp stm32_core_cpp_lib/sensors/IMU/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.o: C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.cpp stm32_core_cpp_lib/sensors/IMU/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DRCSTD_CONFIG_BOARD_REV_3 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/robot-control_std_lib" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/communication/modbus_rtu" -I"C:/work_dir/projects/testbed/software/robots/software_board/libraries/general/stm32_core_cpp_lib/robot/simplexmotion_motors" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/estimation" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/control" -I"D:/work_dir/projects/testbed/software/robots/software_board/robots/TWIPR/firmware/communication" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32_core_cpp_lib-2f-sensors-2f-IMU

clean-stm32_core_cpp_lib-2f-sensors-2f-IMU:
	-$(RM) ./stm32_core_cpp_lib/sensors/IMU/bmi160.d ./stm32_core_cpp_lib/sensors/IMU/bmi160.o ./stm32_core_cpp_lib/sensors/IMU/bmi160.su ./stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.d ./stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.o ./stm32_core_cpp_lib/sensors/IMU/core_imu_helpers.su

.PHONY: clean-stm32_core_cpp_lib-2f-sensors-2f-IMU

