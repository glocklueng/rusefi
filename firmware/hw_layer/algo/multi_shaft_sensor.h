/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    multi_shaft_sensor.h
 */

#include "main.h"

#ifndef MULTI_SHAFT_SENSOR_H_
#define MULTI_SHAFT_SENSOR_H_

#include "shaft_position_input.h"

#if EFI_USE_MULTI_SENSOR_SHAFT_SENSOR

void handleShaftSignal(ShaftEvents signal, time_t now, ShaftPositionState *shaftPositionState);

#endif /* EFI_USE_MULTI_SENSOR_SHAFT_SENSOR */

#endif /* MULTI_SHAFT_SENSOR_H_ */
