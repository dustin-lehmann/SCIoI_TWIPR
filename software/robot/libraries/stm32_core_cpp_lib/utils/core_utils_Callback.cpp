/*
 * core_utils_Callback.cpp
 *
 *  Created on: Jul 7, 2022
 *      Author: Dustin Lehmann
 */

#include "core_utils_Callback.h"

core_utils_Callback::core_utils_Callback() {
	this->callback = NULL;
}

core_utils_Callback::core_utils_Callback(
		void (*callback)(void *argument, void *params), void *params) {
	this->callback = callback;
	this->params = params;
}

void core_utils_Callback::call() {
	if (this->callback != NULL) {
		this->callback(NULL, this->params);
	}

}

void core_utils_Callback::call(void *argument) {
	if (this->callback != NULL) {
		this->callback(argument, this->params);
	}
}
