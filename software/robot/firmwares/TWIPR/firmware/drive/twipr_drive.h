/*
 * twipr_drive.h
 *
 *  Created on: 22 Feb 2023
 *      Author: Dustin Lehmann
 */

#ifndef DRIVE_TWIPR_DRIVE_H_
#define DRIVE_TWIPR_DRIVE_H_

#include "core.h"
#include "simplexmotion.hpp"

typedef enum twipr_drive_status {
	TWIPR_DRIVE_STATUS_IDLE,
	TWIPR_DRIVE_STATUS_RUNNING,
	TWIPR_DRIVE_STATUS_ERROR,
} twipr_drive_status;

typedef struct twipr_drive_input {
	float torque_left;
	float torque_right;
} twipr_drive_input;

typedef struct twipr_drive_config {
	uint8_t id_left;
	uint8_t id_right;
	float torque_max;
} twipr_drive_config;

class TWIPR_Drive {
public:
	TWIPR_Drive();
	void init(twipr_drive_config config);
	void start();

	void stop();


	void check();

	void setInput(twipr_drive_input input);

	twipr_drive_status status;
private:
	SimplexMotionMotor motor_left;
	SimplexMotionMotor motor_right;

	twipr_drive_input _last_input;

};

#endif /* DRIVE_TWIPR_DRIVE_H_ */
