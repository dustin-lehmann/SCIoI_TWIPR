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

uint8_t test_float = 0.0;
uint8_t data[5] = { 1, 2, 3, 4, 5 };

void sample_dma_transfer_cmplt_callback(DMA_HandleTypeDef *hdma);

/* =======================================================*/
void firmware() {
	osThreadNew(firmware_task, (void*) &twipr_firmware,
			&firmware_task_attributes);
}

/* =======================================================*/
void firmware_task(void *argument) {
	TWIPR_Firmware *firmware = (TWIPR_Firmware*) argument;
	firmware->task = xTaskGetCurrentTaskHandle();
	firmware->task_function();
}

/* =======================================================*/
TWIPR_Firmware::TWIPR_Firmware() {

}

/* =======================================================*/
void TWIPR_Firmware::task_function() {
	this->init();
	this->start();

	while (true) {
		led1.toggle();
		this->_comm.uart_interface.send(0x01, 0x01, 12, 1, data, 5);
		osDelay(2000);
	}
}

/* =======================================================*/
void TWIPR_Firmware::init() {
	robot_control_init();
	robot_control_start();

	// Initialize the communication module
	twipr_communication_config_t twipr_comm_config = { .huart = BOARD_CM4_UART,
			.hspi = BOARD_SPI_CM4, .notification_gpio = core_utils_GPIO(GPIOE,
					GPIO_PIN_7), .reg_map_control = &this->_control.reg_map,
			.reg_map_general = &this->register_map, .sample_tx_buffer =
					this->_sample_buffer_tx, .len_sample_buffer =
					TWIPR_FIRMWARE_SAMPLE_BUFFER_SIZE, .trajectory_rx_buffer =
					this->_control.trajectory_rx_buffer,
			.len_trajectory_buffer = TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE };

	this->_comm.init(twipr_comm_config);
	this->_comm.registerCallback(TWIPR_COMM_CALLBACK_NEW_TRAJECTORY,
			core_utils_Callback<void, uint16_t>(&this->_control,
					&TWIPR_ControlManager::newTrajectoryReceived_callback));

	// Initialize the sensors
	twipr_sensors_config_t twipr_sensors_config = { .drive = &this->_drive, };

	this->_sensors.init(twipr_sensors_config);

	// Initilize the estimation module
	twipr_estimation_config_t twipr_estimation_config = { .sensors =
			&this->_sensors, .enable_slip_detection = 1,
			.enable_angle_threshold = 1, .angle_threshold = deg2rad(70.0), };

	this->_estimation.init(twipr_estimation_config);

	// Initialize the control module
	twipr_control_config_t twipr_control_config = { .estimation =
			&this->_estimation, .drive = &this->_drive, .max_torque =
	TWIPR_CONTROL_MAX_TORQUE, };
	memcpy(twipr_control_config.K, twipr_control_default_K, sizeof(float) * 8);

	this->_control.init(twipr_control_config);
	this->_control.registerCallback(TWIPR_CONTROL_CALLBACK_STEP,
			core_utils_Callback<void, uint32_t>(this,
					&TWIPR_Firmware::_controlStep_callback));

	// Initialize the drive module
	twipr_drive_config_t twipr_drive_config = { .id_left = 1, .id_right = 2,
			.direction_left = 1, .direction_right = -1, .torque_max = 0.3,
			.modbus_config = { .huart = BOARD_RS485_UART, .EN_GPIOx =
			BOARD_RS485_UART_EN_GPIOx, .EN_GPIO_Pin =
			BOARD_RS485_UART_EN_GPIO_PIN, .hardware = MB_UART_DMA }, };

//	this->_drive.init(twipr_drive_config);

// Initialize the supervisor module

	// Initalize the data transfer
	HAL_DMA_RegisterCallback(TWIPR_FIRMWARE_SAMPLE_DMA_STREAM,
			HAL_DMA_XFER_CPLT_CB_ID, sample_dma_transfer_cmplt_callback);

	// Register all register entries
	this->reg_entries.firmware_state.set(0x01, &this->register_map,
			&this->firmware_state, REGISTER_ENTRY_READ);
	this->reg_entries.test.set(0x02, &this->register_map, &test_float,
			REGISTER_ENTRY_READWRITE);

	this->_sample_buffer_index = 0;
}

/* =======================================================*/
void TWIPR_Firmware::start() {

	// Start the communication module
	this->_comm.start();

	// Start the estimation module
//	this->_estimation.start();

// Start the control module

}

/* =======================================================*/
void TWIPR_Firmware::step() {

	// Main State Machine
//	switch (this->firmware_state) {
//	case TWIPR_FIRMWARE_STATE_RESET: {
//		break;
//	}
//	case TWIPR_FIRMWARE_STATE_IDLE: {
//		break;
//	}
//	case TWIPR_FIRMWARE_STATE_RUNNING: {
//		break;
//	}
//	case TWIPR_FIRMWARE_STATE_ERROR: {
//		break;
//	}
//	}
}

/* =======================================================*/
void TWIPR_Firmware::_controlStep_callback(uint32_t tick) {

	this->tick = tick;

	// Build the sample
	this->_sample_buffer[this->_sample_buffer_index].general.tick = this->tick;
	this->_sample_buffer[this->_sample_buffer_index].control =
			this->_control.getSample();
	this->_sample_buffer[this->_sample_buffer_index].estimation =
			this->_estimation.getSample();
	this->_sample_buffer[this->_sample_buffer_index].sensors =
			this->_sensors.getSample();

	this->_sample_buffer_index++;

	if (this->_sample_buffer_index == TWIPR_FIRMWARE_SAMPLE_BUFFER_SIZE) {
		// Copy the sample buffer to the outgoing buffer
		HAL_DMA_Start_IT(TWIPR_FIRMWARE_SAMPLE_DMA_STREAM,
				(uint32_t) &this->_sample_buffer,
				(uint32_t) &this->_sample_buffer_tx,
				TWIPR_FIRMWARE_SAMPLE_BUFFER_SIZE
						* sizeof(twipr_logging_sample_t));
		this->_sample_buffer_index = 0;
	}
}

/* =======================================================*/
void TWIPR_Firmware::notifySampleBufferFull() {
	this->_comm.sampleBufferFull();
}

/* =======================================================*/
void sample_dma_transfer_cmplt_callback(DMA_HandleTypeDef *hdma) {
	twipr_firmware.notifySampleBufferFull();
}
