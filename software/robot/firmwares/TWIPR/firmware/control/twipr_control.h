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
#include "core.h"
#include "firmware_defs.h"

extern float twipr_control_default_K[8];

typedef struct twipr_control_config_t {
	TWIPR_Estimation *estimation;
	TWIPR_Drive *drive;
	float K[8];
	float max_torque;
	uint32_t freq;
} twipr_control_config_t;

typedef struct twipr_control_trajectory_input_t {
	uint32_t step;
	float u_1;
	float u_2;
} twipr_control_trajectory_input_t;

typedef struct twipr_control_trajectory_t {
	uint16_t step;
	uint16_t trajectory_id;
	uint16_t length;
} twipr_control_trajectory_t;

typedef enum twipr_control_mode_t {
	TWIPR_CONTROL_MODE_OFF = 0,
	TWIPR_CONTROL_MODE_DIRECT = 1,
	TWIPR_CONTROL_MODE_BALANCING = 2,
	TWIPR_CONTROL_MODE_TRAJECTORY = 3,
} twipr_control_mode_t;

typedef enum twipr_control_status_t {
	TWIPR_CONTROL_STATUS_ERROR = -1,
	TWIPR_CONTROL_STATUS_IDLE = 0,
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

typedef enum twipr_control_callback_id_t {
	TWIPR_CONTROL_CALLBACK_ERROR,
	TWIPR_CONTROL_CALLBACK_TRAJECTORY_START,
	TWIPR_CONTROL_CALLBACK_TRAJECTORY_FINISHED,
	TWIPR_CONTROL_CALLBACK_STEP,
} twipr_control_callback_id_t;

typedef struct twipr_logging_control_t {
	twipr_control_status_t control_status;
	twipr_control_mode_t control_mode;
	twipr_control_input_t input;
	twipr_control_output_t output;
	uint32_t trajectory_step;
	uint16_t trajectory_id;
} twipr_logging_control_t;

typedef struct twipr_control_callbacks_t {
	core_utils_Callback<void, uint16_t> error;
	core_utils_Callback<void, uint16_t> trajectory_start;
	core_utils_Callback<void, uint16_t> trajectory_finished;
	core_utils_Callback<void, uint32_t> step;
} twipr_control_callbacks_t;


#define TWIPR_CONTROL_REG_ENTRY_EXT_INPUT 0x01
#define TWIPR_CONTROL_REG_ENTRY_STATUS 0x02
#define TWIPR_CONTROL_REG_ENTRY_MODE 0x03
#define TWIPR_CONTROL_REG_FUNCTION_SET_MODE 0x04
#define TWIPR_CONTROL_REG_FUNCTION_START_TRAJECTORY 0x05
#define TWIPR_CONTROL_REG_FUNCTION_STOP 0x06
#define TWIPR_CONTROL_REG_ENTRY_CONFIG 0x07
#define TWIPR_CONTROL_REG_FUNCTION_SET_K 0x08

typedef struct twipr_control_reg_entries_t {
	core_utils_RegisterFunction<void, twipr_control_input_t> reg_function_set_external_input;
	core_utils_RegisterEntry<twipr_control_status_t> reg_entry_status;
	core_utils_RegisterEntry<twipr_control_mode_t> reg_entry_mode;
	core_utils_RegisterFunction<uint8_t, twipr_control_mode_t> reg_function_set_mode;
	core_utils_RegisterFunction<uint8_t, twipr_control_trajectory_t> reg_function_start_trajectory;
	core_utils_RegisterFunction<void, void> reg_function_stop;
	core_utils_RegisterFunction<uint8_t, float[8]> reg_function_set_K;
	core_utils_RegisterEntry<twipr_control_config_t> reg_entry_config;
} twipr_control_reg_entries_t;

// TODO: Add function to set K

class TWIPR_ControlManager {

public:
	TWIPR_ControlManager();

	void init(twipr_control_config_t config);
	uint8_t start();

	void stop();
	void reset();

	void task_function();


	twipr_logging_control_t getSample();

	uint8_t setMode(twipr_control_mode_t mode);
	twipr_control_status_t getStatus();

	void setInput(twipr_control_input_t input);
	uint8_t startTrajectory(twipr_control_trajectory_t trajectory);
	uint8_t stopTrajectory();

	uint8_t setBalancingGain(float *K);


	void newTrajectoryReceived_callback(uint16_t);

	void registerCallback(twipr_control_callback_id_t callback_id,
			core_utils_Callback<void, uint16_t> callback);
	void registerCallback(twipr_control_callback_id_t callback_id,
			core_utils_Callback<void, uint32_t> callback);

	twipr_control_status_t status = TWIPR_CONTROL_STATUS_IDLE;
	twipr_control_mode_t mode = TWIPR_CONTROL_MODE_OFF;

	twipr_control_config_t config;

	twipr_control_reg_entries_t reg_entries;
	core_utils_RegisterMap<20> reg_map = core_utils_RegisterMap<20>(
	TWIPR_FIRMWARE_REGISTER_MAP_CONTROL);


	twipr_control_trajectory_input_t trajectory_rx_buffer[TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE];

	void step();

private:
	TWIPR_BalancingControl _balancing_control;

	twipr_control_input_t _input;
	twipr_control_output_t _output;

	twipr_control_trajectory_input_t _trajectory_buffer[TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE];


	twipr_control_trajectory_t _trajectory;

//	twipr_control_input_t _last_input;
	twipr_estimation_state_t _dynamic_state;
//	twipr_estimation_state_t _last_dynamic_state;

	TWIPR_Estimation *_estimation;

	TaskHandle_t _task;
	twipr_control_callbacks_t _callbacks;
	uint32_t _tick;



	void _step_balancing();
	void _step_off();
	void _step_error();
	void _step_idle();
	void _step_trajectory();
	void _step_direct();


	float _sum_theta = 0;
	float _sum_v = 0;


	void _trajectoryFinished();
	void _setTorque(twipr_control_output_t output);
};

void twipr_control_task(void *control_manager);

#endif /* CONTROL_TWIPR_CONTROL_H_ */
