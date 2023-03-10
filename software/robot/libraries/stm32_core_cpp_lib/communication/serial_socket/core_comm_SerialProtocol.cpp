/*
 * serial_protocol.cpp
 *
 *  Created on: 8 Jul 2022
 *      Author: Dustin Lehmann
 */

#include "core_comm_SerialProtocol.h"

void core_comm_SerialMessage::copyTo(core_comm_SerialMessage *msg) {
	msg->address_1 = this->address_1;
	msg->address_2 = this->address_2;
	msg->address_3 = this->address_3;
	msg->cmd = this->cmd;
	msg->len = this->len;

	for (int i = 0; i < len; i++) {
		msg->data[i] = this->data[i];
	}
}

uint8_t core_comm_SerialMessage::encode(uint8_t *buffer) {
	buffer[0] = CORE_SERIAL_MESSAGE_HEADER;
	buffer[1] = this->cmd;
	buffer[2] = this->address_1;
	buffer[3] = this->address_2;
	buffer[4] = this->address_3;
	buffer[5] = this->flag;
	buffer[6] = this->len >> 8;
	buffer[7] = this->len & 0xFF;

	for (uint8_t i = 0; i < this->len; i++) {
		buffer[8 + i] = this->data[i];
	}
	buffer[8 + this->len] = 0; // CRC8
	return this->protocol_overhead + this->len;
}

void core_comm_SerialMessage::encode(core_utils_Buffer *buffer) {
	buffer->buffer[0] = CORE_SERIAL_MESSAGE_HEADER;
	buffer->buffer[1] = this->cmd;
	buffer->buffer[2] = this->address_1;
	buffer->buffer[3] = this->address_2;
	buffer->buffer[4] = this->address_3;
	buffer->buffer[5] = this->flag;

	buffer->buffer[6] = this->len >> 8;
	buffer->buffer[7] = this->len & 0xFF;

	for (uint8_t i = 0; i < this->len; i++) {
		buffer->buffer[8 + i] = this->data[i];
	}
	buffer->buffer[8 + this->len] = 0; // CRC8
	buffer->len = this->len;
}

uint8_t core_comm_SerialMessage::check(uint8_t *buffer, uint16_t len) {

	if (len < this->protocol_overhead) {
		return CORE_ERROR;
	}

	/* Check for the header */
	if (!(buffer[0] == CORE_SERIAL_MESSAGE_HEADER)) {
		return CORE_ERROR;
	}

//	if (!(buffer[len - 1] == CORE_SERIAL_MESSAGE_FOOTER)) {
//		return CORE_ERROR;
//	}

	/* Extract the data length */
	// Check if the data length matches with the length of the message
	uint8_t data_len = buffer[6];
	if ((len - data_len) == this->protocol_overhead) {
	} else {
		return CORE_ERROR;
	}

	return CORE_OK;

}
uint8_t core_comm_SerialMessage::check(core_utils_Buffer *buffer) {
	return this->check(buffer->buffer, buffer->len);
}

uint8_t core_comm_SerialMessage::decode(uint8_t *buffer, uint16_t len) {
	if (this->check(buffer, len) == CORE_ERROR) {
		return CORE_ERROR;
	}

	/* Extract the command */
	this->cmd = buffer[1];

	/* Extract the address */
	this->address_1 = buffer[2];
	this->address_2 = buffer[3];
	this->address_3 = buffer[4];

	/* Flag */
	this->flag = buffer[5];

	/* Extract the data length */
	this->len = uint8_to_uint16(buffer[6], buffer[7]);

	/* Extract the data */
	for (uint8_t i = 0; i < this->len; i++) {
		this->data[i] = buffer[i + 8];
	}

	return CORE_OK;
}

uint8_t core_comm_SerialMessage::decode(core_utils_Buffer *buffer) {
	return this->decode(buffer->buffer, buffer->len);
}

