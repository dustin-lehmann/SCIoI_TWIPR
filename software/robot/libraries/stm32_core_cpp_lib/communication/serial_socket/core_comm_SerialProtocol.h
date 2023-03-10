/*
 * serial_protocol.h
 *
 *  Created on: 8 Jul 2022
 *      Author: Dustin Lehmann
 */

#ifndef CORE_COMMUNICATION_SERIAL_SOCKET_CORE_COMM_SERIALPROTOCOL_H_
#define CORE_COMMUNICATION_SERIAL_SOCKET_CORE_COMM_SERIALPROTOCOL_H_

#include "stdint.h"

#include "../../core_includes.h"
#include "../../utils/core_utils.h"

#define CORE_SERIAL_MESSAGE_HEADER 0x55

class core_comm_SerialMessage {
public:
	uint8_t cmd;
	uint8_t address_1;
	uint8_t address_2;
	uint8_t address_3;
	uint8_t flag;
	uint8_t data[CORE_CONFIG_MAX_MSG_LENGTH];
	uint16_t len;


	void copyTo(core_comm_SerialMessage *msg);
	uint8_t check(uint8_t *buffer, uint16_t len);
	uint8_t check(core_utils_Buffer *buffer);
	uint8_t encode(uint8_t *buffer);
	void encode(core_utils_Buffer *buffer);
	uint8_t decode(uint8_t *buffer, uint16_t len);
	uint8_t decode(core_utils_Buffer *buffer);
private:
	static const uint8_t protocol_overhead = 8;
};

#endif /* CORE_COMMUNICATION_SERIAL_SOCKET_CORE_COMM_SERIALPROTOCOL_H_ */
