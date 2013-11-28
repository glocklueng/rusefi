/*
 * test_event_registry.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "event_registry.h"
#include "test_event_registry.h"
#include "main.h"

static ActuatorEventList eventList;
static ActuatorEventList result;

void testEventRegistry(void) {
	resetEventList(&eventList);

	registerActuatorEvent(&eventList, 0, 10, 0);
	registerActuatorEvent(&eventList, 0, 20, 10);
	assertEquals(2, eventList.size);

	registerActuatorEvent(&eventList, 1, 30, 0);
	registerActuatorEvent(&eventList, 1, 40, 10);
	assertEquals(4, eventList.size);


	printf("Looking for 0\r\n");
	findEvents(0, &eventList, &result);
	assertEquals(2, result.size);
	assertEquals(4, eventList.size);

	assertEquals(10, result.events[0].actuatorId);
	assertEquals(20, result.events[1].actuatorId);

	printf("Looking for 1\r\n");
	findEvents(1, &eventList, &result);
	assertEquals(2, result.size);
	assertEquals(4, eventList.size);

	assertEquals(30, result.events[0].actuatorId);
	assertEquals(40, result.events[1].actuatorId);

}
