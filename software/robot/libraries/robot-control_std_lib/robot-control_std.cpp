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
Madgwick sensor_fusion;


const osThreadAttr_t rc_task_attributes = { .name = "rc_default", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityHigh4, };


void robot_control_start();
void robot_control_sensor_task(void *argument);
void robot_control_task(void *argument);



// ------------------------------------------------------------------------------------------------------------
void robot_control_init(){
//	debug_uart.init();
//	debug_uart.registerCallback(CORE_COMM_SERIAL_SOCKET_CB_RX, uart_rx_fun, NULL);

}
// ------------------------------------------------------------------------------------------------------------
void robot_control_start(){
//	debug_uart.start();
	osThreadNew(robot_control_task, NULL, &rc_task_attributes);
}

// ------------------------------------------------------------------------------------------------------------
void robot_control_task(void *argument){
//	debug.start();

	uint32_t kernel_ticks = 0;
	while (true){
			kernel_ticks = osKernelGetTickCount();
			led_act.toggle();
			osDelayUntil(kernel_ticks + (uint32_t) 250);
	}
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
