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

/**
 * @return TRUE is something is wrong with trigger decoding
 */
int isTriggerDecoderError(void) {
	return cbSum(&errorDetection, 6) > 4;
}

/**
 * @brief This method changes the state of trigger_state_s data structure according to the trigger event
 */
void processTriggerEvent(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape, ShaftEvents signal,
		time_t now) {

	int isLessImportant = (triggerShape->useRiseEdge && signal != SHAFT_PRIMARY_UP)
			|| (!triggerShape->useRiseEdge && signal != SHAFT_PRIMARY_DOWN);

	if (isLessImportant) {
		/**
		 * For less important events we simply increment the index.
		 */
		shaftPositionState->current_index++;
		return;
	}

	int currentDuration = now - shaftPositionState->toothed_previous_time;

// todo: skip a number of signal from the beginning

#if EFI_PROD_CODE
#else
	if (shaftPositionState->toothed_previous_duration != 0) {
		printf("ratio %f\r\n", 1.0 * currentDuration / shaftPositionState->toothed_previous_duration);
	}
#endif

	if (triggerShape->onlyOneTeeth
			|| (currentDuration > shaftPositionState->toothed_previous_duration * triggerShape->syncRatioFrom
					&& currentDuration < shaftPositionState->toothed_previous_duration * triggerShape->syncRatioTo)) {
		/**
		 * We can check if things are fine by comparing the number of events in a cycle with the expected number of event.
		 */
		int isDecodingError = shaftPositionState->current_index != triggerShape->shaftPositionEventCount - 1;
		cbAdd(&errorDetection, isDecodingError);

		shaftPositionState->shaft_is_synchronized = TRUE;
		shaftPositionState->current_index = 0;
	} else {
		shaftPositionState->current_index++;
	}

	shaftPositionState->toothed_previous_duration = currentDuration;
	shaftPositionState->toothed_previous_time = now;

}

void initTriggerDecoder(void) {
	cbInit(&errorDetection);
}

