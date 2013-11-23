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

#define MAX_INJECTOR_COUNT 12
#define MAX_IGNITER_COUNT 4

typedef struct {
	int injectAtEventIndex[SHAFT_POSITION_EVENT_COUNT];
	int igniteAtEventIndex[SHAFT_POSITION_EVENT_COUNT];
} EventHandlerConfiguration;

void initMainEventListener(void);
void onEveryMillisecondTimerSignal(void);

myfloat getFuel(int rpm, float key);

#endif /* MAIN_LOOP_H_ */
