/*
 * firmware.cpp
 *
 *  Created on: Feb 13, 2023
 *      Author: lehmann_workstation
 */

#include "main.h"
#include "firmware_c.h"
#include "firmware.hpp"
#include <stdio.h>

const osThreadAttr_t firmware_task_attributes = { .name = "firmware",
		.stack_size = 1280 * 4, .priority = (osPriority_t) osPriorityNormal, };
TWIPR_Firmware twipr_firmware;

twipr_comm_config_t comm_config = { .huart = BOARD_CM4_UART};

/* =======================================================*/
void firmware() {
	osThreadNew(firmware_task, (void*) &twipr_firmware,
			&firmware_task_attributes);
}

/* =======================================================*/
void firmware_task(void *argument) {
	TWIPR_Firmware *firmware = (TWIPR_Firmware*) argument;
	firmware->task = xTaskGetCurrentTaskHandle();
	firmware->init();

	firmware->start();
	while (true) {
		led1.toggle();
		osDelay(250);
	}
}

/* =======================================================*/

/* =======================================================*/
TWIPR_Firmware::TWIPR_Firmware() {

}

/* =======================================================*/
void TWIPR_Firmware::init() {
	robot_control_init();
	robot_control_start();

	// Initialize the communication module
	this->comm.init(comm_config);

	// Initilize the estimation module

	// Initialize the control module

	// Initialize the drive module

	// Initialize the supervisor module
}

/* =======================================================*/
void TWIPR_Firmware::start() {

	// Start the communication modules
	this->comm.start();
}

//void firmware_task(void *argument);
//void firmware_init();
//void firmware_loop();
//
//ModbusMaster modbus(BOARD_RS485_UART, MB_UART_DMA, RS485_EN_GPIO_Port,
//		RS485_EN_Pin);
//SimplexMotionMotor motor;
//
//void firmware() {
//	osThreadNew(firmware_task, NULL, &firmware_task_attributes);
//}
//
//void firmware_task(void *argument) {
//	firmware_init();
//
//	while (true) {
//		led2.toggle();
//		osDelay(250);
//	}
//
//}
//
//void firmware_init() {
//	robot_control_init();
//	robot_control_start();
//
//	cm4_uart.init(BOARD_CM4_UART);
//	cm4_uart.registerCallback(CORE_COMM_SERIAL_SOCKET_CB_RX, uart_rx_callback,
//	NULL);
//	cm4_uart.start();
//	modbus.init();
//	modbus.start();
//}
//
//void firmware_loop() {
//
//}
//
//void uart_rx_callback(void *argument, void *params) {
//	led1.toggle();
//}
