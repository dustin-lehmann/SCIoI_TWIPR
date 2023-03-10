/*
 * twipr_errors.h
 *
 *  Created on: 4 Mar 2023
 *      Author: Dustin Lehmann
 */

#ifndef ERRORS_TWIPR_ERRORS_H_
#define ERRORS_TWIPR_ERRORS_H_

#include "core.h"
#include "robot-control_std.h"

extern UART_HandleTypeDef huart2;

#define ERROR_UART &huart2;

#define TWIPR_ERROR_UNKNOWN 0x0000
#define TWIPR_ERROR_INIT 0x0001
#define TWIPR_ERROR_HARDFAULT 0x0002



void twipr_error_handler(uint32_t errorcode);
void twipr_error_handler(uint32_t errorcode, uint8_t *data, uint16_t len);

#endif /* ERRORS_TWIPR_ERRORS_H_ */
