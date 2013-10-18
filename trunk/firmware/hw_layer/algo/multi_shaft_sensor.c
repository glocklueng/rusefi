/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    multi_shaft_sensor.c
 * @brief	Logic of multi-sensor decoding
 */

#include "main.h"
#include "multi_shaft_sensor.h"

#if defined __GNUC__
#pragma message VAR_NAME_VALUE(EFI_USE_MULTI_SENSOR_SHAFT_SENSOR)
#endif

#if EFI_USE_MULTI_SENSOR_SHAFT_SENSOR

void handleShaftSignal(ShaftEvents signal, time_t now, ShaftPositionState *shaftPositionState) {
	// todo: reset index at reference signal
	shaftPositionState->current_index++;
}

#endif /* EFI_USE_MULTI_SENSOR_SHAFT_SENSOR */
