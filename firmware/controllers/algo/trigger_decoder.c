/**
 * @file	trigger_decoder.c
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "trigger_decoder.h"
#include "cyclic_buffer.h"

static cyclic_buffer errorDetection;

int isTriggerDecoderError(void) {
	return cbSum(&errorDetection, 6) > 4;
}

void processTriggerEvent(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape, ShaftEvents signal,
		time_t now) {
	if (triggerShape->useRiseEdge && signal != SHAFT_PRIMARY_UP) {
		shaftPositionState->current_index++;
		return;
	}

	if (!triggerShape->useRiseEdge && signal != SHAFT_PRIMARY_DOWN) {
		shaftPositionState->current_index++;
		return;
	}

	int current_duration = now - shaftPositionState->toothed_previous_time;

// todo: skip a number of signal from the beginning

#if EFI_PROD_CODE
#else
	if (shaftPositionState->toothed_previous_duration != 0) {
		printf("ratio %f\r\n", 1.0 * current_duration / shaftPositionState->toothed_previous_duration);
	}
#endif

	if (triggerShape->onlyOneTeeth
			|| (current_duration > shaftPositionState->toothed_previous_duration * triggerShape->syncRatioFrom
					&& current_duration < shaftPositionState->toothed_previous_duration * triggerShape->syncRatioTo)) {
		int isDecodingError = shaftPositionState->current_index != triggerShape->shaftPositionEventCount - 1;
		cbAdd(&errorDetection, isDecodingError);

		shaftPositionState->shaft_is_synchronized = TRUE;
		shaftPositionState->current_index = 0;
	} else {
		shaftPositionState->current_index++;
	}

	shaftPositionState->toothed_previous_duration = current_duration;
	shaftPositionState->toothed_previous_time = now;

}

void initTriggerDecoder(void) {
	cbInit(&errorDetection);
}

