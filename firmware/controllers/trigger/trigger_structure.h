/**
 * @file	trigger_structure.h
 *
 * @date Dec 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef TRIGGER_STRUCTURE_H_
#define TRIGGER_STRUCTURE_H_

#include <stdint.h>

#include "rusefi_enums.h"
#include "EfiWave.h"
#include "engine_configuration.h"

class trigger_shape_s;

class TriggerState {
public:
	TriggerState();
	int getCurrentIndex();
	int getTotalRevolutionCounter();
	uint64_t getTotalEventCounter();
	uint64_t getStartOfRevolutionIndex();
	void nextRevolution(int triggerEventCount);
	void nextTriggerEvent();
	void decodeTriggerEvent(trigger_shape_s const*triggerShape, trigger_config_s const*triggerConfig, trigger_event_e signal, uint64_t nowUs);


	/**
	 * TRUE if we know where we are
	 */
	unsigned char shaft_is_synchronized;

	uint64_t toothed_previous_duration;
	uint64_t toothed_previous_time;
private:
	void clear();
	/**
	 * index within trigger revolution, from 0 to trigger event count
	 */
	int current_index;
	uint64_t totalEventCountBase;
	int totalRevolutionCounter;
	bool isFirstEvent;
};

typedef enum {
	TV_LOW = 0,
	TV_HIGH = 1
} trigger_value_e;

typedef enum {
	T_PRIMARY = 0,
	T_SECONDARY = 1,
	// todo: I really do not want to call this 'tertiary'. maybe we should rename all of these?
	T_CHANNEL_3 = 2
} trigger_wheel_e;

#define TRIGGER_CHANNEL_COUNT 3

class trigger_shape_helper {
	int pinStates[TRIGGER_CHANNEL_COUNT][PWM_PHASE_MAX_COUNT];
public:
	trigger_shape_helper();

	single_wave_s waves[TRIGGER_CHANNEL_COUNT];
};

class trigger_shape_s {
public:
	trigger_shape_s();
	int isSynchronizationNeeded;

	int totalToothCount;
	int skippedToothCount;

	float syncRatioFrom;
	float syncRatioTo;

	int useRiseEdge;

	bool needSecondTriggerInput;
	void addEvent(float angle, trigger_wheel_e waveIndex, trigger_value_e state);
	void reset(operation_mode_e operationMode);
	int getSize();
	multi_wave_s wave;

	/**
	 * Total count of shaft events per CAM or CRANK shaft revolution.
	 * TODO this should be migrated to CRANKshaft revolution, this would go together
	 * TODO with eliminating RPM_MULT magic constant
	 */
	int shaftPositionEventCount;

	// todo: add a runtime validation which would verify that this field was set properly
	// tood: maybe even automate this flag calculation?
	int initialState[PWM_PHASE_MAX_WAVE_PER_PWM];

	int getTriggerShapeSynchPointIndex();

	void calculateTriggerSynchPoint(trigger_config_s const*triggerConfig);

	void setTriggerShapeSynchPointIndex(int triggerShapeSynchPointIndex);
	/**
	 * These angles are in event coordinates - with synchronization point located at angle zero.
	 * These values are pre-calculated for performance reasons.
	 */
	float eventAngles[PWM_PHASE_MAX_COUNT];

private:
	trigger_shape_helper h;
	int size;
	/**
	 * index of synchronization event within trigger_shape_s
	 * See findTriggerZeroEventIndex()
	 */
	int triggerShapeSynchPointIndex;
	/**
	 * Values are in the 0..1 range
	 */
	float switchTimesBuffer[PWM_PHASE_MAX_COUNT];
	/**
	 * These are the same values as in switchTimes, but these are angles in the 0..360 or 0..720 range.
	 * That's a performance optimization - this should save as one multiplication in a critical spot.
	 *
	 * These angles are in trigger DESCRIPTION coordinates - i.e. the way you add events while declaring trigger shape
	 */
	float switchAngles[PWM_PHASE_MAX_COUNT];

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

	void setSwitchTime(int index, float angle);
	int getCycleDuration();
};

void setTriggerSynchronizationGap(trigger_shape_s *s, float synchGap);
void setToothedWheelConfiguration(trigger_shape_s *s, int total, int skipped, engine_configuration_s const *engineConfiguration);

#endif /* TRIGGER_STRUCTURE_H_ */
