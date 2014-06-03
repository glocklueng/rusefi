/**
 * @file	event_registry.h
 *
 * @date Nov 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef EVENT_REGISTRY_H_
#define EVENT_REGISTRY_H_

#include "global.h"
#include "signal_executor.h"

#define MAX_EVENT_COUNT 40

/**
 * This structure defines an angle position within the trigger
 */
typedef struct {
	/**
	 * That's trigger event index
	 */
	int eventIndex;
	/**
	 * Angle offset from the trigger event
	 */
	float angleOffset;
} event_trigger_position_s;

typedef struct {
	event_trigger_position_s position;
	OutputSignal *actuator;
	scheduling_s signalTimer;
} ActuatorEvent;

template <class Type, int Dimention>
class ArrayList {
public:
	int size;
	Type events[Dimention];
	void resetEventList(void);
	Type *getNextActuatorEvent(void);
};

template <class Type, int Dimention>
void ArrayList< Type, Dimention>::resetEventList(void) {
	size = 0;
}

template <class Type, int Dimention>
Type * ArrayList< Type, Dimention>::getNextActuatorEvent(void) {
	efiAssert(size < Dimention, "registerActuatorEvent() too many events", NULL);
	return &events[size++];
}

typedef ArrayList<ActuatorEvent, MAX_EVENT_COUNT> ActuatorEventList;

/**
 * this is an intermediate implementation of flexible event handling.
 *
 * In the future implementation we will drop the 'eventIndex' parameter and everything will be
 * angle-driven. But that's just a plan for next iteration.
 *
 * @param	actuator injector or coil OutputSignal
 */
void registerActuatorEvent(ActuatorEventList *list, int eventIndex, OutputSignal *actuator, float angleOffset);

#endif /* EVENT_REGISTRY_H_ */
