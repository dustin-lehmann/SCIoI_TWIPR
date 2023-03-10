/*
 * firmware.hpp
 *
 *  Created on: Feb 13, 2023
 *      Author: lehmann_workstation
 */

#ifndef FIRMWARE_HPP_
#define FIRMWARE_HPP_

#include "twipr_control.h"
#include "robot-control_std.h"
#include "simplexmotion.hpp"
#include "twipr_estimation.h"
#include "twipr_communication.h"
#include "twipr_errors.h"
#include "twipr_logging.h"

typedef enum twipr_firmware_error_t {
	TWIPR_FIRMWARE_ERROR_NONE = 0,
	TWIPR_FIRMWARE_ERROR_TIMEOUT = 1,
} twipr_firmware_error_t;

typedef enum twipr_firmware_state_t {
	TWIPR_FIRMWARE_STATE_ERROR = -1,
	TWIPR_FIRMWARE_STATE_IDLE = 0,
	TWIPR_FIRMWARE_STATE_RUNNING = 1,
	TWIPR_FIRMWARE_STATE_RESET = 2,
} twipr_firmware_state_t;

typedef struct twipr_firmware_register_entries_t {
	core_utils_RegisterEntry<twipr_firmware_state_t> firmware_state;
} twipr_firmware_register_entries_t;

class TWIPR_Firmware {

public:
	TWIPR_Firmware();
	void init();
	void start();
	void step();

	void reset();



	core_utils_RegisterMap<128> register_map;
	twipr_firmware_register_entries_t reg_entries;


	twipr_firmware_state_t firmware_state = TWIPR_FIRMWARE_STATE_RESET;
	twipr_firmware_error_t firmware_error = TWIPR_FIRMWARE_ERROR_NONE;

	xTaskHandle task;
	osThreadId_t thread;
private:
//	TWIPR_Control controller;
//	TWIPR_Estimation estimation;
	TWIPR_Communication comm;

	uint32_t tick;
};

void firmware_task(void *argument);

#endif /* FIRMWARE_HPP_ */
