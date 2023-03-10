/*
 * twipr_control.cpp
 *
 *  Created on: 22 Feb 2023
 *      Author: Dustin Lehmann
 */

#include <twipr_balancing_control.h>

TWIPR_BalancingControl::TWIPR_BalancingControl() {
	this->mode = TWIPR_BALANCING_CONTROL_MODE_OFF;
	this->status = TWIPR_BALANCING_CONTROL_STATUS_NONE;
}

/* ========================================================================= */

void TWIPR_BalancingControl::init(twipr_balancing_control_config_t config) {
	this->config = config;
	this->status = TWIPR_BALANCING_CONTROL_STATUS_IDLE;
}

/* ========================================================================= */
void TWIPR_BalancingControl::start() {
	if (this->status == TWIPR_BALANCING_CONTROL_STATUS_NONE
			|| this->status == TWIPR_BALANCING_CONTROL_STATUS_ERROR) {
		twipr_error_handler(TWIPR_BALANCING_CONTROL_ERROR_INIT);
	}
}

/* ========================================================================= */
void TWIPR_BalancingControl::update(twipr_estimation_state_t state,
		twipr_balancing_control_input_t input,
		twipr_balancing_control_output_t *output) {

	switch (this->status) {
	case TWIPR_BALANCING_CONTROL_STATUS_NONE: {
		output->u_1 = 0;
		output->u_2 = 0;
		break;
	}
	case TWIPR_BALANCING_CONTROL_STATUS_IDLE: {
		output->u_1 = 0;
		output->u_2 = 0;
		break;
	}
	case TWIPR_BALANCING_CONTROL_STATUS_ERROR: {
		output->u_1 = 0;
		output->u_2 = 0;
		break;
	}
	case TWIPR_BALANCING_CONTROL_STATUS_RUNNING: {
		switch (this->mode) {
		case TWIPR_BALANCING_CONTROL_MODE_OFF: {
			output->u_1 = 0;
			output->u_2 = 0;
			break;
		}
		case TWIPR_BALANCING_CONTROL_MODE_DIRECT: {
			output->u_1 = input.u_1;
			output->u_2 = input.u_2;
			break;
		}
		case TWIPR_BALANCING_CONTROL_MODE_ON: {
			this->_calculateOutput(state, input, output);
		}
		}
	}
	}
}
/* ========================================================================= */
void TWIPR_BalancingControl::_calculateOutput(twipr_estimation_state_t state,
		twipr_balancing_control_input_t input,
		twipr_balancing_control_output_t *output) {
	output->u_1 = this->config.K[0][0] * state.v
			+ this->config.K[0][1] * state.theta
			+ this->config.K[0][2] * state.theta_dot
			+ this->config.K[0][3] * state.psi
			+ this->config.K[0][4] * state.psi_dot;

	output->u_2 = this->config.K[1][0] * state.v
			+ this->config.K[1][1] * state.theta
			+ this->config.K[1][2] * state.theta_dot
			+ this->config.K[1][3] * state.psi
			+ this->config.K[1][4] * state.psi_dot;

	output->u_1 = output->u_1 + input.u_1;
	output->u_2 = output->u_2 + input.u_2;

}
/* ========================================================================= */
void TWIPR_BalancingControl::reset() {
	// TODO
}
/* ========================================================================= */
void TWIPR_BalancingControl::stop() {
	this->mode = TWIPR_BALANCING_CONTROL_MODE_OFF;
	this->status = TWIPR_BALANCING_CONTROL_STATUS_IDLE;
}
/* ========================================================================= */
void TWIPR_BalancingControl::set_K(float K[2][5]) {
	memcpy(this->config.K, K, sizeof(K));
}
/* ========================================================================= */
void TWIPR_BalancingControl::setMode(twipr_balancing_control_mode_t mode) {

	// TODO

	if (this->mode == TWIPR_BALANCING_CONTROL_MODE_DIRECT
			|| this->mode == TWIPR_BALANCING_CONTROL_MODE_ON) {
		this->status == TWIPR_BALANCING_CONTROL_STATUS_RUNNING;
	}
}
/* ========================================================================= */

/* ========================================================================= */

/* ========================================================================= */
