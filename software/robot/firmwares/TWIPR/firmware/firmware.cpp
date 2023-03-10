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

twipr_comm_config_t comm_config = { .huart = BOARD_CM4_UART, .register_map =
		&twipr_firmware.register_map };

TWIPR_ControlManager control;

TWIPR_Drive drive;

twipr_drive_config_t drive_config = { .id_left = 1, .id_right = 2,
		.direction_left = 1, .direction_right = -1, .torque_max = 0.25,
		.modbus_config = { .huart = BOARD_RS485_UART, .EN_GPIOx =
		BOARD_RS485_UART_EN_GPIOx, .EN_GPIO_Pin =
		BOARD_RS485_UART_EN_GPIO_PIN, .hardware = MB_UART_DMA, }, };


twipr_logging_sample_t sample_buffer[100*10] _RAM_D2;

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
	twipr_control_config_t control_config = { .K = { { 1, 2, 3, 4 }, { 5, 6, 7,
			8 } } };
	control.init(control_config);
	// Initialize the drive module

	// Initialize the supervisor module

	// Set the data links for communication

//	drive.init(drive_config);

	sample_buffer[0].general.tick = 4;

	nop();

}

/* =======================================================*/
void TWIPR_Firmware::start() {

	// Start the communication module
	this->comm.start();

	// Star the estimation module

}

/* =======================================================*/
void TWIPR_Firmware::step() {

	// Main State Machine
	switch (this->firmware_state) {
	case TWIPR_FIRMWARE_STATE_RESET: {
		break;
	}
	case TWIPR_FIRMWARE_STATE_IDLE: {
		break;
	}
	case TWIPR_FIRMWARE_STATE_RUNNING: {
		break;
	}
	case TWIPR_FIRMWARE_STATE_ERROR: {
		break;
	}
	}
}

/* =======================================================*/

