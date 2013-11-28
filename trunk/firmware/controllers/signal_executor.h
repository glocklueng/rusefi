/**
 * @file	signal_executor.h
 * @brief   Asynchronous output signal header
 *
 *  Created on: Feb 10, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef SPARKOUT_H_
#define SPARKOUT_H_

#include "main.h"
#include "signal_executor_sleep.h"

/**
 * @brief   Asynchronous output signal data structure
 */
typedef struct {
	/**
	 * name of this signal
	 */
	char *name;
	/**
	 * output signals use status led hardware layer
	 * index of the output led which is used as output pin
	 */
	int ledIndex;
	/**
	 * active on high or active on low
	 */
	int xor;
	// time in system ticks
	volatile int offset;
	// time in system ticks
	volatile int duration;
	Logging logging;
	int initialized;

	time_t last_scheduling_time;

#if EFI_SIGNAL_EXECUTOR_SLEEP
	SignalExecutorSleep hw;
#endif

#if EFI_SIGNAL_EXECUTOR_HW_TIMER
	// todo
#endif
} OutputSignal;

void initOutputSignal(char *name, OutputSignal *signal, int led, int xor);
void scheduleOutput(OutputSignal *signal, int delay, int dwell);

#endif /* SPARKOUT_H_ */
