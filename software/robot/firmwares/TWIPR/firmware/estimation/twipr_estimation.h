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

typedef enum twipr_estimation_status {
	TWIPR_ESTIMATION_STATE_IDLE = 0,
	TWIPR_ESTIMATION_STATE_OK = 1,
	TWIPR_ESTIMATION_STATE_ERROR = -1,
} twipr_estimation_status;

typedef struct twipr_estimation_state {
	float theta;
	float theta_dot;
	float psi;
	float psi_dot;
	float v;
} twipr_estimation_state;

typedef enum twipr_estimation_callback_id {
	TWIPR_ESTIMATION_CALLBACK_UPDATE = 0,
	TWIPR_ESTIMATION_CALLBACK_ERROR = 1,
	TWIPR_ESTIMATION_CALLBACK_ANGLE = 2,
	TWIPR_ESTIMATION_CALLBACK_SLIP = 3,
}twipr_estimation_callback_id;

typedef struct twipr_estimation_callbacks {
	core_utils_Callback update;
	core_utils_Callback error;
	core_utils_Callback angle;
	core_utils_Callback slip;
} twipr_estimation_callbacks;

typedef struct twipr_estimation_config {
	uint16_t freq;
	bool enable_slip_detection;
	bool enable_angle_threshold;
	float angle_threshold;


} twipr_estimation_config;

class TWIPR_Estimation {
public:
	TWIPR_Estimation();
	void init(BMI160 *imu, SimplexMotionMotor *motor_left,
			SimplexMotionMotor *motor_right, twipr_estimation_config config);
	void start();
	void reset();
	void stop();

	void update();

	void registerCallback(twipr_estimation_callback_id callback_id,
			void (*callback)(void *argument, void *params), void *params);

	twipr_estimation_state getState();
	void setState(twipr_estimation_state state);
	twipr_estimation_status getStatus();

	twipr_model *model;
	twipr_estimation_status status;
	twipr_estimation_state state;
private:
	BMI160 *imu;
	SimplexMotionMotor *motor_left;
	SimplexMotionMotor *motor_right;

	uint16_t freq;
};

void estimation_task(void *estimator);

#endif /* ESTIMATION_TWIPR_ESTIMATION_H_ */
