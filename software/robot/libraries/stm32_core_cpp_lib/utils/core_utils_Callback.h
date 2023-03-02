/*
 * core_utils_Callback.h
 *
 *  Created on: Jul 7, 2022
 *      Author: Dustin Lehmann
 */

#ifndef CORE_UTILS_CORE_UTILS_CALLBACK_H_
#define CORE_UTILS_CORE_UTILS_CALLBACK_H_

#include "stdint.h"
#include "core_utils_functionpointer.h"

class core_utils_Callback {
public:
	core_utils_Callback();
	core_utils_Callback(void (*callback)(void *argument, void *params),
			void *params);

//	FunctionPointer function;
	void (*callback)(void *argument, void *params);
	void *params;

	void call();
	void call(void *argument);

	void operator()(void *argument) {
		return this->call(argument);
	}

	void operator()() {
		return this->call();
	}

	uint8_t registered = 0;
private:

};

class core_utils_Notification {
public:

private:

};

#endif /* CORE_UTILS_CORE_UTILS_CALLBACK_H_ */
