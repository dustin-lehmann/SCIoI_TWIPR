/*
 * twipr_communication.cpp
 *
 *  Created on: 12 Mar 2023
 *      Author: Dustin Lehmann
 */

#include "twipr_communication.h"

static core_comm_SerialMessage outgoing_msg;

TWIPR_CommunicationManager::TWIPR_CommunicationManager() {

}

/* ====================================================================== */
void TWIPR_CommunicationManager::init(twipr_communication_config_t config) {
	this->config = config;

	// Initialize the UART CM4 Interface
	twipr_uart_comm_config_t uart_config = { .huart = this->config.huart };
	this->uart_interface.init(uart_config);

	this->uart_interface.registerCallback(TWIPR_UART_COMM_CALLBACK_MSG_WRITE,
			core_utils_Callback<void, core_comm_SerialMessage*>(this,
					&TWIPR_CommunicationManager::_uart_handleMsg_write_callback));

	this->uart_interface.registerCallback(TWIPR_UART_COMM_CALLBACK_MSG_READ,
			core_utils_Callback<void, core_comm_SerialMessage*>(this,
					&TWIPR_CommunicationManager::_uart_handleMsg_read_callback));

	this->uart_interface.registerCallback(TWIPR_UART_COMM_CALLBACK_MSG_FUNC,
			core_utils_Callback<void, core_comm_SerialMessage*>(this,
					&TWIPR_CommunicationManager::_uart_handleMsg_func_callback));

	// Initialize the SPI Interface
	twipr_spi_comm_config_t spi_config = { .hspi = this->config.hspi,
			.sample_buffer = this->config.sample_tx_buffer, .len_sample_buffer =
					this->config.len_sample_buffer, .trajectory_buffer =
					this->config.trajectory_rx_buffer, .len_trajectory_buffer =
					this->config.len_trajectory_buffer };
	this->spi_interface.init(spi_config);

	this->spi_interface.registerCallback(TWIPR_SPI_COMM_CALLBACK_TRAJECTORY_RX,
			core_utils_Callback<void, uint16_t>(this,
					&TWIPR_CommunicationManager::_spi_rxTrajectory_callback));
	this->spi_interface.registerCallback(TWIPR_SPI_COMM_CALLBACK_SAMPLE_TX,
			core_utils_Callback<void, uint16_t>(this,
					&TWIPR_CommunicationManager::_spi_txSamples_callback));
}
/* ====================================================================== */
void TWIPR_CommunicationManager::start() {

	// Start the UART Interface
	this->uart_interface.start();

	// Start the SPI Interface
	this->spi_interface.start();
}
/* ====================================================================== */
void TWIPR_CommunicationManager::registerCallback(twipr_communication_callback_id_t callback_id, core_utils_Callback<void, uint16_t> callback){
	switch (callback_id){
	case TWIPR_COMM_CALLBACK_NEW_TRAJECTORY: {
		this->_callbacks.new_trajectory = callback;
	}
	}
}

/* ====================================================================== */
void TWIPR_CommunicationManager::resetUART(){
	this->uart_interface.reset();
}

/* ====================================================================== */
void TWIPR_CommunicationManager::_uart_handleMsg_write_callback(
		core_comm_SerialMessage *msg) {

	RegisterMap *reg_map;

	switch (msg->address_1) {
	case TWIPR_FIRMWARE_REGISTER_MAP_GENERAL: {
		reg_map = this->config.reg_map_general;
		break;
	}
	case TWIPR_FIRMWARE_REGISTER_MAP_CONTROL: {
		reg_map = this->config.reg_map_control;
		break;
	}
	default: {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS);
		return;
		break;
	}
	}

	uint16_t address = uint8_to_uint16(msg->address_2, msg->address_3);
	if (!reg_map->hasEntry(address)){
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS);
		return;
	}
	if (reg_map->getSize(address) != msg->len) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_LEN);
		return;
	}
	if (reg_map->getType(address) != REGISTER_ENTRY_DATA) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_MSG_TYPE);
		return;
	}
	if (reg_map->getReadWriteSetting(address) == REGISTER_ENTRY_READ) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRITE);
		return;
	}

	reg_map->write(address, msg->data_ptr);

	outgoing_msg.address_1 = msg->address_1;
	outgoing_msg.address_1 = msg->address_2;
	outgoing_msg.address_1 = msg->address_3;
	outgoing_msg.cmd = MSG_COMMAND_ANSWER;
	outgoing_msg.flag = 1;
	outgoing_msg.len = 0;

	this->uart_interface.send(&outgoing_msg);

}
/* ====================================================================== */
void TWIPR_CommunicationManager::_uart_handleMsg_read_callback(
		core_comm_SerialMessage *msg) {

	RegisterMap *reg_map;

	switch (msg->address_1) {
	case TWIPR_FIRMWARE_REGISTER_MAP_GENERAL: {
		reg_map = this->config.reg_map_general;
		break;
	}
	case TWIPR_FIRMWARE_REGISTER_MAP_CONTROL: {
		reg_map = this->config.reg_map_control;
		break;
	}
	default: {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS);
		return;
		break;
	}
	}

	uint16_t address = uint8_to_uint16(msg->address_2, msg->address_3);

	if (!reg_map->hasEntry(address)){
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS);
		return;
	}
	if (reg_map->getType(address) != REGISTER_ENTRY_DATA) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_MSG_TYPE);
		return;
	}
	if (reg_map->getReadWriteSetting(address) == REGISTER_ENTRY_WRITE) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_READ);
		return;
	}

	// Read the entry into the outgoing message
	outgoing_msg.len = reg_map->read(address, outgoing_msg.data_ptr);

	// Construct the outgoing message
	outgoing_msg.address_1 = msg->address_1;
	outgoing_msg.address_2 = msg->address_2;
	outgoing_msg.address_3 = msg->address_3;
	outgoing_msg.flag = 1;
	outgoing_msg.cmd = MSG_COMMAND_ANSWER;

	this->uart_interface.send(&outgoing_msg);
}

/* ====================================================================== */
void TWIPR_CommunicationManager::_uart_handleMsg_func_callback(
		core_comm_SerialMessage *msg) {
	RegisterMap *reg_map;

	switch (msg->address_1) {
	case TWIPR_FIRMWARE_REGISTER_MAP_GENERAL: {
		reg_map = this->config.reg_map_general;
		break;
	}
	case TWIPR_FIRMWARE_REGISTER_MAP_CONTROL: {
		reg_map = this->config.reg_map_control;
		break;
	}
	default: {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS);
		return;
		break;
	}
	}

	uint16_t address = uint8_to_uint16(msg->address_2, msg->address_3);
	if (!reg_map->hasEntry(address)){
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS);
		return;
	}
	if (reg_map->getSize(address) != msg->len) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_LEN);
		return;
	}
	if (reg_map->getType(address) != REGISTER_ENTRY_FUNCTION) {
		this->_uartResponseError(msg, TWIPR_COMM_ERROR_FLAG_MSG_TYPE);
	}

	// Execute the function and store the data
	uint8_t ret_size = reg_map->execute(address, msg->data_ptr,
			outgoing_msg.data_ptr);

	// Send back a message if the function returns something
	if (ret_size > 0) {
		outgoing_msg.address_1 = msg->address_1;
		outgoing_msg.address_2 = msg->address_2;
		outgoing_msg.address_3 = msg->address_3;
		outgoing_msg.flag = 1;
		outgoing_msg.cmd = MSG_COMMAND_ANSWER;
		outgoing_msg.len = ret_size;
		this->uart_interface.send(&outgoing_msg);
	}
}

/* ====================================================================== */
void TWIPR_CommunicationManager::_uartResponseError(core_comm_SerialMessage* incoming_message, uint8_t error_code){
	outgoing_msg.address_1 = incoming_message->address_1;
	outgoing_msg.address_2 = incoming_message->address_2;
	outgoing_msg.address_3 = incoming_message->address_3;
	outgoing_msg.cmd = MSG_COMMAND_ANSWER;
	outgoing_msg.flag = 0;
	outgoing_msg.len = 1;
	outgoing_msg.data_ptr[0] = error_code;
	this->uart_interface.send(&outgoing_msg);
}
/* ====================================================================== */
void TWIPR_CommunicationManager::_spi_rxTrajectory_callback(uint16_t len) {
	// We have received a new trajectory by the CM4
	if (this->_callbacks.new_trajectory.registered){
		this->_callbacks.new_trajectory.call(len);
	}
	this->spi_interface.provideSampleData();
}
/* ====================================================================== */
void TWIPR_CommunicationManager::sampleBufferFull(){
	this->spi_interface.stopTransmission();
	this->spi_interface.provideSampleData();
	this->config.notification_gpio_tx.write(0);
	// Notify the CM4 that the sample buffer is full by writing a HIGH to the communication pin
	this->config.notification_gpio_tx.write(1);

}
/* ====================================================================== */
void TWIPR_CommunicationManager::_spi_txSamples_callback(uint16_t len) {
	this->config.notification_gpio_tx.write(0);
}


/* ====================================================================== */
void TWIPR_CommunicationManager::spi_pin_callback() {
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(SPI_PIN_GPIOx, SPI_PIN_PIN);

	if (pin_state == GPIO_PIN_SET){ // Trajectory Mode
		this->spi_interface.stopTransmission();
		this->spi_interface.receiveTrajectory();
	} else { // Sample Mode
		nop();
	}
}
