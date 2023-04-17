/*
 * core.c
 *
 *  Created on: Jul 6, 2022
 *      Author: Dustin Lehmann
 */

#include "main.h"

#include "core/core.h"
#include "firmware_c.h"

uint8_t build_message();

core_hardware_LED led1(BOARD_LED_1_PORT, BOARD_LED_1_PIN);
core_hardware_LED led2(BOARD_LED_2_PORT, BOARD_LED_2_PIN);
core_hardware_LED led_act(BOARD_ACT_LED_PORT, BOARD_ACT_LED_PIN);

BMI160 imu(BOARD_SPI_INTERN, BOARD_CS_IMU_PORT, BOARD_CS_IMU_PIN);

core_comm_SerialSocket_config cm4_socket_config;
core_comm_SerialSocket cm4_socket(BOARD_DEBUG_UART, cm4_socket_config);

Madgwick sensor_fusion;


uint8_t message[19] = {0};
uint8_t message_encode[100];

uint8_t button_state = 0;

void core_start() {
	HAL_Delay(1000);
	const osThreadAttr_t imu_task_attributes = { .name = "imu", .stack_size =
			1280 * 4, .priority = (osPriority_t) osPriorityHigh4, };

	const osThreadAttr_t usb_task_attributes = { .name = "usb", .stack_size =
			1280 * 4, .priority = (osPriority_t) osPriorityNormal, };

	osThreadNew(imu_task, NULL, &imu_task_attributes);
	osThreadNew(usb_task, NULL, &usb_task_attributes);

}

void imu_task(void *argument) {
	uint32_t kernel_ticks = 0;
	uint32_t loop_idx = 0;

	osDelay(1000);
	uint8_t imu_ok = imu.init();

	if (!imu_ok){
		while(1){
			led2.toggle();
			osDelay(500);
		}
	}

//	imu.fastOffsetCalibration();
	sensor_fusion.begin(100.0f);

	while (1){
		loop_idx++;
		kernel_ticks = osKernelGetTickCount();

		imu.update();
		sensor_fusion.updateIMU(imu.gyr.x, imu.gyr.y, imu.gyr.z, imu.acc.x, imu.acc.y, imu.acc.z);

		if (loop_idx % 10 == 0){
			button_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == 0;
			if (button_state){
				led1.on();
			}
			else {
				led1.off();
			}
			led2.toggle();
		}

		if (loop_idx % 4 == 0) {
			uint8_t len = build_message();
			CDC_Transmit_FS(message_encode, len);
		}

		osDelayUntil(kernel_ticks + 10);
	}
}

uint8_t build_message(){

	message[0] = 0x55;
	float_to_bytearray(sensor_fusion.q0, &message[1]);
	float_to_bytearray(sensor_fusion.q1, &message[5]);
	float_to_bytearray(sensor_fusion.q2, &message[9]);
	float_to_bytearray(sensor_fusion.q3, &message[13]);
	message[17] = button_state;
	message[18] = 0x5D;

	uint8_t len = cobsEncode(message, 19, message_encode);
	message_encode[len] = 0x00;

	return len+1;
}

void usb_task(void *argument) {

	uint32_t ticks = 0;
	while (1){
		ticks = osKernelGetTickCount();
		osDelayUntil(ticks + 250);
	}

}
