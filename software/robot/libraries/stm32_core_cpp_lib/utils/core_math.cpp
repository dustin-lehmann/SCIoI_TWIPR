/*
 * math.cpp
 *
 *  Created on: 7 Jul 2022
 *      Author: Dustin Lehmann
 */

#include "core_math.h"

float mean(float *data, uint16_t len) {
	float sum = 0;

	for (uint16_t i = 0; i < len; i++) {
		sum += data[i];
	}

	return sum / len;
}
