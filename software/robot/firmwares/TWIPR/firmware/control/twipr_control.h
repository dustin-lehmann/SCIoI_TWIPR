/*
 * twipr_control.h
 *
 *  Created on: 3 Mar 2023
 *      Author: lehmann_workstation
 */

#ifndef CONTROL_TWIPR_CONTROL_H_
#define CONTROL_TWIPR_CONTROL_H_

#include "firmware_settings.h"
#include "twipr_balancing_control.h"
#include "twipr_drive.h"

typedef struct twipr_control_config_t {
	TWIPR_Estimation *estimation;
	TWIPR_Drive *drive;
	float K[2][4];
} twipr_control_config_t;

typedef struct twipr_control_trajectory_input_t {
	uint32_t step;
	float u_1;
	float u_2;
} twipr_control_trajectory_input_t;

typedef struct twipr_control_trajectory_t {
	uint32_t step;
	uint32_t length;
} twipr_control_trajectory_t;

typedef enum twipr_control_mode_t {
	TWIPR_CONTROL_MODE_OFF = 0,
	TWIPR_CONTROL_MODE_DIRECT = 1,
	TWIPR_CONTROL_MODE_BALANCING = 2,
	TWIPR_CONTROL_MODE_TRAJECTORY = 3,
};

typedef enum twipr_control_status_t {
	TWIPR_CONTROL_STATUS_ERROR = -1,
	TWIPR_CONTROL_STATUS_OFF = 0,
	TWIPR_CONTROL_STATUS_RUNNING = 1,
} twipr_control_status_t;

typedef struct twipr_control_input_t {
	float u_1;
	float u_2;
} twipr_control_input_t;

typedef struct twipr_control_output_t {
	float u_left;
	float u_right;
} twipr_control_output_t;

class TWIPR_ControlManager {

public:
	TWIPR_ControlManager();

	void init(twipr_control_config_t config);
	uint8_t start();

	void stop();
	void reset();

	void step();

	void setMode(twipr_control_mode_t mode);
	twipr_control_status_t getStatus();

	void setInput(twipr_control_input_t input);
	void startTrajectory(uint16_t length);

	twipr_control_status_t control_status = TWIPR_CONTROL_STATUS_OFF;
	twipr_control_mode_t control_mode = TWIPR_CONTROL_MODE_OFF;

	twipr_control_config_t config;
private:
	TWIPR_BalancingControl balancing_control;

	twipr_control_input_t _input;
	twipr_control_trajectory_input_t _trajectory_buffer[TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE];
	twipr_control_trajectory_input_t _trajectory_rx_buffer[TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE];



	twipr_control_trajectory_t _trajectory;

	twipr_control_input_t _last_input;
	twipr_estimation_state_t _dynamic_state;
	twipr_estimation_state_t _last_dynamic_state;

	TWIPR_Estimation *estimation;
	TWIPR_Drive *drive;

	void _controlStep();
	void _trajectoryStep();
	void _trajectoryFinished();
	void _setTorque(twipr_control_output_t output);
};

#endif /* CONTROL_TWIPR_CONTROL_H_ */
