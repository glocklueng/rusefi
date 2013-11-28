/**
 * @file    main_loop.h
 * @brief   Main logic header
 *
 *
 *  Created on: Feb 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

#include "main.h"
#include "event_registry.h"

#define MAX_INJECTOR_COUNT 12
#define MAX_IGNITER_COUNT 4

typedef struct {
	int injectAtEventIndex[SHAFT_POSITION_EVENT_COUNT];
	ActuatorEventList ignitionEvents;
} EventHandlerConfiguration;

void initMainEventListener(void);
void onEveryMillisecondTimerSignal(void);
/**
 * @brief	Implementation would be provided by engine configutation file
 */
void configureEngineEventHandler(EventHandlerConfiguration *config);

myfloat getFuel(int rpm, float key);

#endif /* MAIN_LOOP_H_ */
