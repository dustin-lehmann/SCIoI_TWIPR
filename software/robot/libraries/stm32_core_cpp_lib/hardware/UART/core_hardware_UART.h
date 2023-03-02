/*
 * core_hardware_UART.h
 *
 *  Created on: Jul 7, 2022
 *      Author: Dustin Lehmann
 */

#ifndef CORE_HARDWARE_UART_CORE_HARDWARE_UART_H_
#define CORE_HARDWARE_UART_CORE_HARDWARE_UART_H_


#include "../../core_includes.h"
#include "../../utils/core_utils.h"

#if CORE_CONFIG_USE_UART

enum core_hardware_UART_CB_ID {
	CORE_HARDWARE_UART_CB_RX
};

enum core_hardware_UART_state {
	CORE_HARDWARE_UART_STATE_NONE,
	CORE_HARDWARE_UART_STATE_INIT,
	CORE_HARDWARE_UART_STATE_RUN,
	CORE_HARDWARE_UART_STATE_ERROR,
};

enum core_hardware_UART_mode {
	CORE_HARDWARE_UART_MODE_POLL,
	CORE_HARDWARE_UART_MODE_IT,
	CORE_HARDWARE_UART_MODE_DMA,
};

typedef struct core_hardware_UART_config {
	core_hardware_UART_mode mode = CORE_HARDWARE_UART_MODE_DMA;
	uint8_t cobs_encode_rx = 1;
	uint8_t cobs_encode_tx = 1;
	uint8_t queues = 1;
} core_hardware_UART_config;

class core_hardware_UART {
public:

	core_hardware_UART();

	void init(UART_HandleTypeDef *huart);
	void init(UART_HandleTypeDef *huart, core_hardware_UART_config config);
	void start();
//	void stop();

	void send(uint8_t *data, uint8_t len);
	void sendRaw(uint8_t *data, uint8_t len);
	void sendBlocking();

	int8_t available();

	void startReceiveDMA();

	void rxFunction(uint16_t len);

	void registerCallback(core_hardware_UART_CB_ID callback_id,
			void (*callback)(void *argument, void *params), void *params);

	core_hardware_UART_config config;

	core_utils_BufferQueue<10> rx_queue;
	core_utils_BufferQueue<10> tx_queue;
	UART_HandleTypeDef *huart;

	core_hardware_UART_state state = CORE_HARDWARE_UART_STATE_NONE;

	core_utils_Buffer rx_buffer;
	core_utils_Buffer tx_buffer;

private:

	uint8_t rx_encode_buffer[CORE_CONFIG_UART_RX_BUF_SIZE + 10];
	uint8_t tx_encode_buffer[CORE_CONFIG_UART_TX_BUF_SIZE + 10];

	core_utils_Callback rx_callback;

	void flushTx();
	void sendNextBuffer();
};
#endif
#endif /* CORE_HARDWARE_UART_CORE_HARDWARE_UART_H_ */
