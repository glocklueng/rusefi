/*
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    toothed_shaft_sensor.h
 */

#include "main.h"

#ifndef TOOTHED_SHAFT_SENSOR_H_
#define TOOTHED_SHAFT_SENSOR_H_

#if EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR

#include "shaft_position_input.h"

void handleShaftSignal(ShaftEvents signal, time_t now, ShaftPositionState *shaftPositionState);
void initShaftSignalDecoder(void);

#endif /* EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR */

#endif /* TOOTHED_SHAFT_SENSOR_H_ */
