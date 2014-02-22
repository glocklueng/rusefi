/*
 * @file    signal_executor_hw_timer.c
 *
 * this is a future home of hardware TIM signal executor https://sourceforge.net/p/rusefi/tickets/6/
 *
 * @date Oct 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "signal_executor.h"
#include "signal_executor_hw_timer.h"

#if EFI_SIGNAL_EXECUTOR_HW_TIMER || defined(__DOXYGEN__)

void initOutputSignal(char *name, OutputSignal *signal, int led, int xor) {
	// todo
}

void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
	// todo
}

#endif /* EFI_SIGNAL_EXECUTOR_HW_TIMER */
