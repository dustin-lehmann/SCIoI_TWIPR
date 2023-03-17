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

class Callback {
public:
	Callback(){

	}

	virtual void call(){

	}

	virtual void call(void* argument){

	}
private:

};

template<typename R, typename A>
class core_utils_Callback: public Callback {
public:
	core_utils_Callback() {
		this->registered = 0;
	}
	core_utils_Callback(R (*function)(A)) {
		_fp = core_utils_FunctionPointer<R, A>(function);
		this->registered = 1;
	}

	template<typename T>
	core_utils_Callback(T *object, R (T::*member)(A)) {
		_fp = core_utils_FunctionPointer<R,A>(object, member);
		this->registered = 1;
	}

	R call(A argument){
		return this->_fp(argument);
	}
//
//	void operator()(void *argument) {
//		return this->call(argument);
//	}
//
//	void operator()() {
//		return this->call();
//	}

	uint8_t registered = 0;
private:
	core_utils_FunctionPointer<R, A> _fp;
};


template<typename R>
class core_utils_Callback<R, void>: public Callback {
public:
	core_utils_Callback() {
		this->registered = 0;
	}
	core_utils_Callback(R (*function)(void)) {
		_fp = core_utils_FunctionPointer<R, void>(function);
		this->registered = 1;
	}

	template<typename T>
	core_utils_Callback(T *object, R (T::*member)(void)) {
		_fp = core_utils_FunctionPointer<R,void>(object, member);
		this->registered = 1;
	}

	R call() {
		return this->_fp();
	}
//
//	void operator()(void *argument) {
//		return this->call(argument);
//	}
//
//	void operator()() {
//		return this->call();
//	}

	uint8_t registered = 0;
private:
	core_utils_FunctionPointer<R, void> _fp;
};



class core_utils_Notification {
public:

private:

};

#endif /* CORE_UTILS_CORE_UTILS_CALLBACK_H_ */
