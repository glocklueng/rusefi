/**
 * @file	signal_executor.c
 *
 * @date Dec 4, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "signal_executor.h"

void initOutputSignalBase(OutputSignal *signal) {
	signal->initialized = TRUE;
	signal->last_scheduling_time = 0;
}

void scheduleOutputBase(OutputSignal *signal, int offset, int duration) {
	/**
	 * it's better to check for the exact 'TRUE' value since otherwise
	 * we would accept any memory garbage
	 */
	chDbgCheck(signal->initialized == TRUE, "Signal not initialized");
	signal->offset = offset;
	signal->duration = duration;
}
