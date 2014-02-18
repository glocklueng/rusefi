/**
 * @file	signal_executor_sleep.c
 * @brief   Asynchronous output signal code
 *
 * Here we have the simplest, thread-based implementation of signal executor.
 * TODO: https://sourceforge.net/p/rusefi/tickets/6/
 *
 * @date Feb 10, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "rficonsole.h"
#include "datalogging.h"
#include "rpm_calculator.h"
#include "injector_central.h"
#include "engine_math.h"

#if EFI_SIGNAL_EXECUTOR_SLEEP || defined(__DOXYGEN__)

void scheduleTask(scheduling_s *scheduling, int delay, schfunc_t callback, void *param) {
	if (delay == 0) {
		/**
		 * in case of zero delay, we should invoke the callback
		 */
		callback(param);
		return;
	}

	lockAnyContext();
	int isArmed = chVTIsArmedI(&scheduling->timer);
	if (isArmed)
		chVTResetI(&scheduling->timer);

	chVTSetI(&scheduling->timer, delay, (vtfunc_t)callback, param);
	unlockAnyContext();
}

void scheduleByAngle(scheduling_s *timer, float angle, schfunc_t callback, void *param) {
	int delay = (int)(getOneDegreeTime(getRpm()) * angle);
	scheduleTask(timer, delay, callback, param);
}

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
	signal->io_pin = ioPin;
	signal->name = getPinName(ioPin);
	signal->duration = 0;
	initOutputSignalBase(signal);
}

#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */
