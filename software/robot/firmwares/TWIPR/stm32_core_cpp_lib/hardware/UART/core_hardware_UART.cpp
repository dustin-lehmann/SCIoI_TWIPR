/*
 * core_hardware_UART.cpp
 *
 *  Created on: Jul 7, 2022
 *      Author: Dustin Lehmann
 */

#include "core_hardware_UART.h"

#if CORE_CONFIG_USE_UART


UART *uarts[CORE_CONFIG_MAX_UARTS];
uint8_t num_uarts = 0;

core_hardware_UART_config core_hardware_uart_std_config = { .mode =
		CORE_HARDWARE_UART_MODE_DMA, .cobs_encode_rx = 1, .cobs_encode_tx = 1,
		.queues = 1, };


/* ============================================================================= */
void uartRxCmpltDMA_callback(UART_HandleTypeDef *huart, uint16_t size) {
	for (int i = 0; i < num_uarts; i++) {
		if (!(uarts[i] == NULL) && (uarts[i]->get_huart() == huart)) {
			uarts[i]->rxFunction(size);
		}
	}
}

#endif
