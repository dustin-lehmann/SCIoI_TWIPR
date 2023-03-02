/*
 * robot-control_std.h
 *
 *  Created on: Jul 29, 2022
 *      Author: Dustin Lehmann
 */

#ifndef ROBOT_CONTROL_STD_H_
#define ROBOT_CONTROL_STD_H_

#include <core.h>
#include "robot-control_board.h"
#include "robot-control_default_config.h"

extern core_hardware_LED led1;
extern core_hardware_LED led2;
extern core_hardware_LED led_act;

extern core_comm_UartInterface debug_uart;

void robot_control_init();
void robot_control_start();


#endif /* ROBOT_CONTROL_STD_H_ */
