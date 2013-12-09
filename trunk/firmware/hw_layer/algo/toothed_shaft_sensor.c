/*
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    toothed_shaft_sensor.c
 * @brief	Logic of toothed wheel decoding
 */

#include "toothed_shaft_sensor.h"

#if EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR

void handleShaftSignal(ShaftEvents signal, time_t now, ShaftPositionState *shaftPositionState) {
	if (signal != SHAFT_PRIMARY_UP) {
		shaftPositionState->current_index++;
		return;
	}

	int current_duration = now - shaftPositionState->toothed_previous_time;

// todo: skip a number of signal from the beginning

	if (current_duration > shaftPositionState->toothed_previous_duration * 1.5
			&& current_duration < shaftPositionState->toothed_previous_duration * 4) {
		shaftPositionState->shaft_is_synchronized = TRUE;
		shaftPositionState->current_index = 0;
	} else {
		shaftPositionState->current_index++;
	}

	shaftPositionState->toothed_previous_duration = current_duration;
	shaftPositionState->toothed_previous_time = now;
}

void initShaftSignalDecoder(void) {
}

int isSignalDecoderError(void) {
	return FALSE;
}

#endif /* EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR */
