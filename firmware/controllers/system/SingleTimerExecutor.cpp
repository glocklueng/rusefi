/*
 * SingleTimerExecutor.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Andrey
 */

#include "SingleTimerExecutor.h"
#include "efitime.h"
#include "signal_temp.h"

#if EFI_SIGNAL_EXECUTOR_ONE_TIMER || defined(__DOXYGEN__)

static Executor instance;

extern schfunc_t globalTimerCallback;

static void executorCallback(void *arg) {
	instance.eq.execute(getTimeNowUs());
}

Executor::Executor() {
	globalTimerCallback = executorCallback;
}

void Executor::schedule(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param) {
	eq.schedule(scheduling, nowUs, delayUs, callback, param);
	uint64_t nextEventTime = eq.getNextEventTime();
	setTimer

}

void scheduleTask(scheduling_s *scheduling, float delayMs, schfunc_t callback, void *param) {
	instance.schedule(scheduling, getTimeNowUs(), delayMs * 1000000, callback, param);
}

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
	signal->io_pin = ioPin;
	signal->name = getPinName(ioPin);
//	signal->duration = 0;
	initOutputSignalBase(signal);
}


#endif

