/*
 * serial_socket.cpp
 *
 *  Created on: 8 Jul 2022
 *      Author: Dustin Lehmann
 */

#include "core_comm_SerialSocket.h"

#if CORE_CONFIG_USE_UART && CORE_CONFIG_USE_RTOS

core_hardware_UART_config std_hardware_uart_config = { .mode =
		CORE_HARDWARE_UART_MODE_DMA, .cobs_encode_rx = 1, .cobs_encode_tx = 1,
		.queues = 1, };

core_comm_UartInterface_config std_uart_config = { .uart =
		std_hardware_uart_config, .use_rtos = 1, .use_protocol = 1, .use_queue =
		1, .rx_callback_value = CORE_COMM_SERIAL_SOCKET_RX_CB_MSG, };

core_comm_UartInterface::core_comm_UartInterface(){
	this->state = CORE_COMM_SERIAL_SOCKET_STATE_NONE;
}


/* ============================================================================= */
void core_comm_UartInterface::init(UART_HandleTypeDef *huart) {
	this->init(huart, std_uart_config);
}
/* ============================================================================= */
void core_comm_UartInterface::init(UART_HandleTypeDef *huart, core_comm_UartInterface_config config) {

	this->config = config;
	this->uart.init(huart, this->config.uart);

	// Add the rx callback to the UART
	this->uart.registerCallback(CORE_HARDWARE_UART_CB_RX,
			core_comm_SerialSocket_rx_notify, this);

	this->state = CORE_COMM_SERIAL_SOCKET_STATE_INIT;
}

/* ============================================================================= */
void core_comm_UartInterface::start() {

	this->uart.start();
	this->state = CORE_COMM_SERIAL_SOCKET_STATE_RUN;

#ifdef CORE_CONFIG_USE_RTOS
	if (this->config.use_rtos) {
		this->startRTOS();
	}
#else
	core_ErrorHandler(1);
#endif
}

/* ============================================================================= */
void core_comm_UartInterface::startRTOS() {
	const osThreadAttr_t task_attributes = { .name = "socket_task",
			.stack_size = CORE_COMM_SERIAL_SOCKET_RTOS_RX_STACKSIZE, .priority =
					(osPriority_t) CORE_COMM_SERIAL_SOCKET_RTOS_RX_PRIORITY };

	this->rtos.threadId = osThreadNew(core_comm_SerialSocket_RTOS_Task, this,
			&task_attributes);
}

/* ============================================================================= */
void core_comm_UartInterface::send(core_comm_SerialMessage *message) {
	uint8_t len = message->encode(this->tx_buf);
	this->send(this->tx_buf, len);
}

/* ============================================================================= */
void core_comm_UartInterface::send(uint8_t *buffer, uint8_t len) {
	if (this->state != CORE_COMM_SERIAL_SOCKET_STATE_RUN) {
		core_ErrorHandler(1);
	}

	this->uart.send(buffer, len);
}

/* ============================================================================= */
void core_comm_UartInterface::sendRaw(uint8_t *buffer, uint8_t len) {
	if (this->state != CORE_COMM_SERIAL_SOCKET_STATE_RUN) {
		core_ErrorHandler(1);
	}

	this->uart.sendRaw(buffer, len);
}

/* ============================================================================= */
void core_comm_UartInterface::registerCallback(
		core_comm_SerialSocket_CB_ID callback_id,
		void (*callback)(void *argument, void *params), void *params) {

	switch (callback_id) {
	case CORE_COMM_SERIAL_SOCKET_CB_RX: {
		this->callbacks.rx.callback = callback;
		this->callbacks.rx.params = params;
		this->callbacks.rx.registered = 1;
		break;
	}
	case CORE_COMM_SERIAL_SOCKET_CB_ERROR: {
		break;
	}
	}
}

/* ============================================================================= */
core_comm_SerialMessage core_comm_UartInterface::getMessage() {
	return this->rx_queue.read();
}

/* ============================================================================= */
core_comm_SerialMessage* core_comm_UartInterface::getMessagePointer() {
	return this->rx_queue.readPointer();
}

/* ============================================================================= */
uint8_t core_comm_UartInterface::rx_function() {
	uint8_t num_messages = 0;

	while (this->uart.available() > 0) {
		core_utils_Buffer *buffer = this->uart.rx_queue.read();

		if (this->config.use_protocol) {
			// Decode the buffer into the rx message
			uint8_t correct_message = this->rx_message.decode(buffer);

			// If the buffer did not contain a correct message do not proceed with the message handling
			if (!correct_message) {
				continue;
			}

			if (this->config.use_queue) {
				this->rx_queue.write(&rx_message);
			}

			if (this->callbacks.rx.registered) {
				if (this->config.rx_callback_value == CORE_COMM_SERIAL_SOCKET_RX_CB_MSG){
					this->callbacks.rx.call(&rx_message);
				} else if (this->config.rx_callback_value == CORE_COMM_SERIAL_SOCKET_RX_CB_IFC){
					this->callbacks.rx.call(this);
				}
			}
		} else { // no protocol used
			if (this->callbacks.rx.registered) {
				if (this->config.rx_callback_value == CORE_COMM_SERIAL_SOCKET_RX_CB_BUF){
					this->callbacks.rx.call(buffer);
				} else {
					while (1){
						nop();
						// Not yet implemented
					}
				}
			}
		}

		num_messages++;

	}
	return num_messages;
}
/* ============================================================================= */
void core_comm_SerialSocket_RTOS_Task(void *SerialSocket) {
	core_comm_UartInterface *socket = (core_comm_UartInterface*) SerialSocket;

	// Get the task handle and save it in the RTOS structure for later notifying this task
	socket->rtos.task = xTaskGetCurrentTaskHandle();

	while (!socket->exit) {

		// TODO: this is now waiting only for receiving a notification, but maybe we want to do other things
		uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if (ulNotificationValue) {
			socket->rx_function();
		}

	}
	vTaskDelete(socket->rtos.task);
}

/* ============================================================================= */
void core_comm_SerialSocket_rx_notify(void *argument, void *SerialSocket) {
	core_comm_UartInterface *socket = (core_comm_UartInterface*) SerialSocket;
	if (socket->rtos.task != NULL) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(socket->rtos.task, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

#endif
