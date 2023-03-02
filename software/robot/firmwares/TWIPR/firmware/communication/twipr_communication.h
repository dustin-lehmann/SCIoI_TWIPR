/*
 * twipr_communication.h
 *
 *  Created on: Feb 22, 2023
 *      Author: lehmann_workstation
 */

#ifndef COMMUNICATION_TWIPR_COMMUNICATION_H_
#define COMMUNICATION_TWIPR_COMMUNICATION_H_

#include "core.h"

#define MSG_COMMAND_WRITE 0x01
#define MSG_COMMAND_READ 0x02
#define MSG_COMMAND_ANSWER 0x03
#define MSG_COMMAND_STREAM 0x04
#define MSG_COMMAND_EVENT 0x05
#define MSG_COMMAND_MSG 0x06
#define MSG_COMMAND_FCT 0x07
#define MSG_COMMAND_ECHO 0x08

typedef struct twipr_comm_config_t {
	UART_HandleTypeDef *huart;
} twipr_comm_config_t;

typedef struct twipr_comm_filter_t {
	uint8_t address1;
	uint8_t address2;
	core_utils_Callback callback;
} twipr_comm_filter_t;

class TWIPR_Communication {
public:
	TWIPR_Communication();

	void init(twipr_comm_config_t config);
	void start();

	void send(core_comm_SerialMessage msg);
	void send(core_comm_SerialMessage *msg);
	void send(uint8_t cmd, uint8_t module, uint16_t address, uint8_t flag, uint8_t* data, uint8_t len);
	void sendRaw(uint8_t* buffer, uint16_t len);





	void task_loop();


	osThreadId_t thread;
	xTaskHandle task;

private:

	void _handleIncomingMessages();
	void _handleMessage_read(core_comm_SerialMessage* msg);

	core_comm_UartInterface uart_cm4;
	core_utils_RegisterMap *register_map;
};

void twipr_comm_task(void *argument);
void uart_cm4_rx_callback(void *argument, void *parameters);

#endif /* COMMUNICATION_TWIPR_COMMUNICATION_H_ */
