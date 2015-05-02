/**
 * @file	trigger_decoder.h
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef TRIGGER_DECODER_H_
#define TRIGGER_DECODER_H_

#include "main.h"
#include "trigger_structure.h"
#include "engine_configuration.h"

class TriggerState;

typedef void (*TriggerStateCallback)(TriggerState *);

class TriggerState {
public:
	TriggerState();
	int getCurrentIndex();
	int getTotalRevolutionCounter();
	uint64_t getTotalEventCounter();
	uint64_t getStartOfRevolutionIndex();
	void decodeTriggerEvent(trigger_event_e const signal, uint64_t nowUs DECLARE_ENGINE_PARAMETER_S);

	float getTriggerDutyCycle(int index);
	TriggerStateCallback cycleCallback;

	/**
	 * TRUE if we know where we are
	 */
	bool shaft_is_synchronized;

	uint32_t toothed_previous_duration;
	/**
	 * this could be a local variable, but it's better for debugging to have it as a field
	 */
	uint32_t currentDuration;
	uint64_t toothed_previous_time;

	/**
	 * Here we accumulate the amount of time this signal was ON within current trigger cycle
	 */
	int totalTimeNt[PWM_PHASE_MAX_WAVE_PER_PWM];
	/**
	 * Total time result for previous trigger cycle
	 */
	uint32_t prevTotalTime[PWM_PHASE_MAX_WAVE_PER_PWM];
	int expectedTotalTime[PWM_PHASE_MAX_WAVE_PER_PWM];
	uint32_t totalTriggerErrorCounter;
	uint32_t runningTriggerErrorCounter;
	uint32_t orderingErrorCounter;
	uint32_t runningOrderingErrorCounter;

	void resetRunningCounters();


	/**
	 * index within trigger revolution, from 0 to trigger event count
	 */
	uint32_t current_index;
	uint32_t runningRevolutionCounter;
private:
	void clear();
	/**
	 * Number of actual events within current trigger cycle
	 * see TriggerShape
	 */
	uint32_t eventCount[PWM_PHASE_MAX_WAVE_PER_PWM];
	trigger_event_e curSignal;
	trigger_event_e prevSignal;
	uint32_t eventCountExt[2 * PWM_PHASE_MAX_WAVE_PER_PWM];
	uint64_t timeOfPreviousEventNt[PWM_PHASE_MAX_WAVE_PER_PWM];
	uint64_t totalEventCountBase;
	uint32_t totalRevolutionCounter;
	bool isFirstEvent;
	uint64_t prevCycleDuration;
	uint64_t startOfCycleNt;
};

class TriggerStimulatorHelper {
public:
	TriggerStimulatorHelper();
	void nextStep(TriggerState *state, TriggerShape * shape, int i, trigger_config_s const*triggerConfig DECLARE_ENGINE_PARAMETER_S);
};

float getEngineCycle(operation_mode_e operationMode);
void addSkippedToothTriggerEvents(trigger_wheel_e wheel, TriggerShape *s,
		int totalTeethCount, int skippedCount,
		float toothWidth,
		float offset, float engineCycle, float filterLeft, float filterRight);
void initializeSkippedToothTriggerShapeExt(TriggerShape *s, int totalTeethCount, int skippedCount, operation_mode_e operationMode);
uint32_t findTriggerZeroEventIndex(TriggerShape * shape, trigger_config_s const*triggerConfig DECLARE_ENGINE_PARAMETER_S);

class Engine;

void initializeTriggerShape(Logging *logger, engine_configuration_s const *engineConfiguration, Engine *engine);
void initTriggerDecoder(void);
void initTriggerDecoderLogger(Logging *sharedLogger);

bool_t isTriggerDecoderError(void);

#define isLessImportant(signal) ((TRIGGER_SHAPE(useRiseEdge) && signal != SHAFT_PRIMARY_UP) \
		|| (!TRIGGER_SHAPE(useRiseEdge) && signal != SHAFT_PRIMARY_DOWN))


#endif /* TRIGGER_DECODER_H_ */
