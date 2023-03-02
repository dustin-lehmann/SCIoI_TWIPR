/*
 * bytes.cpp
 *
 *  Created on: 7 Jul 2022
 *      Author: Dustin Lehmann
 */

#include "core_bytes.h"

float bytearray_to_float(uint8_t *bytearray) {
	uint32_t temp = 0;
	temp = ((bytearray[3] << 24) | (bytearray[2] << 16) | (bytearray[1] << 8)
			| bytearray[0]);
	return *((float*) &temp);
}

uint16_t bytearray_to_uint16(uint8_t *bytearray) {
	uint16_t out = bytearray[1] << 8 | bytearray[0];
	return out;
}

int16_t bytearray_to_int16(uint8_t *bytearray) {
	int16_t out = bytearray[1] << 8 | bytearray[0];
	return out;
}

//int16_t bytearray_to_int16(uint8_t *bytearray) {
//	int16_t out = bytearray[0] << 8 | bytearray[1];
//	return out;
//}

int16_t bytearray_to_uint32(uint8_t *bytearray) {
	uint32_t temp = 0;
	temp = ((bytearray[3] << 24) | (bytearray[2] << 16) | (bytearray[1] << 8)
			| bytearray[0]);
	return temp;
}


void float_to_bytearray(float value, uint8_t* bytearray) {
    uint32_t l = *(uint32_t*) &value;

    bytearray[0] = l & 0x00FF;
    bytearray[1] = (l >> 8) & 0x00FF;
    bytearray[2] = (l >> 16) & 0x00FF;
    bytearray[3] = l >> 24;
}
