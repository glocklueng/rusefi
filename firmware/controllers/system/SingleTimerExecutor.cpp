/*
 * SingleTimerExecutor.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Andrey
 */

#include "SingleTimerExecutor.h"
#include "efitime.h"
#include "microsecond_timer.h"

#if EFI_SIGNAL_EXECUTOR_ONE_TIMER || defined(__DOXYGEN__)

static Executor instance;

extern schfunc_t globalTimerCallback;

void Executor::setTimer(uint64_t nowUs) {
	uint64_t nextEventTime = eq.getNextEventTime(nowUs);
	setHardwareUsTimer(nextEventTime - nowUs);
}

static void executorCallback(void *arg) {
	uint64_t now = getTimeNowUs();
	instance.eq.execute(now);
	instance.setTimer(now);
}

Executor::Executor() {
}

void Executor::schedule(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param) {
	eq.schedule(scheduling, nowUs, delayUs, callback, param);
	setTimer(nowUs);
}

void scheduleTask(scheduling_s *scheduling, float delayMs, schfunc_t callback, void *param) {
	if(delayMs==0) {
		callback(param);
		return;
	}
	// todo: eliminate this /100. Times still come as systick times here
	instance.schedule(scheduling, getTimeNowUs(), delayMs * 1000000 / 100000, callback, param);
}

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
	signal->io_pin = ioPin;
	signal->name = getPinName(ioPin);
//	signal->duration = 0;
	initOutputSignalBase(signal);
}

void initSignalExecutorImpl(void) {
	globalTimerCallback = executorCallback;
	TIM_Init();
}

#endif

