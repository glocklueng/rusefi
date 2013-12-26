/**
 * @file    main_loop.h
 * @brief   Main logic header
 *
 *
 * @date Feb 9, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

#include "main.h"
#include "event_registry.h"

#define MAX_INJECTOR_COUNT 12
#define MAX_IGNITER_COUNT 4

void initMainEventListener(void);
void showMainHistogram(void);
void onEveryMillisecondTimerSignal(void);
int isIgnitionTimingError(void);

myfloat getFuel(int rpm, float key);

#endif /* MAIN_LOOP_H_ */
