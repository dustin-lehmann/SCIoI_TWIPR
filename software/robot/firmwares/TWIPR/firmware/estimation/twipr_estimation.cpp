/*
 * twipr_estimation.cpp
 *
 *  Created on: 22 Feb 2023
 *      Author: Dustin Lehmann
 */

#include "twipr_estimation.h"

static const osThreadAttr_t estimation_task_attributes = { .name = "estimation",
		.stack_size = 1280 * 4, .priority = (osPriority_t) osPriorityNormal, };

/* ======================================================= */
TWIPR_Estimation::TWIPR_Estimation() {
	this->status = TWIPR_ESTIMATION_STATUS_NONE;
}

/* ======================================================= */
void TWIPR_Estimation::init(twipr_estimation_config_t config) {
	this->config = config;

	// Initialize the sensors
	twipr_sensors_config_t twipr_sensors_config = { .drive = this->config.drive, };
	this->_sensors.init(twipr_sensors_config);

	this->status = TWIPR_ESTIMATION_STATUS_IDLE;
	this->_semaphore = osSemaphoreNew(1, 1, NULL);
}

/* ======================================================= */
void TWIPR_Estimation::start() {
	osThreadNew(estimation_task, (void*) this, &estimation_task_attributes);
}
/* ======================================================= */
void TWIPR_Estimation::reset() {
	twipr_error_handler(0);
}
/* ======================================================= */
void TWIPR_Estimation::task_function() {

	this->_orientation_fusion.begin((float) TWIPR_ESTIMATION_FREQUENCY);
	this->status = TWIPR_ESTIMATION_STATUS_OK;
//	this->_sensors.calibrate();
	uint32_t ticks;

	while (true) {
		ticks = osKernelGetTickCount();
		this->update();
		osDelayUntil(ticks + (uint32_t) (1000.0 / TWIPR_ESTIMATION_FREQUENCY));
	}
}
/* ======================================================= */
void TWIPR_Estimation::stop() {
	twipr_error_handler(0);
}
/* ======================================================= */
void TWIPR_Estimation::update() {

	// Update the Sensors
	this->_sensors.update();

	// Read the sensor data
	twipr_sensors_data_t data = this->_sensors.getData();

	// Orientation Estimation
	this->_orientation_fusion.updateIMU(data.gyr.x, data.gyr.y, data.gyr.z,
			data.acc.x, data.acc.y, data.acc.z);

	// Read the pitch angle
	float theta = this->_orientation_fusion.getRollRadians();
	float theta_dot = data.gyr.x;

	// Get the speed and yaw speed
	float v = (data.speed_left + data.speed_right) / 2 * this->config.model.r_wheel;
	float psi_dot = (data.speed_right - data.speed_left) * this->config.model.r_wheel
			/ this->config.model.distance_wheels;

	// Set the current state
	osSemaphoreAcquire(_semaphore, portMAX_DELAY);
	this->state.v = v;
	this->state.theta = theta;
	this->state.theta_dot = theta_dot;
	this->state.psi = 0;
	this->state.psi_dot = psi_dot;

	// Calculate the average
	this->mean_state.v = this->mean_state.v
			- (this->_state_buffer[this->_state_buffer_index].v
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE)
			+ (this->state.v / (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE);
	this->mean_state.theta = this->mean_state.theta
			- (this->_state_buffer[this->_state_buffer_index].theta
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE)
			+ (this->state.theta / (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE);
	this->mean_state.theta_dot = this->mean_state.theta_dot
			- (this->_state_buffer[this->_state_buffer_index].theta_dot
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE)
			+ (this->state.theta_dot
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE);
	this->mean_state.psi = this->mean_state.psi
			- (this->_state_buffer[this->_state_buffer_index].psi
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE)
			+ (this->state.psi
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE);
	this->mean_state.psi_dot = this->mean_state.psi_dot
			- (this->_state_buffer[this->_state_buffer_index].psi_dot
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE)
			+ (this->state.psi_dot
					/ (float) TWIPR_ESTIMATION_STATE_BUFFER_SIZE);

	this->_state_buffer[this->_state_buffer_index] = this->state;
	osSemaphoreRelease(_semaphore);

	this->_state_buffer_index++;
	if (this->_state_buffer_index == TWIPR_ESTIMATION_STATE_BUFFER_SIZE) {
		this->_state_buffer_index = 0;
	}

}
/* ======================================================= */
twipr_estimation_state_t TWIPR_Estimation::getMeanState() {
	twipr_estimation_state_t out;
	osSemaphoreAcquire(_semaphore, portMAX_DELAY);
	out = this->mean_state;
	osSemaphoreRelease(_semaphore);
	return out;
}
/* ======================================================= */
twipr_estimation_state_t TWIPR_Estimation::getState() {
	osSemaphoreAcquire(_semaphore, portMAX_DELAY);
	twipr_estimation_state_t out = this->state;
	osSemaphoreRelease(_semaphore);
	return out;
}
/* ======================================================= */
void TWIPR_Estimation::setState(twipr_estimation_state_t state) {
	twipr_error_handler(0);
}
/* ======================================================= */
twipr_logging_estimation_t TWIPR_Estimation::getSample(){
	twipr_logging_estimation_t sample;
	sample.state = this->getState();
	sample.data = this->_sensors.getData();
	return sample;
}
/* ======================================================= */
void estimation_task(void *estimation) {
	TWIPR_Estimation *estimator = (TWIPR_Estimation*) estimation;
	estimator->task_function();
}
