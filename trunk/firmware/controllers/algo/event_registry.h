/**
 * @file	event_registry.h
 *
 *  Created on: Nov 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef EVENT_REGISTRY_H_
#define EVENT_REGISTRY_H_

#define MAX_EVENT_COUNT 40

typedef struct {
	int eventIndex;
	int actuatorId;
	float angleOffset;
} ActuatorEvent;

typedef struct {
	int size;
	ActuatorEvent events[MAX_EVENT_COUNT];
} ActuatorEventList;

void resetEventList(ActuatorEventList *list);

/**
 * this is an intermediate implementation of flexible event handling.
 *
 * In the future implementation we will drop the 'eventIndex' parameter and everything will be
 * angle-driven. But that's just a plan for next iteration.
 *
 * @param	actuatorId injector ID or coil ID
 */
void registerActuatorEvent(ActuatorEventList *list, int eventIndex, int actuatorId, float angleOffset);

void findEvents(int eventIndex, ActuatorEventList *source, ActuatorEventList *target);

#endif /* EVENT_REGISTRY_H_ */
