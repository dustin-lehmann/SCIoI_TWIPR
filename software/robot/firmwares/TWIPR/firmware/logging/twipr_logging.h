/*
 * twipr_logging.h
 *
 *  Created on: Mar 7, 2023
 *      Author: lehmann_workstation
 */

#ifndef LOGGING_TWIPR_LOGGING_H_
#define LOGGING_TWIPR_LOGGING_H_

#include "twipr_estimation.h"
#include "twipr_sensors.h"
#include "twipr_drive.h"
#include "twipr_control.h"

typedef struct twipr_logging_general_t {
	uint32_t tick;
} twipr_logging_general_t;

typedef struct twipr_logging_sample_t {
	twipr_logging_general_t general;
	twipr_logging_control_t control;
	twipr_logging_estimation_t estimation;
	twipr_logging_sensors_t sensors;
} twipr_logging_sample_t;

typedef struct twipr_logging_sample_small {

} twipr_logging_sample_small;


#endif /* LOGGING_TWIPR_LOGGING_H_ */
