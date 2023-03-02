/*
 * core_imu_helpers.h
 *
 *  Created on: Jul 8, 2022
 *      Author: Dustin Lehmann
 */

#ifndef CORE_SENSORS_IMU_CORE_IMU_HELPERS_H_
#define CORE_SENSORS_IMU_CORE_IMU_HELPERS_H_

#include "../../core_includes.h"
#include "../../utils/core_utils.h"


#include "bmi160.h"
#include "bmi160_defs.h"

#if CORE_CONFIG_USE_SPI

bmi160_gyr_calib core_sensors_GyroCalibration(BMI160* imu, uint8_t samples, bool resetCalibration);

#endif

#endif /* CORE_SENSORS_IMU_CORE_IMU_HELPERS_H_ */
