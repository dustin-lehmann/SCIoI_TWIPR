/*
 * firmware_setting.h
 *
 *  Created on: 3 Mar 2023
 *      Author: lehmann_workstation
 */

#ifndef FIRMWARE_SETTINGS_H_
#define FIRMWARE_SETTINGS_H_


//


// Control
#define TWIPR_CONTROL_TS 10 //msec
#define TWIPR_CONTROL_MAX_TORQUE 0.3

// Control - Trajectories
#define TWIPR_CONTROL_TRAJECTORY_BUFFER_SIZE 10 * 1000/TWIPR_CONTROL_TS


// Logging
#define TWIPR_FIRMWARE_SAMPLE_BUFFER_SIZE (uint16_t) (0.1 * 1000 / TWIPR_CONTROL_TS)

#endif /* FIRMWARE_SETTINGS_H_ */
