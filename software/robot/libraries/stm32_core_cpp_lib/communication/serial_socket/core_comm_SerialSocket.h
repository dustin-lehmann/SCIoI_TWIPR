/*
 * serial_socket.h
 *
 *  Created on: 8 Jul 2022
 *      Author: Dustin Lehmann
 */

#ifndef CORE_COMMUNICATION_SERIAL_SOCKET_H_
#define CORE_COMMUNICATION_SERIAL_SOCKET_H_

#include "../../core_includes.h"

#include "core_comm_MessageQueue.h"
#include "core_comm_SerialProtocol.h"
#include "../../hardware/UART/core_hardware_UART.h"

#if CORE_CONFIG_USE_UART && CORE_CONFIG_USE_RTOS


#define CORE_COMM_SERIAL_SOCKET_RTOS_RX_STACKSIZE 512*4
#define CORE_COMM_SERIAL_SOCKET_RTOS_RX_PRIORITY osPriorityHigh

/* ---------------------------------------------------------- */
enum core_comm_SerialSocket_CB_ID {
	CORE_COMM_SERIAL_SOCKET_CB_RX,
	CORE_COMM_SERIAL_SOCKET_CB_ERROR
};

/* ---------------------------------------------------------- */
enum core_comm_SerialSocket_state {
	CORE_COMM_SERIAL_SOCKET_STATE_NONE,
	CORE_COMM_SERIAL_SOCKET_STATE_INIT,
	CORE_COMM_SERIAL_SOCKET_STATE_RUN,
	CORE_COMM_SERIAL_SOCKET_STATE_ERROR
};

/* ---------------------------------------------------------- */
enum core_comm_SerialSocket_rx_callback_value {
	CORE_COMM_SERIAL_SOCKET_RX_CB_BUF = 0,
	CORE_COMM_SERIAL_SOCKET_RX_CB_MSG = 1,
	CORE_COMM_SERIAL_SOCKET_RX_CB_IFC = 2, // Return the interface itself
};

/* ---------------------------------------------------------- */
typedef struct core_comm_SerialSocket_callbacks {
	core_utils_Callback rx;
} core_comm_SerialSocket_callbacks;

/* ---------------------------------------------------------- */
struct core_comm_UartInterface_config {
	core_hardware_UART_config uart;
	uint8_t use_rtos;
	uint8_t use_protocol;
	uint8_t use_queue;
	core_comm_SerialSocket_rx_callback_value rx_callback_value;
};

/* ---------------------------------------------------------- */
typedef struct core_comm_SerialSocket_RTOS {
	osThreadId_t threadId = NULL;
	TaskHandle_t task = NULL;
} core_comm_SerialSocket_RTOS;

/* ---------------------------------------------------------- */
class core_comm_UartInterface {
public:

	core_comm_UartInterface();

	void init(UART_HandleTypeDef *huart);
	void init(UART_HandleTypeDef *huart, core_comm_UartInterface_config config);
	void start();

	void send(core_comm_SerialMessage *message);
	void send(uint8_t *buffer, uint8_t len);
	void sendRaw(uint8_t *buffer, uint8_t len);

	core_comm_SerialMessage getMessage();
	core_comm_SerialMessage* getMessagePointer();

	void registerCallback(core_comm_SerialSocket_CB_ID callback_id,
			void (*callback)(void *argument, void *params), void *params);

	uint8_t rx_function();



	core_comm_UartInterface_config config;

	core_comm_MessageQueue<CORE_CONFIG_MSG_QUEUE_SIZE> rx_queue;
	core_comm_SerialSocket_state state;

	core_comm_SerialSocket_RTOS rtos;


	uint8_t exit = 0;
private:
	void startRTOS();
	core_comm_SerialMessage rx_message;
	core_hardware_UART uart;
	uint8_t tx_buf[CORE_CONFIG_MAX_MSG_LENGTH];
	core_comm_SerialSocket_callbacks callbacks;

};

void core_comm_SerialSocket_rx_notify(void *argument, void *SerialSocket);
void core_comm_SerialSocket_RTOS_Task(void *SerialSocket);

#endif
#endif /* CORE_COMMUNICATION_SERIAL_SOCKET_H_ */
