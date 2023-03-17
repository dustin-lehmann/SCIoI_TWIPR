/*
 * twipr_control.cpp
 *
 *  Created on: 3 Mar 2023
 *      Author: lehmann_workstation
 */

#include "twipr_control.h"

float twipr_control_default_K[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static const osThreadAttr_t control_task_attributes = { .name = "control",
		.stack_size = 512 * 4, .priority = (osPriority_t) osPriorityHigh, };

/* ======================================================== */
void twipr_control_task(void *argument) {
	TWIPR_ControlManager *control_manager = (TWIPR_ControlManager*) argument;
	control_manager->task_function();
}

/* ======================================================== */
TWIPR_ControlManager::TWIPR_ControlManager() {

}

/* ======================================================== */
void TWIPR_ControlManager::init(twipr_control_config_t config) {
	this->config = config;
	this->_estimation = config.estimation;

	// Initialize the balancing controller
	twipr_balancing_control_config_t balancing_control_config;
	memcpy(balancing_control_config.K, this->config.K,
			sizeof(balancing_control_config.K));
	this->_balancing_control.init(balancing_control_config);

	this->status = TWIPR_CONTROL_STATUS_IDLE;
	this->mode = TWIPR_CONTROL_MODE_OFF;
	this->_input.u_1 = 0;
	this->_input.u_2 = 0;
	this->_output.u_left = 0;
	this->_output.u_right = 0;
	this->_tick = 0;

	// Setting the Register Entries
	this->reg_entries.reg_entry_external_input.set(
	TWIPR_CONTROL_REG_ENTRY_EXT_INPUT, &this->reg_map, &this->_input,
			REGISTER_ENTRY_READWRITE);

	this->reg_entries.reg_entry_status.set(
	TWIPR_CONTROL_REG_ENTRY_STATUS, &this->reg_map, &this->status,
			REGISTER_ENTRY_READ);

	this->reg_entries.reg_entry_status.set(
	TWIPR_CONTROL_REG_ENTRY_MODE, &this->reg_map, &this->status,
			REGISTER_ENTRY_READ);

	this->reg_entries.reg_function_set_mode.set(
	TWIPR_CONTROL_REG_FUNCTION_SET_MODE, &this->reg_map,
			core_utils_Callback<uint8_t, twipr_control_mode_t>(this,
					&TWIPR_ControlManager::setMode));

	this->reg_entries.reg_function_start_trajectory.set(
	TWIPR_CONTROL_REG_FUNCTION_START_TRAJECTORY, &this->reg_map,
			core_utils_Callback<uint8_t, twipr_control_trajectory_t>(this,
					&TWIPR_ControlManager::startTrajectory));

	this->reg_entries.reg_function_stop.set(
	TWIPR_CONTROL_REG_FUNCTION_STOP, &this->reg_map,
			core_utils_Callback<void, void>(this, &TWIPR_ControlManager::stop));

	this->reg_entries.reg_entry_config.set(
	TWIPR_CONTROL_REG_ENTRY_CONFIG, &this->reg_map, &this->config,
			REGISTER_ENTRY_READ);

	this->reg_entries.reg_function_set_K.set(
	TWIPR_CONTROL_REG_FUNCTION_SET_K, &this->reg_map,
			core_utils_Callback<uint8_t, float*>(this,
					&TWIPR_ControlManager::setBalancingGain));
}
/* ======================================================== */
uint8_t TWIPR_ControlManager::start() {

	osThreadNew(twipr_control_task, (void*) this, &control_task_attributes);

	return 1;
}

/* ======================================================== */
void TWIPR_ControlManager::task_function() {
	this->_task = xTaskGetCurrentTaskHandle();
	uint32_t global_tick;

	while (true) {
		global_tick = osKernelGetTickCount();
		this->_step();
		osDelayUntil(global_tick + 1000.0 / (float) this->config.freq);
	}
}

/* ======================================================== */
void TWIPR_ControlManager::stop() {

	// Stop the balancing controller
	this->_balancing_control.stop();

	// Set the own state to idle
	this->status = TWIPR_CONTROL_STATUS_IDLE;
	this->mode = TWIPR_CONTROL_MODE_OFF;

	// Set the input to 0
	this->_input.u_1 = 0.0;
	this->_input.u_2 = 0.0;
	this->_output.u_left = 0.0;
	this->_output.u_right = 0.0;
}
/* ======================================================== */
void TWIPR_ControlManager::reset() {
	twipr_error_handler(0);
}

/* ======================================================== */
void TWIPR_ControlManager::newTrajectoryReceived_callback(uint16_t len) {
	// There is a new trajectory. Copy over to the trajectory buffer
	// TODO: This is only working if not in trajectory mode
	if (this->mode == TWIPR_CONTROL_MODE_TRAJECTORY) {
		return;
	}

	memcpy((uint8_t*) this->_trajectory_buffer,
			(uint8_t*) this->trajectory_rx_buffer,
			sizeof(twipr_control_trajectory_input_t)
					* TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE);
}
/* ======================================================== */
void TWIPR_ControlManager::_step() {

	// Read the state from the estimator
	this->_dynamic_state = this->_estimation->getState();

	// Check for errors
	// Drive
	// TODO

	switch (this->status) {
	case TWIPR_CONTROL_STATUS_ERROR: {
		this->_step_error();
		break;
	}
	case TWIPR_CONTROL_STATUS_IDLE: {
		this->_step_idle();
		break;
	}
	case TWIPR_CONTROL_STATUS_RUNNING: {
		switch (this->mode) {
		case TWIPR_CONTROL_MODE_OFF: {
			this->_step_off();
			break;
		}
		case TWIPR_CONTROL_MODE_DIRECT: {
			this->_step_direct();
			break;
		}
		case TWIPR_CONTROL_MODE_BALANCING: {
			this->_step_balancing();
			break;
		}
		case TWIPR_CONTROL_MODE_TRAJECTORY: {
			this->_step_trajectory();
			break;
		}
		}
		break;
	}
	}

	// Call the step callback
	if (this->_callbacks.step.registered) {
		this->_callbacks.step.call(this->_tick);
	}

	// Check for state transitions // TODO
	if (this->mode == TWIPR_CONTROL_MODE_TRAJECTORY) {
		//	 Check if the trajectory is finished
		if (this->_trajectory.step == this->_trajectory.length) {
			this->_trajectoryFinished();
		}
	}

}
/* ======================================================== */
uint8_t TWIPR_ControlManager::setMode(twipr_control_mode_t mode) {

	// Setting mode should only work while running
	if (this->status == TWIPR_CONTROL_STATUS_IDLE) {
		return 0;
	}
	if (this->status == TWIPR_CONTROL_STATUS_ERROR) {
		return 0;
	}

	if (mode == TWIPR_CONTROL_MODE_TRAJECTORY) {
		return 0;
	}

	this->mode = mode;

	// Switch the mode of the balancing controller to the appropriate mode
	switch (this->mode) {
	case TWIPR_CONTROL_MODE_OFF: {
		this->_balancing_control.setMode(TWIPR_BALANCING_CONTROL_MODE_OFF);
		break;
	}
	case TWIPR_CONTROL_MODE_DIRECT: {
		this->_balancing_control.setMode(TWIPR_BALANCING_CONTROL_MODE_DIRECT);
		break;
	}
	case TWIPR_CONTROL_MODE_BALANCING: {
		this->_balancing_control.setMode(TWIPR_BALANCING_CONTROL_MODE_ON);
		break;
	}
	case TWIPR_CONTROL_MODE_TRAJECTORY: {
		this->_balancing_control.setMode(TWIPR_BALANCING_CONTROL_MODE_ON);
		break;
	}
	}

	// Reset the input
	this->_input.u_1 = 0;
	this->_input.u_2 = 0;

	return 1;
}
/* ======================================================== */
void TWIPR_ControlManager::setInput(twipr_control_input_t input) {
// TODO: We need some input checking here
	if (this->status != TWIPR_CONTROL_STATUS_RUNNING) {
		return;
	}
	if (this->mode == TWIPR_CONTROL_MODE_OFF) {
		return;
	}
	this->_input = input;
}
/* ======================================================== */
twipr_control_status_t TWIPR_ControlManager::getStatus() {
	return this->status;
}

/* ======================================================== */
uint8_t TWIPR_ControlManager::setBalancingGain(float *K) {
	// This is only allowed if the controller is off
	if (this->status != TWIPR_CONTROL_STATUS_RUNNING) {
		return 0;
	}
	if (this->mode != TWIPR_CONTROL_MODE_OFF) {
		return 0;
	}

	memcpy(this->config.K, K, sizeof(float) * 8);
	this->_balancing_control.set_K(this->config.K);
	return 1;
}
/* ======================================================== */
uint8_t TWIPR_ControlManager::startTrajectory(
		twipr_control_trajectory_t trajectory) {

	if (this->status != TWIPR_CONTROL_STATUS_RUNNING) {
		return 0;
	}

	// This is only allowed when we are in balancing mode for now // TODO
	if (this->mode != TWIPR_CONTROL_MODE_BALANCING) {
		return 0;
	}

	this->_trajectory.step = trajectory.step;
	this->_trajectory.trajectory_id = trajectory.trajectory_id;
	this->_trajectory.length = trajectory.length;

	// Set the mode to trajectory
	this->mode = TWIPR_CONTROL_MODE_TRAJECTORY;

	return 1;
}
/* ======================================================== */
uint8_t TWIPR_ControlManager::stopTrajectory() {
	if (this->status != TWIPR_CONTROL_STATUS_RUNNING) {
		return 0;
	}
	if (this->mode != TWIPR_CONTROL_MODE_TRAJECTORY) {
		return 0;
	}

	// Set the mode back to balancing
	this->mode = TWIPR_CONTROL_MODE_BALANCING;

	// Set the input back to 0
	this->_input.u_1 = 0;
	this->_input.u_2 = 0;

	return 1;
}
/* ======================================================== */
void TWIPR_ControlManager::_step_off() {
	this->_input.u_1 = 0.0;
	this->_input.u_2 = 0.0;
	this->_output.u_left = 0.0;
	this->_output.u_right = 0.0;

	this->_setTorque(this->_output);
}
/* ======================================================== */
void TWIPR_ControlManager::_step_direct() {
	this->_output.u_left = limit(this->_input.u_1, this->config.max_torque);
	this->_output.u_right = limit(this->_input.u_2, this->config.max_torque);

	this->_setTorque(this->_output);
}
/* ======================================================== */
void TWIPR_ControlManager::_step_idle() {
	this->_input.u_1 = 0.0;
	this->_input.u_2 = 0.0;
	this->_output.u_left = 0.0;
	this->_output.u_right = 0.0;

	this->_setTorque(this->_output);
}
/* ======================================================== */
void TWIPR_ControlManager::_step_error() {
	this->_input.u_1 = 0.0;
	this->_input.u_2 = 0.0;
	this->_output.u_left = 0.0;
	this->_output.u_right = 0.0;

	this->_setTorque(this->_output);
}
/* ======================================================== */
void TWIPR_ControlManager::_step_balancing() {
	//	 Calculate the input from the balancing controller
	twipr_balancing_control_input_t balancing_input = { .u_1 = this->_input.u_1,
			.u_2 = this->_input.u_2 };

	twipr_balancing_control_output_t balancing_output;

	// Update the balancing controller
	this->_balancing_control.update(this->_dynamic_state, balancing_input,
			&balancing_output);

	this->_output.u_left = limit(balancing_output.u_1, this->config.max_torque);
	this->_output.u_right = limit(balancing_output.u_2,
			this->config.max_torque);

	// Drive the motors
	this->_setTorque(this->_output);
}
/* ======================================================== */
void TWIPR_ControlManager::_step_trajectory() {

	// Check if the step is correct
	if (this->_trajectory_buffer[this->_trajectory.step].step
			!= this->_trajectory.step) {
		// TODO
	}

	// Set the input from the current input of the buffer
	this->_input.u_1 = this->_trajectory_buffer[this->_trajectory.step].u_1;
	this->_input.u_2 = this->_trajectory_buffer[this->_trajectory.step].u_2;

	// Perform a control step
	twipr_balancing_control_input_t balancing_input = { .u_1 = this->_input.u_1,
			.u_2 = this->_input.u_2 };

	twipr_balancing_control_output_t balancing_output;

	// Update the balancing controller
	this->_balancing_control.update(this->_dynamic_state, balancing_input,
			&balancing_output);

	this->_output.u_left = limit(balancing_output.u_1, this->config.max_torque);
	this->_output.u_right = limit(balancing_output.u_2,
			this->config.max_torque);

	// Drive the motors
	this->_setTorque(this->_output);

	// Increase the trajectory step counter
	this->_trajectory.step++;

}
/* ======================================================== */
void TWIPR_ControlManager::_setTorque(twipr_control_output_t output) {

	// Apply the torque to the motors
	twipr_drive_input_t drive_input = { .torque_left = output.u_left,
			.torque_right = output.u_right };

	this->_drive->setTorque(drive_input);
}
/* ======================================================== */
void TWIPR_ControlManager::registerCallback(
		twipr_control_callback_id_t callback_id,
		core_utils_Callback<void, uint16_t> callback) {
	switch (callback_id) {
	case TWIPR_CONTROL_CALLBACK_ERROR: {
		this->_callbacks.error = callback;
		break;
	}
	case TWIPR_CONTROL_CALLBACK_TRAJECTORY_START: {
		this->_callbacks.trajectory_start = callback;
		break;
	}
	case TWIPR_CONTROL_CALLBACK_TRAJECTORY_FINISHED: {
		this->_callbacks.trajectory_finished = callback;
		break;
	}
	case TWIPR_CONTROL_CALLBACK_STEP: {
		twipr_error_handler(0);
		break;
	}
	}
}
/* ======================================================== */
void TWIPR_ControlManager::registerCallback(
		twipr_control_callback_id_t callback_id,
		core_utils_Callback<void, uint32_t> callback) {
	switch (callback_id) {
	case TWIPR_CONTROL_CALLBACK_ERROR: {
		twipr_error_handler(0);
		break;
	}
	case TWIPR_CONTROL_CALLBACK_TRAJECTORY_START: {
		twipr_error_handler(0);
		break;
	}
	case TWIPR_CONTROL_CALLBACK_TRAJECTORY_FINISHED: {
		twipr_error_handler(0);
		break;
	}
	case TWIPR_CONTROL_CALLBACK_STEP: {
		this->_callbacks.step = callback;
		break;
	}
	}
}
/* ======================================================== */
void TWIPR_ControlManager::_trajectoryFinished() {

	// Set the mode back to balancing
	this->mode = TWIPR_CONTROL_MODE_BALANCING;

	// Reset the external input
	this->_input.u_1 = 0;
	this->_input.u_2 = 0;

	if (this->_callbacks.trajectory_finished.registered) {
		this->_callbacks.trajectory_finished.call(this->_trajectory.length);
	}
}
/* ======================================================== */
twipr_logging_control_t TWIPR_ControlManager::getSample() {
	twipr_logging_control_t sample;
	sample.control_mode = this->mode;
	sample.control_status = this->status;
	sample.input = this->_input;
	sample.output = this->_output;

	if (this->mode == TWIPR_CONTROL_MODE_TRAJECTORY) {
		sample.trajectory_step = this->_trajectory.step;
		sample.trajectory_id = this->_trajectory.trajectory_id;
	} else {
		sample.trajectory_step = 0;
		sample.trajectory_id = 0;
	}

	return sample;
}
