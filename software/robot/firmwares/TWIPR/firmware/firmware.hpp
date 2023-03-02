/*
 * firmware.hpp
 *
 *  Created on: Feb 13, 2023
 *      Author: lehmann_workstation
 */

#ifndef FIRMWARE_HPP_
#define FIRMWARE_HPP_

#include "robot-control_std.h"
#include "simplexmotion.hpp"
#include "twipr_control.h"
#include "twipr_estimation.h"
#include "twipr_communication.h"

typedef enum twipr_firmware_state_t {
	TWIPR_FIRMWARE_STATE_ERROR = -1,
	TWIPR_FIRMWARE_STATE_IDLE = 0,
	TWIPR_FIRMWARE_STATE_RUNNING = 1,
	TWIPR_FIRMWARE_STATE_RESET = 2,
	TWIPR_FIRMWARE_STATE_TIMEOUT = 3,
} twipr_firmware_state_t;

class TWIPR_Firmware {

public:
	TWIPR_Firmware();
	void init();
	void start();


	void reset();

	xTaskHandle task;
	osThreadId_t thread;
private:
//	TWIPR_Control controller;
//	TWIPR_Estimation estimation;
	TWIPR_Communication comm;
};

void firmware_task(void *argument);

#endif /* FIRMWARE_HPP_ */
