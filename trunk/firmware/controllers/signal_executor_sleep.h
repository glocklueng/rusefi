/*
 * @file    signal_executir_sleep.h

 * @date Oct 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef SIGNAL_EXECUTOR_SLEEP_H_
#define SIGNAL_EXECUTOR_SLEEP_H_

#include "main.h"

#if EFI_SIGNAL_EXECUTOR_SLEEP

typedef struct {
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
} SignalExecutorSleep;

#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */


#endif /* SIGNAL_EXECUTOR_SLEEP_H_ */
