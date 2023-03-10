/*
 * twipr_control.cpp
 *
 *  Created on: 3 Mar 2023
 *      Author: lehmann_workstation
 */

#include "twipr_control.h"

TWIPR_ControlManager::TWIPR_ControlManager() {

}

/* ======================================================== */
void TWIPR_ControlManager::init(twipr_control_config_t config) {
	this->config = config;
	this->estimation = config.estimation;

	// Initialize the balancing controller
	twipr_balancing_control_config_t balancing_control_config;
	memcpy(balancing_control_config.K, this->config.K,
			sizeof(balancing_control_config.K));
	this->balancing_control.init(balancing_control_config);

	this->control_status = TWIPR_CONTROL_STATUS_OFF;
}
/* ======================================================== */
uint8_t TWIPR_ControlManager::start() {

	return 1;
}

/* ======================================================== */
void TWIPR_ControlManager::stop() {

	// Stop the balancing controller
	this->balancing_control.stop();

	// Set the own state to off
	this->control_status = TWIPR_CONTROL_STATUS_OFF;

	// Set the input to 0
	this->_input.u_1 = 0.0;
	this->_input.u_2 = 0.0;
}
/* ======================================================== */
void TWIPR_ControlManager::reset() {

}
/* ======================================================== */
void TWIPR_ControlManager::step() {

	// Perform State Estimation
	// TODO
	this->_dynamic_state = this->estimation->getState();

	// Check for errors
	// Drive
	// TODO

	switch (this->control_status) {
	case TWIPR_CONTROL_STATUS_OFF: {
		// Do nothing
		break;
	}
	case TWIPR_CONTROL_STATUS_ERROR: {
		// Turn everything off // TODO
		break;
	}
	case TWIPR_CONTROL_STATUS_RUNNING: {
		// TODO
		break;
	}

	}
}
/* ======================================================== */
void TWIPR_ControlManager::setMode(twipr_control_mode_t mode) {
	// TODO: Do some checking here

}
/* ======================================================== */
void TWIPR_ControlManager::setInput(twipr_control_input_t input) {
	// TODO: We need some input checking here
	this->_input = input;
}
/* ======================================================== */
twipr_control_status_t TWIPR_ControlManager::getStatus() {
	return this->control_status;
}

/* ======================================================== */
void TWIPR_ControlManager::_trajectoryStep() {
	// Check if the trajectory is finished
	if (this->_trajectory.step == this->_trajectory.length) {
		this->_trajectoryFinished();
		return;
	}

	// Check if the step is correct
	if (this->_trajectory_buffer[this->_trajectory.step].step
			!= this->_trajectory.step) {
		// TODO
	}

	// Set the input from the current input of the buffer
	this->_input.u_1 = this->_trajectory_buffer[this->_trajectory.step].u_1;
	this->_input.u_2 = this->_trajectory_buffer[this->_trajectory.step].u_2;

	// Perform a control step
	this->_controlStep();

	// Increase the trajectory step counter
	this->_trajectory.step++;

}

/* ======================================================== */
void TWIPR_ControlManager::_controlStep() {

	// Calculate the input from the balancing controller
	twipr_balancing_control_input_t balancing_input = { .u_1 = this->_input.u_1,
			.u_2 = this->_input.u_2, };

	twipr_balancing_control_output_t balancing_output;

	// Update the balancing controller
	this->balancing_control.update(this->_dynamic_state, balancing_input,
			&balancing_output);

	twipr_control_output_t control_output = { .u_left = balancing_output.u_1,
			.u_right = balancing_output.u_2 };

	// Drive the motors
	this->_setTorque(control_output);
}

/* ======================================================== */
void TWIPR_ControlManager::_setTorque(twipr_control_output_t output) {
	// TODO: Checks

	// Apply the torque to the motors
	twipr_drive_input_t drive_input = { .torque_left = output.u_left,
			.torque_right = output.u_right };

	this->drive->setTorque(drive_input);
}
/* ======================================================== */

/* ======================================================== */

/* ======================================================== */

/* ======================================================== */

/* ======================================================== */
