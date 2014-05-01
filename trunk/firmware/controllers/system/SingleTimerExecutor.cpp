/**
 * @file SingleTimerExecutor.cpp
 *
 * This class combines the powers of a 1MHz hardware timer from microsecond_timer.c
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
	efiAssert(nextEventTime > nowUs, "setTimer constraint");
	if (nextEventTime == EMPTY_QUEUE)
		return; // no pending events in the queue
	setHardwareUsTimer(nextEventTime - nowUs);
}

Executor::Executor() {
}

void Executor::schedule(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param) {
	queue.insertTask(scheduling, nowUs, delayUs, callback, param);
	execute(nowUs);
}

void Executor::execute(uint64_t nowUs) {
	/**
	 * Let's execute actions we should execute at this point
	 */
	queue.executeAll(nowUs);
	/**
	 * Let's set up the timer for the next execution
	 */
	setTimer(nowUs);
}

/**
 * @brief Schedule an event
 *
 * Invokes event callback after the specified amount of time.
 *
 * @param [in, out] scheduling Data structure to keep this event in the collection.
 * @param [in] delayUs the number of microseconds before the output signal immediate output if delay is zero.
 * @param [in] dwell the number of ticks of output duration.
 */
void scheduleTask(scheduling_s *scheduling, int delayUs, schfunc_t callback, void *param) {
	if (delayUs == 0) {
		callback(param);
		return;
	}
	instance.schedule(scheduling, getTimeNowUs(), delayUs, callback, param);
}

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
	signal->io_pin = ioPin;
	signal->name = getPinName(ioPin);
	initOutputSignalBase(signal);
}

void initSignalExecutorImpl(void) {
	globalTimerCallback = executorCallback;
#if EFI_PROD_CODE
	initMicrosecondTimer();
#endif /* EFI_PROD_CODE */
}

#endif

