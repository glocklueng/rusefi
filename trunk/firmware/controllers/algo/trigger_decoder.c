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

static inline int isSynchronizationGap(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape,
		int currentDuration) {
	if (triggerShape->onlyOneTeeth)
			return FALSE;
	return currentDuration > shaftPositionState->toothed_previous_duration * triggerShape->syncRatioFrom
			&& currentDuration < shaftPositionState->toothed_previous_duration * triggerShape->syncRatioTo;
}

static inline int noSynchronizationResetNeeded(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape) {
	if (!triggerShape->onlyOneTeeth)
		return FALSE;
	if (!shaftPositionState->shaft_is_synchronized)
		return TRUE;
	return shaftPositionState->current_index == triggerShape->shaftPositionEventCount - 1;
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

	if (noSynchronizationResetNeeded(shaftPositionState, triggerShape)
			|| isSynchronizationGap(shaftPositionState, triggerShape, currentDuration)) {
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

static void initializeSkippedToothTriggerShape(trigger_shape_s *s, int totalTeethCount, int skippedCount) {
	triggerShapeInit(s);

	float toothWidth = 0.5;

	for (int i = 0; i < totalTeethCount - skippedCount - 1; i++) {
		float angleDown = 720.0 / totalTeethCount * (i + toothWidth);
		float angleUp = 720.0 / totalTeethCount * (i + 1);
		triggerAddEvent(s, angleDown, T_PRIMARY, 1);
		triggerAddEvent(s, angleUp, T_PRIMARY, 0);
	}

	float angleDown = 720.0 / totalTeethCount * (totalTeethCount - skippedCount - 1 + toothWidth);
	triggerAddEvent(s, angleDown, T_PRIMARY, 1);
	triggerAddEvent(s, 720, T_PRIMARY, 0);
}

void skippedToothTriggerShapeExt(engine_configuration2_s *engineConfiguration2, int totalTeethCount, int skippedCount) {
	trigger_shape_s *s = &engineConfiguration2->triggerShape;
	engineConfiguration2->triggerShape.shaftPositionEventCount = ((totalTeethCount - skippedCount) * 2);
	initializeSkippedToothTriggerShape(s, totalTeethCount, skippedCount);
	checkSwitchTimes(s->size, s->wave.switchTimes);
}

void initTriggerDecoder(void) {
	cbInit(&errorDetection);
}

