/**
 * @file	trigger_decoder.c
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "trigger_decoder.h"
#include "cyclic_buffer.h"
#include "trigger_mazda.h"
#if EFI_PROD_CODE
#include "datalogging.h"
static Logging logger;
#endif

static cyclic_buffer errorDetection;

/**
 * @return TRUE is something is wrong with trigger decoding
 */
int isTriggerDecoderError(void) {
	return cbSum(&errorDetection, 6) > 4;
}

static inline int isSynchronizationGap(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape,
		trigger_config_s *triggerConfig, int currentDuration) {
	if (!triggerConfig->isSynchronizationNeeded)
		return FALSE;

	return currentDuration > shaftPositionState->toothed_previous_duration * triggerConfig->syncRatioFrom
			&& currentDuration < shaftPositionState->toothed_previous_duration * triggerConfig->syncRatioTo;
}

static inline int noSynchronizationResetNeeded(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape,
		trigger_config_s *triggerConfig) {
	if (triggerConfig->isSynchronizationNeeded)
		return FALSE;
	if (!shaftPositionState->shaft_is_synchronized)
		return TRUE;
	return shaftPositionState->current_index == triggerShape->shaftPositionEventCount - 1;
}

/**
 * @brief This method changes the state of trigger_state_s data structure according to the trigger event
 */
void processTriggerEvent(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape,
		trigger_config_s *triggerConfig, ShaftEvents signal, time_t now) {

	int isLessImportant = (triggerConfig->useRiseEdge && signal != SHAFT_PRIMARY_UP)
			|| (!triggerConfig->useRiseEdge && signal != SHAFT_PRIMARY_DOWN);

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
//	scheduleMsg(&logger, "from %f to %f %d %d", triggerConfig->syncRatioFrom, triggerConfig->syncRatioTo, currentDuration, shaftPositionState->toothed_previous_duration);
//	scheduleMsg(&logger, "ratio %f", 1.0 * currentDuration/ shaftPositionState->toothed_previous_duration);
#else
	if (shaftPositionState->toothed_previous_duration != 0) {
		printf("ratio %f: cur=%d pref=%d\r\n", 1.0 * currentDuration / shaftPositionState->toothed_previous_duration,
				currentDuration, shaftPositionState->toothed_previous_duration);
	}
#endif

	if (noSynchronizationResetNeeded(shaftPositionState, triggerShape, triggerConfig)
			|| isSynchronizationGap(shaftPositionState, triggerShape, triggerConfig, currentDuration)) {
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
		triggerAddEvent(s, angleDown, T_PRIMARY, TV_HIGH);
		triggerAddEvent(s, angleUp, T_PRIMARY, TV_LOW);
	}

	float angleDown = 720.0 / totalTeethCount * (totalTeethCount - skippedCount - 1 + toothWidth);
	triggerAddEvent(s, angleDown, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 720, T_PRIMARY, TV_LOW);
}

void initializeSkippedToothTriggerShapeExt(engine_configuration2_s *engineConfiguration2, int totalTeethCount,
		int skippedCount) {
	trigger_shape_s *s = &engineConfiguration2->triggerShape;
	initializeSkippedToothTriggerShape(s, totalTeethCount, skippedCount);

	engineConfiguration2->triggerShape.shaftPositionEventCount = ((totalTeethCount - skippedCount) * 2);
	checkSwitchTimes(s->size, s->wave.switchTimes);
}

static void configureNeonTriggerShape(trigger_shape_s *s) {
	triggerShapeInit(s);

	triggerAddEvent(s, 60, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 210, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 420, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 630, T_PRIMARY, TV_LOW);
	// voodoo magic - we always need 720 at the end
	triggerAddEvent(s, 720, T_PRIMARY, TV_LOW);

	s->shaftPositionEventCount = 4;
}

static void confgiureFordAspireTriggerShape(trigger_shape_s * s) {
	triggerShapeInit(s);

	s->shaftPositionEventCount = 10;


	triggerAddEvent(s, 53.747, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 121.90, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 232.76, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 300.54, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 360, T_PRIMARY, TV_HIGH);

	triggerAddEvent(s, 409.8412, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 478.6505, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 588.045, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 657.03, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 720, T_PRIMARY, TV_LOW);
}


void initializeTriggerShape(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	trigger_config_s *tt = &engineConfiguration->triggerConfig;
	switch (tt->triggerType) {

	case TT_TOOTHED_WHEEL:
		initializeSkippedToothTriggerShapeExt(engineConfiguration2, tt->totalToothCount, tt->skippedToothCount);
		return;

	case TT_MAZDA_MIATA_NB:
		initializeMazdaMiataNbShape(&engineConfiguration2->triggerShape);
		return;

	case TT_DODGE_NEON:
		configureNeonTriggerShape(&engineConfiguration2->triggerShape);
		return;

	case TT_FORD_ASPIRE:
		confgiureFordAspireTriggerShape(&engineConfiguration2->triggerShape);
		return;

	default:
		fatal("not implemented")
		;
	}
}

void initTriggerDecoder(void) {
#if EFI_PROD_CODE
	initLogging(&logger, "trigger decoder");
#endif

cbInit(&errorDetection);
}

