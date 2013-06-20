/*
 * sparkout.h
 *
 *  Created on: Feb 10, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef SPARKOUT_H_
#define SPARKOUT_H_

#include "datalogging.h"

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
	/**
	 * this timer is used to wait for the time to activate the thread
	 */
	VirtualTimer signalTimer;
	/**
	 * this timer is used to notify the worker thread when it's time to output
	 * the signal
	 */
	Semaphore signalSemaphore;
	WORKING_AREA(soThreadStack, 512);
	Logging logging;
	int initialized;

	time_t last_scheduling_time;

} OutputSignal;

void scheduleSparkOut(int offset, int duration);
void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks);

void initOutputSignals(void);
void pokeOutputSignals(void);

#endif /* SPARKOUT_H_ */
