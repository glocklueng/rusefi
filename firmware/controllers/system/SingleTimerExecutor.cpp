/**
 * @file SingleTimerExecutor.cpp
 *
 * This class combines the 1MHz hardware timer and microsecond_timer.c
 * and pending events queue event_queue.cpp
 *
 * todo: add thread safety
 *
 * @date: Apr 18, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "SingleTimerExecutor.h"
#include "efitime.h"
#if EFI_PROD_CODE
#include "microsecond_timer.h"
#endif

#if EFI_SIGNAL_EXECUTOR_ONE_TIMER || defined(__DOXYGEN__)

static Executor instance;

extern schfunc_t globalTimerCallback;

static void executorCallback(void *arg) {
	instance.execute(getTimeNowUs());
}

void Executor::setTimer(uint64_t nowUs) {
	uint64_t nextEventTime = queue.getNextEventTime(nowUs);
	setHardwareUsTimer(nextEventTime - nowUs);
}

Executor::Executor() {
}

void Executor::schedule(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param) {
	queue.schedule(scheduling, nowUs, delayUs, callback, param);
	setTimer(nowUs);
}

void Executor::execute(uint64_t now) {
	/**
	 * Let's execute actions we should execute at this point
	 */
	queue.execute(now);
	/**
	 * Let's set up the timer for the next execution
	 */
	setTimer(now);
}

void scheduleTask(scheduling_s *scheduling, float delayMs, schfunc_t callback, void *param) {
	if (delayMs == 0) {
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
#if EFI_PROD_CODE
	initMicrosecondTimer();
#endif
}

#endif

