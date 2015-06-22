/**
 * @file	trigger_structure.h
 *
 * @date Dec 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef TRIGGER_STRUCTURE_H_
#define TRIGGER_STRUCTURE_H_

#include "main.h"

#include "rusefi_enums.h"
#include "EfiWave.h"
#include "engine_configuration.h"

class TriggerShape;

#define TRIGGER_CHANNEL_COUNT 3

class trigger_shape_helper {
	pin_state_t pinStates[TRIGGER_CHANNEL_COUNT][PWM_PHASE_MAX_COUNT];
public:
	trigger_shape_helper();

	single_wave_s waves[TRIGGER_CHANNEL_COUNT];
};

class Engine;

class TriggerShape {
public:
	TriggerShape();
	void initializeTriggerShape(Logging *logger DECLARE_ENGINE_PARAMETER_S);

	bool_t isSynchronizationNeeded;
	bool_t needSecondTriggerInput;

	int totalToothCount;
	int skippedToothCount;

	float dutyCycle[PWM_PHASE_MAX_WAVE_PER_PWM];

	/**
	 * this cache allows us to find a close-enough (with one degree precision) trigger wheel index by
	 * given angle with fast constant speed
	 */
	int triggerIndexByAngle[720];

	float syncRatioFrom;
	float syncRatioTo;

	/**
	 * that's the angle distance from trigger event #0 and actual engine TDC
	 * see also globalTriggerAngleOffset
	 */
	angle_t tdcPosition;

	/**
	 * Should we use falls or rises for gap ratio detection?
	 */
	bool_t useRiseEdge;
	/**
	 * Should we measure gaps with events of both kinds?
	 */
	bool_t gapBothDirections;

	/**
	 * This is used for signal validation
	 */
	uint32_t expectedEventCount[PWM_PHASE_MAX_WAVE_PER_PWM];

	multi_wave_s wave;

	// todo: add a runtime validation which would verify that this field was set properly
	// tood: maybe even automate this flag calculation?
	int initialState[PWM_PHASE_MAX_WAVE_PER_PWM];

	/**
	 * These angles are in event coordinates - with synchronization point located at angle zero.
	 * These values are pre-calculated for performance reasons.
	 */
	float eventAngles[PWM_PHASE_MAX_COUNT];

	int8_t isFrontEvent[PWM_PHASE_MAX_COUNT];
	/**
	 * this table translates trigger definition index into 'front-only' index. This translation is not so trivial
	 * in case of a multi-channel signal with overlapping waves, for example Ford Aspire/Mitsubishi
	 */
	int frontOnlyIndexes[PWM_PHASE_MAX_COUNT];

	bool_t invertOnAdd;
	/**
	 * Total count of shaft events per CAM or CRANK shaft revolution.
	 * TODO this should be migrated to CRANKshaft revolution, this would go together
	 * TODO: rename to triggerDefinitionSize ?
	 */
	int size;

	void addEvent(float angle, trigger_wheel_e const waveIndex, trigger_value_e const state);
	void addEvent(float angle, trigger_wheel_e const waveIndex, trigger_value_e const stateParam, float filterLeft, float filterRight);
	operation_mode_e getOperationMode();

	// todo: these two methods here, something could be improved
	void clear();
	void reset(operation_mode_e operationMode, bool needSecondTriggerInput);
	void setTriggerSynchronizationGap2(float syncRatioFrom, float syncRatioTo);
	void setTriggerSynchronizationGap(float synchRatio);
	/**
	 * this one is per CRANKshaft revolution
	 */
	uint32_t getLength() const;
	int getSize() const;

	int getTriggerShapeSynchPointIndex();

	void calculateTriggerSynchPoint(DECLARE_ENGINE_PARAMETER_F);

private:

	trigger_shape_helper h;

	/**
	 * index of synchronization event within TriggerShape
	 * See findTriggerZeroEventIndex()
	 */
	int triggerShapeSynchPointIndex;
	/**
	 * Values are in the 0..1 range
	 */
	float switchTimesBuffer[PWM_PHASE_MAX_COUNT];
	/**
	 * These angles are in trigger DESCRIPTION coordinates - i.e. the way you add events while declaring trigger shape
	 */
	float getSwitchAngle(int index) const;

	float previousAngle;
	/**
	 * this is part of performance optimization
	 */
	operation_mode_e operationMode;

	/**
	 * This private method should only be used to prepare the array of pre-calculated values
	 * See eventAngles array
	 */
	float getAngle(int phaseIndex) const;

	int getCycleDuration() const;
};

void setToothedWheelConfiguration(TriggerShape *s, int total, int skipped, operation_mode_e operationMode);

#endif /* TRIGGER_STRUCTURE_H_ */
