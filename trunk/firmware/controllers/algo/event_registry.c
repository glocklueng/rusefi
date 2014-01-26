/**
 * @file	event_registry.c
 *
 * @date Nov 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "event_registry.h"
#include "main.h"
#include "engine_configuration.h"

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

void resetEventList(ActuatorEventList *list) {
	list->size = 0;
}

static void copyActuatorEvent(ActuatorEvent *source, ActuatorEvent*target) {
	target->eventIndex = source->eventIndex;
	target->actuator = source->actuator;
	target->angleOffset = source->angleOffset;
}

void registerActuatorEventExt(ActuatorEventList *list, OutputSignal *actuator, float angleOffset) {
	trigger_shape_s * s = &engineConfiguration2->triggerShape;

	angleOffset = fixAngle(angleOffset + engineConfiguration->globalTriggerOffsetAngle);

	// todo: migrate to crankAngleRange?
	float firstAngle = s->wave.switchTimes[0] * 720;

	// let's find the last trigger angle which is less or equal to the desired angle
	int i;
	for (i = 0; i < s->size - 1; i++) {
		float angle = s->wave.switchTimes[i + 1] * 720 - firstAngle;
		if (angle > angleOffset)
			break;
	}
	float angle = s->wave.switchTimes[i] * 720 - firstAngle;

	registerActuatorEvent(list, i, actuator, angleOffset - angle);
}

void registerActuatorEvent(ActuatorEventList *list, int eventIndex, OutputSignal *actuator, float angleOffset) {
	if (list->size == MAX_EVENT_COUNT) {
		fatal("registerActuatorEvent");
		return;
	}
	ActuatorEvent *e = &list->events[list->size++];
	e->eventIndex = eventIndex;
	e->actuator = actuator;
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
