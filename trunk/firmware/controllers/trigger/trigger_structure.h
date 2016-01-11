/**
 * @file	trigger_structure.h
 *
 * @date Dec 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef TRIGGER_STRUCTURE_H_
#define TRIGGER_STRUCTURE_H_

#include "main.h"

#include "rusefi_enums.h"
#include "EfiWave.h"
#include "engine_configuration.h"

#define TRIGGER_CHANNEL_COUNT 3

class trigger_shape_helper {
public:
	trigger_shape_helper();

	single_wave_s waves[TRIGGER_CHANNEL_COUNT];
private:
	pin_state_t pinStates[TRIGGER_CHANNEL_COUNT][PWM_PHASE_MAX_COUNT];
};

class Engine;
class TriggerState;

/**
 * @brief Trigger shape has all the fields needed to describe and decode trigger signal.
 */
class TriggerShape {
public:
	TriggerShape();
	void initializeTriggerShape(Logging *logger DECLARE_ENGINE_PARAMETER_S);

	bool isSynchronizationNeeded;
	bool needSecondTriggerInput;

	/**
	 * duty cycle for each individual trigger channel
	 */
	float dutyCycle[PWM_PHASE_MAX_WAVE_PER_PWM];

	/**
	 * These angles are in event coordinates - with synchronization point located at angle zero.
	 * These values are pre-calculated for performance reasons.
	 */
	angle_t eventAngles[PWM_PHASE_MAX_COUNT];
	/**
	 * this cache allows us to find a close-enough (with one degree precision) trigger wheel index by
	 * given angle with fast constant speed. That's a performance optimization for event scheduling.
	 */
	int triggerIndexByAngle[720];

	float syncRatioFrom;
	float syncRatioTo;

	/**
	 * Usually this is not needed, but some crazy triggers like 36-2-2-2 require two consecutive
	 * gaps ratios to sync
	 */
	float secondSyncRatioFrom;
	float secondSyncRatioTo;

	float thirdSyncRatioFrom;
	float thirdSyncRatioTo;


	/**
	 * Trigger indexes within trigger cycle are counted from synchronization point, and all
	 * engine processes are defined in angles from TDC.
	 *
	 * That's the angle distance from trigger event #0 and actual engine TDC
	 *
	 * see also globalTriggerAngleOffset
	 */
	angle_t tdcPosition;

	/**
	 * In case of a multi-channel trigger, do we want to sync based on primary channel only?
	 * See also gapBothDirections
	 */
	bool useOnlyPrimaryForSync;
	/**
	 * Should we use falls or rises for gap ratio detection?
	 * todo: combine this flag with gapBothDirections?
	 */
	bool useRiseEdge;
	/**
	 * This is about selecting signal edges within partictular trigger channels.
	 * Should we measure gaps with both fall and rise signal edges?
	 * See also useOnlyPrimaryForSync
	 */
	bool gapBothDirections;

	/**
	 * This is used for signal validation
	 */
	uint32_t expectedEventCount[PWM_PHASE_MAX_WAVE_PER_PWM];

#if EFI_UNIT_TEST || defined(__DOXYGEN__)
	/**
	 * These signals are used for trigger export only
	 */
	int triggerSignals[PWM_PHASE_MAX_COUNT];
#endif

	multi_wave_s wave;

	// todo: add a runtime validation which would verify that this field was set properly
	// tood: maybe even automate this flag calculation?
	int initialState[PWM_PHASE_MAX_WAVE_PER_PWM];

	int8_t isFrontEvent[PWM_PHASE_MAX_COUNT];
	/**
	 * this table translates trigger definition index into 'front-only' index. This translation is not so trivial
	 * in case of a multi-channel signal with overlapping waves, for example Ford Aspire/Mitsubishi
	 */
	int frontOnlyIndexes[PWM_PHASE_MAX_COUNT];

	/**
	 * This is a pretty questionable option which is considered by 'addEvent' method
	 */
	bool invertOnAdd;
	/**
	 * Total count of shaft events per CAM or CRANK shaft revolution.
	 * TODO this should be migrated to CRANKshaft revolution, this would go together
	 * TODO: rename to triggerDefinitionSize ?
	 */
	int size;

	void addEvent2(angle_t angle, trigger_wheel_e const waveIndex, trigger_value_e const state DECLARE_ENGINE_PARAMETER_S);
	void addEvent(angle_t angle, trigger_wheel_e const waveIndex, trigger_value_e const state);
	void addEvent(angle_t angle, trigger_wheel_e const waveIndex, trigger_value_e const stateParam, float filterLeft, float filterRight);
	operation_mode_e getOperationMode();

	void initialize(operation_mode_e operationMode, bool needSecondTriggerInput);
	void setTriggerSynchronizationGap(float syncRatio);
	void setTriggerSynchronizationGap2(float syncRatioFrom, float syncRatioTo);
	void setSecondTriggerSynchronizationGap(float syncRatio);
	void setSecondTriggerSynchronizationGap2(float syncRatioFrom, float syncRatioTo);
	void setThirdTriggerSynchronizationGap(float syncRatio);
	void setThirdTriggerSynchronizationGap2(float syncRatioFrom, float syncRatioTo);
	/**
	 * this one is per CRANKshaft revolution
	 */
	uint32_t getLength() const;
	int getSize() const;

	int getTriggerShapeSynchPointIndex();

private:
	trigger_shape_helper h;

	/**
	 * index of synchronization event within TriggerShape
	 * See findTriggerZeroEventIndex()
	 */
	int triggerShapeSynchPointIndex;
	/**
	 * Working buffer for 'wave' instance
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
	void calculateTriggerSynchPoint(TriggerState *state DECLARE_ENGINE_PARAMETER_S);
};

void setVwConfiguration(TriggerShape *s);

void setToothedWheelConfiguration(TriggerShape *s, int total, int skipped, operation_mode_e operationMode);
void configureHondaAccordCD(TriggerShape *s, bool withOneEventSignal, bool withFourEventSignal,
		trigger_wheel_e const oneEventWave,
		trigger_wheel_e const fourEventWave,
		float d);

#endif /* TRIGGER_STRUCTURE_H_ */
