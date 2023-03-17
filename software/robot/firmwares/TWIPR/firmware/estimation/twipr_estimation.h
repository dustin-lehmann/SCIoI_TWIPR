/*
 * twipr_estimation.h
 *
 *  Created on: 22 Feb 2023
 *      Author: Dustin Lehmann
 */

#ifndef ESTIMATION_TWIPR_ESTIMATION_H_
#define ESTIMATION_TWIPR_ESTIMATION_H_

#include "core.h"
#include "twipr_model.h"
#include "simplexmotion.hpp"
#include "twipr_sensors.h"

#define TWIPR_ESTIMATION_FREQUENCY 200
#define TWIPR_ESTIMATION_STATE_BUFFER_SIZE TWIPR_ESTIMATION_FREQUENCY*1

typedef enum twipr_estimation_status_t {
	TWIPR_ESTIMATION_STATUS_NONE = 0,
	TWIPR_ESTIMATION_STATUS_IDLE = 1,
	TWIPR_ESTIMATION_STATUS_OK = 2,
	TWIPR_ESTIMATION_STATUS_ERROR = -1,
} twipr_estimation_status_t;

typedef struct twipr_estimation_state_t {
	float v;
	float theta;
	float theta_dot;
	float psi;
	float psi_dot;
} twipr_estimation_state_t;

typedef enum twipr_estimation_callback_id {
	TWIPR_ESTIMATION_CALLBACK_UPDATE = 0,
	TWIPR_ESTIMATION_CALLBACK_ERROR = 1,
	TWIPR_ESTIMATION_CALLBACK_ANGLE = 2,
	TWIPR_ESTIMATION_CALLBACK_SLIP = 3,
} twipr_estimation_callback_id;

typedef struct twipr_estimation_callbacks {
	core_utils_Callback<void, void> update;
	core_utils_Callback<void, void> error;
	core_utils_Callback<void, void> angle;
	core_utils_Callback<void, void> slip;
} twipr_estimation_callbacks;

typedef struct twipr_estimation_config_t {
	TWIPR_Sensors *sensors;
	bool enable_slip_detection;
	bool enable_angle_threshold;
	float angle_threshold;
} twipr_estimation_config_t;

typedef struct twipr_logging_estimation_t {
	twipr_estimation_state_t state;
} twipr_logging_estimation_t;

class TWIPR_Estimation {
public:
	TWIPR_Estimation();
	void init(twipr_estimation_config_t config);
	void start();
	void reset();
	void stop();

	void update();

	void task_function();

	twipr_logging_estimation_t getSample();

	void registerCallback(twipr_estimation_callback_id callback_id,
			void (*callback)(void *argument, void *params), void *params);

	twipr_estimation_state_t getState();
	twipr_estimation_state_t getMeanState();

	void setState(twipr_estimation_state_t state);

	twipr_estimation_status_t getStatus();

	twipr_model *model;
	twipr_estimation_status_t status;
	twipr_estimation_state_t state;
	twipr_estimation_state_t mean_state;
	twipr_estimation_config_t config;
private:
	TWIPR_Sensors *_sensors;
	uint16_t _freq;
	twipr_estimation_state_t _state_buffer[TWIPR_ESTIMATION_STATE_BUFFER_SIZE];
	uint16_t _state_buffer_index = 0;
	osSemaphoreId_t _semaphore;
	Madgwick _orientation_fusion;
};

void estimation_task(void *estimation);

#endif /* ESTIMATION_TWIPR_ESTIMATION_H_ */
