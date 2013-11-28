/**
 * @file	event_registry.c
 *
 * @date Nov 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "event_registry.h"
#include "main.h"

void resetEventList(ActuatorEventList *list) {
	list->size = 0;
}

static void copyActuatorEvent(ActuatorEvent *source, ActuatorEvent*target) {
	target->eventIndex = source->eventIndex;
	target->actuatorId = source->actuatorId;
	target->angleOffset = source->angleOffset;
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
	resetEventList(target);
	// todo: implement something faster
	for (int i = 0; i < source->size; i++) {
		ActuatorEvent *s = &source->events[i];
		if (s->eventIndex != eventIndex)
			continue;
		// todo: migrate to pointers instead of copying an object?
		copyActuatorEvent(s, &target->events[target->size++]);
	}
}
