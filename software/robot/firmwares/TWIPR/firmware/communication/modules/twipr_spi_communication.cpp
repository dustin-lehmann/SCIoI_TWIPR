/*
 * twipr_spi_communication.cpp
 *
 *  Created on: 12 Mar 2023
 *      Author: Dustin Lehmann
 */

#include "twipr_spi_communication.h"

static uint8_t tx_cmd_buf[4] = { 0x55, 0x00, 0x00, 0x00};

TWIPR_SPI_Communication::TWIPR_SPI_Communication() {

}

/* =============================================================== */
void TWIPR_SPI_Communication::init(twipr_spi_comm_config_t config) {
	this->config = config;

	core_hardware_spi_config_t spi_config = { .hspi = this->config.hspi,
			.rx_buffer = (uint8_t*) this->config.trajectory_buffer, .tx_buffer =
					(uint8_t*) this->config.sample_buffer, };

	this->spi_slave.init(spi_config);
	this->spi_slave.registerCallback(CORE_HARDWARE_SPI_CALLBACK_RX,
			core_utils_Callback<void, void>(this,
					&TWIPR_SPI_Communication::rx_cmplt_function));

	this->spi_slave.registerCallback(CORE_HARDWARE_SPI_CALLBACK_TX,
			core_utils_Callback<void, void>(this,
					&TWIPR_SPI_Communication::tx_cmplt_function));

	this->spi_slave.registerCallback(CORE_HARDWARE_SPI_CALLBACK_RXTX,
			core_utils_Callback<void, void>(this,
					&TWIPR_SPI_Communication::rxtx_cmplt_function));

	uint8_t trajectory_size = sizeof(twipr_control_trajectory_input_t);
	uint8_t sample_size = sizeof(twipr_logging_sample_t);
	tx_cmd_buf[1] = trajectory_size;
	tx_cmd_buf[2] =	sample_size;

}
/* =============================================================== */
void TWIPR_SPI_Communication::start() {
	this->spi_slave.start();
	this->listenForCommand();
}
/* =============================================================== */
void TWIPR_SPI_Communication::registerCallback(
		twipr_spi_comm_callback_id_t callback_id,
		core_utils_Callback<void, uint16_t> callback) {
	switch (callback_id) {
	case TWIPR_SPI_COMM_CALLBACK_SAMPLE_TX: {
		this->callbacks.sample_tx_callback = callback;
		break;
	}
	case TWIPR_SPI_COMM_CALLBACK_TRAJECTORY_RX: {
		this->callbacks.trajectory_rx_callback = callback;
		break;
	}
	}
}
/* =============================================================== */
void TWIPR_SPI_Communication::listenForCommand() {
	this->mode = TWIPR_SPI_COMM_MODE_NONE;
	this->spi_slave.receiveTransmitData(this->_commandBuffer, tx_cmd_buf,
	TWIPR_SPI_COMMAND_MESSAGE_LENGTH);
}
/* =============================================================== */
void TWIPR_SPI_Communication::receiveTrajectory(uint16_t len) {
	this->receiveTrajectory(this->config.trajectory_buffer, sizeof(twipr_control_trajectory_input_t)* len);
}
/* =============================================================== */
void TWIPR_SPI_Communication::receiveTrajectory(
		twipr_control_trajectory_input_t *trajectory_buffer, uint16_t len) {
	this->spi_slave.receiveData((uint8_t*) trajectory_buffer, len);
}
/* =============================================================== */
void TWIPR_SPI_Communication::provideSampleData(uint16_t len) {
	this->provideSampleData(this->config.sample_buffer, len);
}
/* =============================================================== */
void TWIPR_SPI_Communication::provideSampleData(
		twipr_logging_sample_t *sample_buffer, uint16_t len) {

	this->mode = TWIPR_SPI_COMM_MODE_TX;
	this->spi_slave.provideData((uint8_t*) sample_buffer, sizeof(twipr_logging_sample_t) * len);
}
/* =============================================================== */
void TWIPR_SPI_Communication::rx_cmplt_function() {
	if (this->callbacks.trajectory_rx_callback.registered) {
		this->callbacks.trajectory_rx_callback.call(this->_len);
	}

	// Start listening again for commands
	this->listenForCommand();
}
/* =============================================================== */
void TWIPR_SPI_Communication::tx_cmplt_function() {

	// Execute the TX Callback, if registered
	if (this->callbacks.sample_tx_callback.registered) {
		this->callbacks.sample_tx_callback.call(this->_len);
	}

	// Start listening again for commands
	this->listenForCommand();
}
/* =============================================================== */
void TWIPR_SPI_Communication::rxtx_cmplt_function() {
	// Received a command
	if (this->mode == TWIPR_SPI_COMM_MODE_NONE) {
		// Check the command buffer
		//
		uint8_t command = this->_commandBuffer[0];
//		uint8_t temp = this->_commandBuffer[1];
		uint16_t len = uint8_to_uint16(this->_commandBuffer[2],
				this->_commandBuffer[3]);

		this->_len = len;

		switch (command) {
		case 0x01: {
			// Read sample data
			this->provideSampleData(len);
			break;
		}
		case 0x02: {
			// Write trajectory
			this->receiveTrajectory(len);
			break;
		}
		// Dummy read
		case 0x00 : {
			this->listenForCommand();
			break;
		}
		}
	}
}
/* =============================================================== */

/* =============================================================== */

/* =============================================================== */

/* =============================================================== */

/* =============================================================== */

