/*
 *  Created on: Feb 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    main_loop.h
 * @brief   Main logic header
 */

#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

#include "main.h"

#define MAX_INJECTOR_COUNT 12

typedef struct {
	int fireAtEventIndex[SHAFT_POSITION_EVENT_COUNT];
} InjectionConfiguration;

void initMainEventListener(void);
void onEveryMillisecondTimerSignal(void);

myfloat getVRef(void);
myfloat getVBatt(void);
myfloat getFuel(int rpm, float key);

#endif /* MAIN_LOOP_H_ */
