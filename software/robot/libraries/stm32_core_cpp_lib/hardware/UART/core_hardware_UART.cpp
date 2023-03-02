/*
 * core_hardware_UART.cpp
 *
 *  Created on: Jul 7, 2022
 *      Author: Dustin Lehmann
 */

#include "core_hardware_UART.h"

#if CORE_CONFIG_USE_UART

core_hardware_UART *uarts[CORE_CONFIG_MAX_UARTS];
uint8_t num_uarts = 0;

core_hardware_UART_config core_hardware_uart_std_config = { .mode =
		CORE_HARDWARE_UART_MODE_DMA, .cobs_encode_rx = 1, .cobs_encode_tx = 1,
		.queues = 1, };

void uartRxCmpltDMA_callback(UART_HandleTypeDef *huart, uint16_t size);

/* ============================================================================= */
core_hardware_UART::core_hardware_UART() {

}

/* ============================================================================= */
void core_hardware_UART::init(UART_HandleTypeDef *huart) {
	this->init(huart, core_hardware_uart_std_config);
}
/* ============================================================================= */
void core_hardware_UART::init(UART_HandleTypeDef *huart,
		core_hardware_UART_config config) {

	uarts[num_uarts] = this;
	num_uarts++;
	this->huart = huart;

	this->config = config;
	if (this->huart == NULL) {
		core_ErrorHandler(1);
	}

//	HAL_UART_RegisterCallback(this->huart, HAL_UART_RX_COMPLETE_CB_ID, uartRxCmpltDMA_callback);
	HAL_UART_RegisterRxEventCallback(this->huart, uartRxCmpltDMA_callback);
	__HAL_DMA_DISABLE_IT(this->huart->hdmarx, DMA_IT_HT);

	this->state = CORE_HARDWARE_UART_STATE_INIT;
}

/* ============================================================================= */
int8_t core_hardware_UART::available() {
	return this->rx_queue.available();
}
/* ============================================================================= */
void core_hardware_UART::start() {
	if (this->state != CORE_HARDWARE_UART_STATE_INIT) {
		core_ErrorHandler(2);
	}

	if (this->config.mode == CORE_HARDWARE_UART_MODE_DMA) {
		this->startReceiveDMA();
	} else {
		core_ErrorHandler(3);
	}
	this->state = CORE_HARDWARE_UART_STATE_RUN;
}

/* ============================================================================= */
void core_hardware_UART::startReceiveDMA() {
	if (this->config.queues) {
//		this->writeBuffer = this->rx_queue.getWritePointer();
		HAL_UARTEx_ReceiveToIdle_DMA(this->huart, &this->rx_buffer.buffer[0],
		CORE_CONFIG_UART_RX_BUF_SIZE);
		__HAL_DMA_DISABLE_IT(this->huart->hdmarx, DMA_IT_HT);
	} else {
		core_ErrorHandler(CORE_ERROR_NOT_IMPLEMENTED);
	}

}

/* ============================================================================= */
void core_hardware_UART::registerCallback(core_hardware_UART_CB_ID callback_id,
		void (*callback)(void *argument, void *params), void *params) {

	if (callback_id == CORE_HARDWARE_UART_CB_RX) {
		this->rx_callback.callback = callback;
		this->rx_callback.params = params;
		this->rx_callback.registered = 1;
	}
}
/* ============================================================================= */
void uartRxCmpltDMA_callback(UART_HandleTypeDef *huart, uint16_t size) {
	for (int i = 0; i < num_uarts; i++) {
		if (!(uarts[i] == NULL) && (uarts[i]->huart == huart)) {
			uarts[i]->rxFunction(size);
		}
	}
}

/* ============================================================================= */
void core_hardware_UART::rxFunction(uint16_t len) {
	if (len == 0) {
		return;
	}

	if (this->config.cobs_encode_rx) {
		len = cobsDecodeInPlace(this->rx_buffer.buffer, len - 1);
	}

	this->rx_buffer.len = len;
	if (this->config.queues) {
		this->rx_queue.write(&this->rx_buffer);
	}

	if (this->rx_callback.registered) {
		this->rx_callback.call((void*) &this->rx_buffer);
	}

	this->startReceiveDMA();
}
/* ============================================================================= */
void core_hardware_UART::send(uint8_t *data, uint8_t len) {

	if (this->state != CORE_HARDWARE_UART_STATE_RUN) {
		core_ErrorHandler(4);
	}

	if (this->config.mode != CORE_HARDWARE_UART_MODE_DMA
			&& this->config.queues != 1) {
		// TODO Not implemented yet
		core_ErrorHandler(5);
	}

	if (this->config.cobs_encode_tx) {
		uint8_t len_encode = cobsEncode(data, len, this->tx_buffer.buffer);
		this->tx_buffer.buffer[len_encode] = 0x00;
		this->tx_buffer.len = len_encode + 1;
		this->tx_queue.write(&this->tx_buffer);
	} else {
		this->tx_queue.write(data, (uint8_t) len);
	}
	this->flushTx();
}

/* ============================================================================= */
void core_hardware_UART::sendRaw(uint8_t *data, uint8_t len) {
	if (this->state != CORE_HARDWARE_UART_STATE_RUN) {
		core_ErrorHandler(4);
	}

	if (this->config.mode != CORE_HARDWARE_UART_MODE_DMA
			&& this->config.queues != 1) {
		// TODO Not implemented yet
		core_ErrorHandler(5);
	}

	this->tx_queue.write(data, (uint8_t) len);
	this->flushTx();

}

/* ============================================================================= */
void core_hardware_UART::flushTx() {
	while (!(this->huart->gState == HAL_UART_STATE_READY)) {

	}
	this->sendNextBuffer();
}

/* ============================================================================= */
void core_hardware_UART::sendNextBuffer() {
	// Check if there is a message pending in the tx buffer
	if (!this->tx_queue.available()) {
		return;
	}

	if (this->huart->gState != HAL_UART_STATE_READY) {
		return;
	}

	uint8_t *buffer = NULL;
	uint8_t len = this->tx_queue.read(&buffer);
	HAL_UART_Transmit_DMA(this->huart, buffer, len);
}

#endif
