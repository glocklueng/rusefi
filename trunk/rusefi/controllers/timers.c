/*
 * timers.c
 *
 *  Created on: Feb 10, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "timers.h"
#include "main_loop.h"

static VirtualTimer everyMsTimer;

static void onMillisecondInternal() {
	onEveryMillisecondTimerSignal();

	// schedule next invocation
	chSysLockFromIsr();
	chVTSetI(&everyMsTimer, TICKS_IN_MS, &onMillisecondInternal, 0);
	chSysUnlockFromIsr();
}

void initTimers() {
	// schedule first invocation
	chVTSet(&everyMsTimer, TICKS_IN_MS, &onMillisecondInternal, 0);
}
