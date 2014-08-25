/**
 * @file	trigger_decoder.cpp
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"
#include "obd_error_codes.h"
#include "trigger_decoder.h"
#include "cyclic_buffer.h"
#include "trigger_mazda.h"
#include "trigger_chrysler.h"
#include "trigger_gm.h"
#include "trigger_bmw.h"
#include "trigger_mitsubishi.h"

#include "trigger_structure.h"

#if (EFI_PROD_CODE || EFI_SIMULATOR) || defined(__DOXYGEN__)
static Logging logger;
#endif

static cyclic_buffer errorDetection;

/**
 * @return TRUE is something is wrong with trigger decoding
 */
int isTriggerDecoderError(void) {
	return errorDetection.sum(6) > 4;
}

static inline bool isSynchronizationGap(TriggerState const *shaftPositionState, trigger_shape_s const *triggerShape,
		const int currentDuration) {
	if (!triggerShape->isSynchronizationNeeded) {
		return false;
	}

	return currentDuration > shaftPositionState->toothed_previous_duration * triggerShape->syncRatioFrom
			&& currentDuration < shaftPositionState->toothed_previous_duration * triggerShape->syncRatioTo;
}

static inline bool noSynchronizationResetNeeded(TriggerState *shaftPositionState, trigger_shape_s const *triggerShape) {
	if (triggerShape->isSynchronizationNeeded) {
		return false;
	}
	if (!shaftPositionState->shaft_is_synchronized) {
		return true;
	}
	/**
	 * in case of noise the counter could be above the expected number of events
	 */
	return shaftPositionState->getCurrentIndex() >= triggerShape->shaftPositionEventCount - 1;
}

static trigger_wheel_e eventIndex[6] = { T_PRIMARY, T_PRIMARY, T_SECONDARY, T_SECONDARY, T_CHANNEL_3, T_CHANNEL_3 };
static trigger_value_e eventType[6] = { TV_LOW, TV_HIGH, TV_LOW, TV_HIGH, TV_LOW, TV_HIGH };

/**
 * @brief Trigger decoding happens here
 * This method changes the state of trigger_state_s data structure according to the trigger event
 */
void TriggerState::decodeTriggerEvent(trigger_shape_s const*triggerShape, trigger_config_s const*triggerConfig,
		trigger_event_e const signal, uint64_t nowUs) {
	efiAssertVoid(signal <= SHAFT_3RD_UP, "unexpected signal");

	trigger_wheel_e triggerWheel = eventIndex[signal];

	eventCount[triggerWheel]++;

	int isLessImportant = (triggerShape->useRiseEdge && signal != SHAFT_PRIMARY_UP)
			|| (!triggerShape->useRiseEdge && signal != SHAFT_PRIMARY_DOWN);

	if (isLessImportant) {
		/**
		 * For less important events we simply increment the index.
		 */
		nextTriggerEvent(triggerWheel, nowUs);
		return;
	}

	int64_t currentDuration = isFirstEvent ? 0 : nowUs - toothed_previous_time;
	isFirstEvent = false;
	efiAssertVoid(currentDuration >= 0, "decode: negative duration?");

// todo: skip a number of signal from the beginning

#if EFI_PROD_CODE
//	scheduleMsg(&logger, "from %f to %f %d %d", triggerConfig->syncRatioFrom, triggerConfig->syncRatioTo, currentDuration, shaftPositionState->toothed_previous_duration);
//	scheduleMsg(&logger, "ratio %f", 1.0 * currentDuration/ shaftPositionState->toothed_previous_duration);
#else
	if (toothed_previous_duration != 0) {
//		printf("ratio %f: cur=%d pref=%d\r\n", 1.0 * currentDuration / shaftPositionState->toothed_previous_duration,
//				currentDuration, shaftPositionState->toothed_previous_duration);
	}
#endif

	if (noSynchronizationResetNeeded(this, triggerShape) || isSynchronizationGap(this, triggerShape, currentDuration)) {
		/**
		 * We can check if things are fine by comparing the number of events in a cycle with the expected number of event.
		 */
		bool isDecodingError = eventCount[0] != triggerShape->expectedEventCount[0]
				|| eventCount[1] != triggerShape->expectedEventCount[1]
				|| eventCount[2] != triggerShape->expectedEventCount[2];

		errorDetection.add(isDecodingError);

		if (isTriggerDecoderError()) {
			warning(OBD_PCM_Processor_Fault, "trigger decoding issue. expected %d/%d/%d got %d/%d/%d",
					triggerShape->expectedEventCount[0], triggerShape->expectedEventCount[1],
					triggerShape->expectedEventCount[2], eventCount[0], eventCount[1], eventCount[2]);
		}

		shaft_is_synchronized = true;
		// this call would update duty cycle values
//		nextTriggerEvent(triggerWheel, nowUs);

		nextRevolution(triggerShape->shaftPositionEventCount, nowUs);
	} else {
		nextTriggerEvent(triggerWheel, nowUs);
	}

	toothed_previous_duration = currentDuration;
	toothed_previous_time = nowUs;
}

static void initializeSkippedToothTriggerShape(trigger_shape_s *s, int totalTeethCount, int skippedCount,
		operation_mode_e operationMode) {
	efiAssertVoid(s != NULL, "trigger_shape_s is NULL");
	s->reset(operationMode);

	float toothWidth = 0.5;

	for (int i = 0; i < totalTeethCount - skippedCount - 1; i++) {
		float angleDown = 720.0 / totalTeethCount * (i + toothWidth);
		float angleUp = 720.0 / totalTeethCount * (i + 1);
		s->addEvent(angleDown, T_PRIMARY, TV_HIGH);
		s->addEvent(angleUp, T_PRIMARY, TV_LOW);
	}

	float angleDown = 720.0 / totalTeethCount * (totalTeethCount - skippedCount - 1 + toothWidth);
	s->addEvent(angleDown, T_PRIMARY, TV_HIGH);
	s->addEvent(720, T_PRIMARY, TV_LOW);
}

void initializeSkippedToothTriggerShapeExt(trigger_shape_s *s, int totalTeethCount, int skippedCount,
		operation_mode_e operationMode) {
	efiAssertVoid(totalTeethCount > 0, "totalTeethCount is zero");

	s->totalToothCount = totalTeethCount;
	s->skippedToothCount = skippedCount;
	initializeSkippedToothTriggerShape(s, totalTeethCount, skippedCount, operationMode);

	s->shaftPositionEventCount = ((totalTeethCount - skippedCount) * 2);
	s->wave.checkSwitchTimes(s->getSize());
}

static void configureFordAspireTriggerShape(trigger_config_s *triggerConfig, trigger_shape_s * s) {
	s->isSynchronizationNeeded = false;
	s->reset(FOUR_STROKE_CAM_SENSOR);

	s->shaftPositionEventCount = 10;

	s->addEvent(53.747, T_SECONDARY, TV_HIGH);
	s->addEvent(121.90, T_SECONDARY, TV_LOW); // delta = 68.153
	s->addEvent(232.76, T_SECONDARY, TV_HIGH); // delta = 110.86
	s->addEvent(300.54, T_SECONDARY, TV_LOW); // delta = 67.78
	s->addEvent(360, T_PRIMARY, TV_HIGH);

	s->addEvent(409.8412, T_SECONDARY, TV_HIGH); // delta = 49.8412
	s->addEvent(478.6505, T_SECONDARY, TV_LOW); // delta = 68.8093
	s->addEvent(588.045, T_SECONDARY, TV_HIGH); // delta = 109.3945
	s->addEvent(657.03, T_SECONDARY, TV_LOW);
	s->addEvent(720, T_PRIMARY, TV_LOW);
}

/**
 * External logger is needed because at this point our logger is not yet initialized
 */
void initializeTriggerShape(Logging *logger, engine_configuration_s *engineConfiguration,
		engine_configuration2_s *engineConfiguration2) {
#if EFI_PROD_CODE
	scheduleMsg(logger, "initializeTriggerShape()");
#endif
	trigger_config_s *triggerConfig = &engineConfiguration->triggerConfig;
	trigger_shape_s *triggerShape = &engineConfiguration2->triggerShape;

	setTriggerSynchronizationGap(triggerShape, 2);
	triggerShape->useRiseEdge = TRUE;

	switch (triggerConfig->triggerType) {

	case TT_TOOTHED_WHEEL:
		// todo: move to into configuration definition		engineConfiguration2->triggerShape.needSecondTriggerInput = false;

		engineConfiguration2->triggerShape.isSynchronizationNeeded =
				engineConfiguration->triggerConfig.customIsSynchronizationNeeded;

		initializeSkippedToothTriggerShapeExt(triggerShape, triggerConfig->customTotalToothCount,
				triggerConfig->customSkippedToothCount, getOperationMode(engineConfiguration));
		return;

	case TT_MAZDA_MIATA_NB:
		initializeMazdaMiataNbShape(triggerShape);
		return;

	case TT_DODGE_NEON:
		configureNeonTriggerShape(triggerShape);
		return;

	case TT_FORD_ASPIRE:
		configureFordAspireTriggerShape(triggerConfig, triggerShape);
		return;

	case TT_GM_7X:
		configureGmTriggerShape(triggerConfig, triggerShape);
		return;

	case TT_FORD_ESCORT_GT:
		configureMazdaProtegeLx(triggerShape);
		return;

	case TT_MINI_COOPER_R50:
		configureMiniCooperTriggerShape(triggerShape);
		return;

	case TT_TOOTHED_WHEEL_60_2:
		setToothedWheelConfiguration(triggerShape, 60, 2, engineConfiguration);
		setTriggerSynchronizationGap(triggerShape, 2.5);
		return;

	case TT_TOOTHED_WHEEL_36_1:
		setToothedWheelConfiguration(triggerShape, 36, 1, engineConfiguration);
		return;

	case TT_HONDA_ACCORD_CD_TWO_WIRES:
		configureHondaAccordCD(triggerShape, false);
		return;

	case TT_HONDA_ACCORD_CD:
		configureHondaAccordCD(triggerShape, true);
		return;

	case TT_HONDA_ACCORD_CD_DIP:
		configureHondaAccordCDDip(triggerShape);
		return;

	case TT_MITSU:
		initializeMitsubishi4g18(triggerShape);
		return;

	default:
		firmwareError("initializeTriggerShape() not implemented: %d", triggerConfig->triggerType);
		;
	}
	if (engineConfiguration2->triggerShape.shaftPositionEventCount != engineConfiguration2->triggerShape.getSize())
		firmwareError("trigger size or shaftPositionEventCount?");
}

TriggerStimulatorHelper::TriggerStimulatorHelper() {
	primaryWheelState = false;
	secondaryWheelState = false;
}

void TriggerStimulatorHelper::nextStep(TriggerState *state, trigger_shape_s * shape, int i,
		trigger_config_s const*triggerConfig) {
	int stateIndex = i % shape->getSize();

	int loopIndex = i / shape->getSize();

	int time = (int) (100000 * (loopIndex + shape->wave.getSwitchTime(stateIndex)));

	bool newPrimaryWheelState = shape->wave.getChannelState(0, stateIndex);
	bool newSecondaryWheelState = shape->wave.getChannelState(1, stateIndex);

	if (primaryWheelState != newPrimaryWheelState) {
		primaryWheelState = newPrimaryWheelState;
		trigger_event_e s = primaryWheelState ? SHAFT_PRIMARY_UP : SHAFT_PRIMARY_DOWN;
		state->decodeTriggerEvent(shape, triggerConfig, s, time);
	}

	if (secondaryWheelState != newSecondaryWheelState) {
		secondaryWheelState = newSecondaryWheelState;
		trigger_event_e s = secondaryWheelState ? SHAFT_SECONDARY_UP : SHAFT_SECONDARY_DOWN;
		state->decodeTriggerEvent(shape, triggerConfig, s, time);
	}
}

static void onFindIndex(TriggerState *state) {
	for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++) {
		// todo: that's not the best place for this intermediate data storage, fix it!
		state->expectedTotalTime[i] = state->totalTime[i];
	}
}

static uint32_t doFindTrigger(TriggerStimulatorHelper *helper, trigger_shape_s * shape,
		trigger_config_s const*triggerConfig, TriggerState *state) {
	for (int i = 0; i < 4 * PWM_PHASE_MAX_COUNT; i++) {
		helper->nextStep(state, shape, i, triggerConfig);

		if (state->shaft_is_synchronized)
			return i;
	}
	firmwareError("findTriggerZeroEventIndex() failed");
	return EFI_ERROR_CODE;
}

/**
 * Trigger shape is defined in a way which is convenient for trigger shape definition
 * On the other hand, trigger decoder indexing begins from synchronization event.
 *
 * This function finds the index of synchronization event within trigger_shape_s
 */
uint32_t findTriggerZeroEventIndex(trigger_shape_s * shape, trigger_config_s const*triggerConfig) {

	TriggerState state;
	errorDetection.clear();

	TriggerStimulatorHelper helper;

	uint32_t index = doFindTrigger(&helper, shape, triggerConfig, &state);
	if (index == EFI_ERROR_CODE) {
		return index;
	}
	efiAssert(state.getTotalRevolutionCounter() == 1, "totalRevolutionCounter", EFI_ERROR_CODE);

	/**
	 * Now that we have just located the synch point, we can simulate the whole cycle
	 * in order to calculate expected duty cycle
	 */
	state.cycleCallback = onFindIndex;
	for (uint32_t i = index + 1; i <= index + 2 * shape->getSize(); i++) {
		helper.nextStep(&state, shape, i, triggerConfig);
	}
	efiAssert(state.getTotalRevolutionCounter() > 1, "totalRevolutionCounter2", EFI_ERROR_CODE);

	for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++) {
		shape->expectedTotalTime[i] = state.expectedTotalTime[i];
	}


	return index % shape->getSize();
}

void initTriggerDecoder(void) {
#if EFI_PROD_CODE || EFI_SIMULATOR
	initLogging(&logger, "trigger decoder");
#endif
}

