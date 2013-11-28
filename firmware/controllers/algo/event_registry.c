/**
 * @file	event_registry.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "event_registry.h"
#include "main.h"

void resetEventList(ActuatorEventList *list) {
	list->size = 0;
}

void registerActuatorEvent(ActuatorEventList *list, int eventIndex, int actuatorId, float angleOffset) {
	if (list->size == MAX_EVENT_COUNT) {
		fatal("registerActuatorEvent");
		return;
	}
	ActuatorEvent *e = &list->events[list->size++];
	e->eventIndex = eventIndex;
	e->actuatorId = actuatorId;
	e->angleOffset = angleOffset;
}

void findEvents(int eventIndex, ActuatorEventList *source, ActuatorEventList *target) {

}
