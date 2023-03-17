/*
 * twipr_communication.h
 *
 *  Created on: 12 Mar 2023
 *      Author: Dustin Lehmann
 */

#ifndef COMMUNICATION_TWIPR_COMMUNICATION_H_
#define COMMUNICATION_TWIPR_COMMUNICATION_H_

#include "twipr_uart_communication.h"
#include "twipr_spi_communication.h"
#include "firmware_defs.h"

#define TWIPR_COMM_ERROR_FLAG_UNKNOWN 0x01
#define TWIPR_COMM_ERROR_FLAG_WRONG_ADDRESS 0x02
#define TWIPR_COMM_ERROR_FLAG_WRITE 0x03
#define TWIPR_COMM_ERROR_FLAG_READ 0x04
#define TWIPR_COMM_ERROR_FLAG_LEN 0x05
#define TWIPR_COMM_ERROR_FLAG_MSG_TYPE 0x06

typedef enum twipr_communication_callback_id_t {
	TWIPR_COMM_CALLBACK_NEW_TRAJECTORY,
} twipr_communication_callback_id_t;

typedef struct twipr_communication_callbacks_t {
	core_utils_Callback<void, uint16_t> new_trajectory;
}twipr_communication_callbacks_t;

typedef struct twipr_communication_config_t {
	UART_HandleTypeDef *huart;
	SPI_HandleTypeDef *hspi;
	core_utils_GPIO notification_gpio;
	RegisterMap *reg_map_control;
	RegisterMap *reg_map_general;
	twipr_logging_sample_t *sample_tx_buffer;
	uint16_t len_sample_buffer;
	twipr_control_trajectory_input_t *trajectory_rx_buffer;
	uint16_t len_trajectory_buffer;
} twipr_communication_config_t;

class TWIPR_CommunicationManager {
public:
	TWIPR_CommunicationManager();

	void init(twipr_communication_config_t config);
	void start();


	void registerCallback(twipr_communication_callback_id_t callback_id, core_utils_Callback<void, uint16_t> callback);

	void sampleBufferFull();

	twipr_communication_config_t config;
	TWIPR_UART_Communication uart_interface;
	TWIPR_SPI_Communication spi_interface;
private:

	twipr_communication_callbacks_t _callbacks;

	void _uart_handleMsg_write_callback(core_comm_SerialMessage *msg);
	void _uart_handleMsg_read_callback(core_comm_SerialMessage *msg);
	void _uart_handleMsg_func_callback(core_comm_SerialMessage *msg);

	void _spi_rxTrajectory_callback(uint16_t len);
	void _spi_txSamples_callback(uint16_t len);

	void _uartResponseError(core_comm_SerialMessage *incoming_message,
			uint8_t error_code);

};

#endif /* COMMUNICATION_TWIPR_COMMUNICATION_H_ */
