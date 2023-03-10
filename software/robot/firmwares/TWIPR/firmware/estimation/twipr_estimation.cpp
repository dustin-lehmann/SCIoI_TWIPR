/*
 * twipr_estimation.cpp
 *
 *  Created on: 22 Feb 2023
 *      Author: Dustin Lehmann
 */

#include "twipr_estimation.h"

//osSemaphoreId_t

TWIPR_Estimation::TWIPR_Estimation() {
	this->status = TWIPR_ESTIMATION_STATUS_NONE;
}

/* ======================================================= */
void TWIPR_Estimation::init(twipr_estimation_config_t config) {
	this->config = config;

	this->status = TWIPR_ESTIMATION_STATUS_IDLE;
}

/* ======================================================= */
void TWIPR_Estimation::start() {

}
/* ======================================================= */
void TWIPR_Estimation::reset() {

}
/* ======================================================= */
void TWIPR_Estimation::stop() {

}
/* ======================================================= */
void TWIPR_Estimation::update() {

}
/* ======================================================= */
twipr_estimation_state_t TWIPR_Estimation::getState() {

}
/* ======================================================= */
void TWIPR_Estimation::setState(twipr_estimation_state_t state) {

}
/* ======================================================= */
/* ======================================================= */
/* ======================================================= */
/* ======================================================= */
/* ======================================================= */
/* ======================================================= */
/* ======================================================= */
void estimation_task(void *estimation) {

}
