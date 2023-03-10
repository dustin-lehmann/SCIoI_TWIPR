/*
 * twipr_communication.cpp
 *
 *  Created on: Feb 22, 2023
 *      Author: lehmann_workstation
 */

#include <communication/twipr_communication.h>

static core_comm_UartInterface_config twipr_communication_uart_cm4_interface_config =
		{ .uart = { .mode = CORE_HARDWARE_UART_MODE_DMA, .cobs_encode_rx = 1,
				.cobs_encode_tx = 1, .queues = 1, }, .use_rtos = 1,
				.use_protocol = 1, .use_queue = 1, .rx_callback_value =
						CORE_COMM_SERIAL_SOCKET_RX_CB_MSG };

//static core_comm_UartInterface_config twipr_communication_uart_ext_interface_config =
//		{ .uart = { .mode = CORE_HARDWARE_UART_MODE_DMA, .cobs_encode_rx = 1,
//				.cobs_encode_tx = 1, .queues = 1, }, .use_rtos = 1,
//				.use_protocol = 1, .use_queue = 0, .rx_callback_value =
//						CORE_COMM_SERIAL_SOCKET_RX_CB_MSG };

static const osThreadAttr_t task_attributes = { .name = "comm_task",
		.stack_size = 512 * 4, .priority = (osPriority_t) osPriorityNormal };

core_comm_SerialMessage incoming_msg;
core_comm_SerialMessage outgoing_msg;

uint8_t function_output_buffer[128] = { 0 };

/* =======================================================*/
TWIPR_Communication::TWIPR_Communication() {

}

/* =======================================================*/
void TWIPR_Communication::init(twipr_comm_config_t config) {

	// Copy the register map
	this->register_map = config.register_map;

	// Initialize the UART interface to the Raspberry Pi
	this->uart_cm4.init(config.huart,
			twipr_communication_uart_cm4_interface_config);
	this->uart_cm4.registerCallback(CORE_COMM_SERIAL_SOCKET_CB_RX,
			uart_cm4_rx_callback, this);
}

/* =======================================================*/
void TWIPR_Communication::start() {

	// Start the UART interfaces
	this->uart_cm4.start();

	// Start the board UART interface
//	this->uart_ext.start();

// Start the task
	this->thread = osThreadNew(twipr_comm_task, this, &task_attributes);
}

/* =======================================================*/
void TWIPR_Communication::send(uint8_t cmd, uint8_t module, uint16_t address,
		uint8_t flag, uint8_t *data, uint8_t len) {

	outgoing_msg.cmd = cmd;
	outgoing_msg.address_1 = module;
	outgoing_msg.address_2 = address >> 8;
	outgoing_msg.address_3 = address;
	outgoing_msg.flag = flag;

	for (int i = 0; i < len; i++) {
		outgoing_msg.data[i] = data[i];
	}
	outgoing_msg.len = len;
	this->send(&outgoing_msg);
}

/* =======================================================*/
void TWIPR_Communication::send(core_comm_SerialMessage *msg) {

	// Check the message

	this->uart_cm4.send(msg);
}

/* =======================================================*/
void twipr_comm_task(void *argument) {

	TWIPR_Communication *comm = (TWIPR_Communication*) argument;
	comm->task = xTaskGetCurrentTaskHandle();

	xTaskNotifyGive(comm->task);
	nop();

//	uint32_t kernel_ticks = 0;
	while (true) {
//		kernel_ticks = osKernelGetTickCount();

		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		// Do stuff
		comm->task_loop();

//		osDelayUntil(kernel_ticks + (uint32_t) 1);
	}
}

/* =======================================================*/
void TWIPR_Communication::task_loop() {
	// Check if there is a new message in the CM4 UART
	if (this->uart_cm4.rx_queue.available()) {
		this->_handleIncomingMessages();
	}
}

/* =======================================================*/
void TWIPR_Communication::_handleIncomingMessages() {
	// Loop through all the messages in the rx queue
	while (this->uart_cm4.rx_queue.available()) {
		this->uart_cm4.rx_queue.read(&incoming_msg);

		// Check if the message is correct
		// TODO

		// Handle the different addresses

		// Handle the different commands
		switch (incoming_msg.cmd) {
		case MSG_COMMAND_WRITE: {
			this->_handleMessage_write(&incoming_msg);
			break;
		}
		case MSG_COMMAND_READ: {
			this->_handleMessage_read(&incoming_msg);
			break;
		}
		case MSG_COMMAND_EVENT: {
			nop();
			break;
		}
		case MSG_COMMAND_MSG: {
			nop();
			break;
		}
		case MSG_COMMAND_FCT: {
			this->_handleMessage_function(&incoming_msg);
			break;
		}
		case MSG_COMMAND_ECHO: {
			this->send(&incoming_msg);
			break;
		}
		default: {
			continue;
			break;
		}
		}
		this->last_received_message_tick = osKernelGetTickCount();
	}
}

/* =======================================================*/
void TWIPR_Communication::_handleMessage_write(core_comm_SerialMessage *msg) {
	// Check if the module is the default module
	if (!msg->address_1 == 0x00) {
		return; // TODO
	}

	// Check if the address exists in the register map
	uint16_t address = uint8_to_uint16(msg->address_2, msg->address_3);
	if (!this->register_map->hasEntry(address)) {
		return;
	}
	// Check if the length of the message is correct
	if (this->register_map->getSize(address) != msg->len) {
		return; // TODO
	}

	// Write the entry
	this->register_map->write(address, msg->data);
}

/* =======================================================*/
void TWIPR_Communication::_handleMessage_read(core_comm_SerialMessage *msg) {

	// Check if the module is the default module
	if (!msg->address_1 == 0x00) {
		return; // TODO
	}

	// Check if the address exists in the register map
	uint16_t address = uint8_to_uint16(msg->address_2, msg->address_3);

	if (!this->register_map->hasEntry(address)) {
		return;
	}

	// Check if this is a data entry
	if (this->register_map->getType(address) != REGISTER_ENTRY_DATA) {
		return;
	}

	// Read the entry into the outgoing message
	outgoing_msg.len = this->register_map->read(address, outgoing_msg.data);

	// Construct the outgoing message
	outgoing_msg.address_1 = msg->address_1;
	outgoing_msg.address_2 = msg->address_2;
	outgoing_msg.address_3 = msg->address_3;
	outgoing_msg.flag = 1;
	outgoing_msg.cmd = MSG_COMMAND_ANSWER;

	this->send(&outgoing_msg);
}
/* =======================================================*/
void TWIPR_Communication::_handleMessage_function(
		core_comm_SerialMessage *msg) {

	// Check if the module is the default module
	if (!msg->address_1 == 0x00) {
		return; // TODO
	}

	// Check if the address exists in the register map and is a function
	uint16_t address = uint8_to_uint16(msg->address_2, msg->address_3);

	if (!this->register_map->hasEntry(address)) {
		return;
	}

	// Check if it is a function
	if (this->register_map->getType(address) != REGISTER_ENTRY_FUNCTION) {
		return;
	}

	// Execute the function and store the data
	uint8_t ret_size = this->register_map->execute(address, msg->data,
			outgoing_msg.data);

	// Send back a message if the function returns something
	if (ret_size > 0) {
		outgoing_msg.address_1 = msg->address_1;
		outgoing_msg.address_2 = msg->address_2;
		outgoing_msg.address_3 = msg->address_3;
		outgoing_msg.flag = 1;
		outgoing_msg.cmd = MSG_COMMAND_ANSWER;
		outgoing_msg.len = ret_size;
		this->send(&outgoing_msg);
	}

}

/* =======================================================*/
void uart_cm4_rx_callback(void *argument, void *parameters) {

	TWIPR_Communication *comm = (TWIPR_Communication*) parameters;
	if (comm->task != NULL) {
//		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		nop();

		xTaskNotifyGive(comm->task);

//		vTaskNotifyGiveFromISR(comm->task, &xHigherPriorityTaskWoken);
//		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
