/**
 * @file	signal_executor.c
 *
 * @date Dec 4, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "signal_executor.h"

#define OUTPUT_SIGNAL_COUNT 40

static OutputSignal signals[OUTPUT_SIGNAL_COUNT];

int outputSignalCount;

OutputSignal * addOutputSignal(io_pin_e ioPin) {
	chDbgAssert(outputSignalCount < OUTPUT_SIGNAL_COUNT, "OUTPUT_SIGNAL_COUNT", NULL);
	OutputSignal *signal = &signals[outputSignalCount++];

	initOutputSignal(signal, ioPin);

	return signal;
}



void initOutputSignalBase(OutputSignal *signal) {
	signal->status = IDLE;
	signal->last_scheduling_time = 0;
	signal->initialized = TRUE;
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
