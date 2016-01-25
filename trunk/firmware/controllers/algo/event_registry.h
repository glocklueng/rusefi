/**
 * @file	event_registry.h
 *
 * @date Nov 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef EVENT_REGISTRY_H_
#define EVENT_REGISTRY_H_

#include "global.h"
#include "signal_executor.h"
#include "fl_stack.h"

/**
 * This structure defines an angle position within the trigger
 */
class event_trigger_position_s {
public:
	event_trigger_position_s();
	/**
	 * That's trigger event index
	 */
	uint32_t eventIndex;
	angle_t eventAngle;
	/**
	 * Angle offset from the trigger event
	 */
	angle_t angleOffset;
};

class InjectionEvent {
public:
	InjectionEvent();
	/**
	 * This is a performance optimization - it's more efficient to handle all
	 * injectors together if that's the case
	 */
	bool isSimultanious;
	NamedOutputPin *output;
	int injectorIndex;

	event_trigger_position_s injectionStart;
};

class IgnitionEvent {
public:
	IgnitionEvent();
	NamedOutputPin *output;
	scheduling_s signalTimerUp;
	scheduling_s signalTimerDown;
	angle_t advance;
	event_trigger_position_s dwellPosition;
	event_trigger_position_s sparkPosition;
	IgnitionEvent *next;
	char *name;
};

#define MAX_INJECTION_OUTPUT_COUNT 45
#define MAX_IGNITION_EVENT_COUNT 80

typedef ArrayList<InjectionEvent, MAX_INJECTION_OUTPUT_COUNT> InjectionEventList;

typedef ArrayList<IgnitionEvent, MAX_IGNITION_EVENT_COUNT> IgnitionEventList;

#endif /* EVENT_REGISTRY_H_ */
