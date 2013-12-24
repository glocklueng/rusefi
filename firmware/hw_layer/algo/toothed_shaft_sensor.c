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
#include "cyclic_buffer.h"
#include "engine_configuration.h"

static Logging logger;
static cyclic_buffer errorDetection;
extern EngineConfiguration2 engineConfiguration2;

void handleShaftSignal(ShaftEvents signal, time_t now, trigger_state_s *shaftPositionState) {
}

void initShaftSignalDecoder(void) {
	initLogging(&logger, "toothed_shaft_sensor");
	cbInit(&errorDetection);
}

int isSignalDecoderError(void) {
	return cbSum(&errorDetection, 6) > 4;
}

#endif /* EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR */
