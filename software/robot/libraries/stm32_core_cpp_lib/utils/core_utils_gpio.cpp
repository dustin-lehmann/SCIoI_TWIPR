/*
 * core_utils_gpio.cpp
 *
 *  Created on: Mar 15, 2023
 *      Author: lehmann_workstation
 */

#include "core_utils_gpio.h"

core_utils_GPIO::core_utils_GPIO(GPIO_TypeDef *GPIOx, uint16_t pin) {
	this->GPIOx = GPIOx;
	this->pin = pin;
}

/* -------------------------------------------------------------------------------- */
void core_utils_GPIO::write(uint8_t value) {
	if (value) {
		HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_RESET);
	}
}

/* -------------------------------------------------------------------------------- */
void core_utils_GPIO::toggle() {
	HAL_GPIO_TogglePin(GPIOx, pin);
}

/* -------------------------------------------------------------------------------- */
uint8_t core_utils_GPIO::read() {
	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOx, pin);
	if (state == GPIO_PIN_SET) {
		return 1;
	} else {
		return 0;
	}
}
