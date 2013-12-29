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

	VirtualTimer signalTimerDown;
} SignalExecutorSleep;

void scheduleByAngle(VirtualTimer *timer, float angle, vtfunc_t callback, void *param);

#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */


#endif /* SIGNAL_EXECUTOR_SLEEP_H_ */
