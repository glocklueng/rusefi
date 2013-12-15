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

/**
 * @brief Here we store information about which injectior or spark should be fired when.
 */
typedef struct {
	ActuatorEventList crankingInjectionEvents;
	ActuatorEventList injectionEvents;
	ActuatorEventList ignitionEvents;
} EventHandlerConfiguration;

void initMainEventListener(void);
void onEveryMillisecondTimerSignal(void);
int isIgnitionTimingError(void);
/**
 * @brief	Implementation would be provided by engine configuration file
 */
void configureEngineEventHandler(EventHandlerConfiguration *config);

myfloat getFuel(int rpm, float key);

#endif /* MAIN_LOOP_H_ */
