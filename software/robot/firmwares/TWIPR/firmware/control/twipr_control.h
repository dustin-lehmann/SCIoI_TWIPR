/*
 * twipr_control.h
 *
 *  Created on: 22 Feb 2023
 *      Author: Dustin Lehmann
 */

#ifndef CONTROL_TWIPR_CONTROL_H_
#define CONTROL_TWIPR_CONTROL_H_

#include "core.h"
#include "twipr_estimation.h"

typedef enum twipr_control_state {
	TWIPR_CONTROL_STATE_IDLE = 0,
	TWIPR_CONTROL_STATE_ERROR = -1,
	TWIPR_CONTROL_STATE_DIRECT = 1,
	TWIPR_CONTROL_STATE_SF = 2,
} twipr_control_state;

typedef enum twipr_control_callback_id {
	TWIPR_CONTROL_CALLBACK_ERROR = 1,
}twipr_control_callback_id;

typedef struct twipr_control_config {
	uint16_t freq;
	float K[2][4];
} twipr_control_config;

typedef struct twipr_control_input {
	float u_1;
	float u_2;
} twipr_control_input;

typedef struct twipr_control_output {
	float u_left;
	float u_right;
} twipr_control_output;

class TWIPR_Control {
public:
	TWIPR_Control();
	void init(twipr_control_config config);
	void start();
	void reset();
	void stop();

	void registerCallback(twipr_control_callback_id callback_id,
			void (*callback)(void *argument, void *params), void *params);

	void update(twipr_estimation_state state, twipr_control_input input,
			twipr_control_output *output);

	void set_K(float K[2][4]);
	void setState(twipr_control_state state);

	twipr_control_state state;
	twipr_control_config config;
private:
	twipr_control_input _last_input;
	twipr_estimation_state _last_state;
	twipr_control_output _last_output;
};


// TODO: This should have the trajectories and such
class TWIPR_ControlManager {

};

//void control_task(void *controller);

#endif /* CONTROL_TWIPR_CONTROL_H_ */
