/**
 * @file    multi_shaft_sensor.c
 * @brief	Logic of multi-sensor position signal decoding
 *
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "multi_shaft_sensor.h"
#include "cyclic_buffer.h"
#include "engine_configuration.h"
#include "trigger_decoder.h"

#if defined __GNUC__
#pragma message VAR_NAME_VALUE(EFI_USE_MULTI_SENSOR_SHAFT_SENSOR)
#endif

#if EFI_USE_MULTI_SENSOR_SHAFT_SENSOR

static Logging logger;

extern EngineConfiguration2 *engineConfiguration2;

void handleShaftSignal(ShaftEvents signal, time_t now, trigger_state_s *shaftPositionState) {
	shaftPositionState->shaft_is_synchronized = TRUE;

	if (signal == SHAFT_PRIMARY_UP) {
		int isDecodingError = shaftPositionState->current_index != engineConfiguration2->triggerShape.shaftPositionEventCount - 1;
//		cbAdd(&errorDetection, isDecodingError);

		shaftPositionState->current_index = 0;
	} else {
		shaftPositionState->current_index++;
	}
}

void initShaftSignalDecoder(void) {
	initLogging(&logger, "multi_shaft_sensor");
	initTriggerDecoder();
}

int isSignalDecoderError(void) {
	return isTriggerDecoderError();
}

#endif /* EFI_USE_MULTI_SENSOR_SHAFT_SENSOR */
