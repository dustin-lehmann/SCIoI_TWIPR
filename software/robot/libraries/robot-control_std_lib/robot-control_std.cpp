/*
 * robot-control_std.cpp
 *
 *  Created on: Jul 29, 2022
 *      Author: Dustin Lehmann
 */

#include "robot-control_std.h"
#include <stdio.h>

core_hardware_LED led1(BOARD_LED_1_PORT, BOARD_LED_1_PIN);
core_hardware_LED led2(BOARD_LED_2_PORT, BOARD_LED_2_PIN);
core_hardware_LED led_act(BOARD_LED_ACT_PORT, BOARD_LED_ACT_PIN);



//core_debug_Interface debug(CORE_DEBUG_INTERFACE_UART, BOARD_DEBUG_UART);
BMI160 imu(BOARD_SPI_INTERN, BOARD_CS_IMU_PORT, BOARD_CS_IMU_PIN);
Madgwick sensor_fusion;


const osThreadAttr_t rc_task_attributes = { .name = "rc_default", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityHigh4, };

const osThreadAttr_t sensor_task_attributes = { .name = "rc_sensors", .stack_size =
		512 * 4, .priority = (osPriority_t) osPriorityHigh4, };

void robot_control_start();
void robot_control_sensor_task(void *argument);
void robot_control_task(void *argument);



// ------------------------------------------------------------------------------------------------------------
void robot_control_init(){
//	debug_uart.init();
//	debug_uart.registerCallback(CORE_COMM_SERIAL_SOCKET_CB_RX, uart_rx_fun, NULL);


	uint8_t imu_ok = imu.init();

	if (!imu_ok){
		// I need some error handling here
	}
}
// ------------------------------------------------------------------------------------------------------------
void robot_control_start(){
//	debug_uart.start();
	osThreadNew(robot_control_sensor_task, NULL, &sensor_task_attributes);
	osThreadNew(robot_control_task, NULL, &rc_task_attributes);
}

// ------------------------------------------------------------------------------------------------------------
void robot_control_task(void *argument){
//	debug.start();

	uint32_t kernel_ticks = 0;
	while (true){
			kernel_ticks = osKernelGetTickCount();
			led_act.toggle();
			osDelayUntil(kernel_ticks + (uint32_t) 100);
	}
}

// ------------------------------------------------------------------------------------------------------------
void robot_control_sensor_task(void *argument){
	uint32_t kernel_ticks = 0;
	uint32_t tick = 0;
	sensor_fusion.begin(RC_SENSOR_LOOP_FREQ);

	while (true){
		tick++;
		kernel_ticks = osKernelGetTickCount();

		// Read the IMU
		imu.update();

		// Update the sensor fusion algorithm for the IMU
		sensor_fusion.updateIMU(imu.gyr.x, imu.gyr.y, imu.gyr.z, imu.acc.x, imu.acc.y, imu.acc.z);


		if (tick % 5 == 0){
			tick = 0;
//			led2.toggle();
		}

		osDelayUntil(kernel_ticks + (uint32_t) (1000.0/RC_SENSOR_LOOP_FREQ));
	}
}

// ------------------------------------------------------------------------------------------------------------
void robot_control_loop(){

}






//core_utils_RingBuffer<128> ringBuffer;

//void test() {
//	uint8_t data[20] = {0};
//
//	ringBuffer.add(1);
//	ringBuffer.add(2);
//	ringBuffer.add(3);
//	ringBuffer.add(4);
//
//	ringBuffer.get_n_bytes(data, 3);
//}
