/**
 * @file	signal_executor.h
 * @brief   Asynchronous output signal header
 *
 * @date Feb 10, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef SPARKOUT_H_
#define SPARKOUT_H_

#include "global.h"
#include "features.h"
#include "io_pins.h"

#if EFI_PROD_CODE
#include "datalogging.h"
#endif /* EFI_PROD_CODE */

#if EFI_SIGNAL_EXECUTOR_SLEEP
#include "signal_executor_sleep.h"
#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */

#if EFI_SIGNAL_EXECUTOR_SINGLE_TIMER
#include "signal_executor_single_timer.h"
#endif /* EFI_SIGNAL_EXECUTOR_SINGLE_TIMER */

typedef enum {
	IDLE = 0, ACTIVE
} executor_status_t;

/**
 * @brief   Asynchronous output signal data structure
 */
typedef struct OutputSignal_struct OutputSignal;
struct OutputSignal_struct {
	/**
	 * name of this signal
	 */
	char *name;
	io_pin_e io_pin;
	// time in system ticks
	volatile int offset;
	// time in system ticks
	volatile int duration;

	int initialized;

	time_t last_scheduling_time;
	time_t hi_time;

#if EFI_SIGNAL_EXECUTOR_SLEEP
	SignalExecutorSleep hw;
#endif

	executor_status_t status;

#if EFI_SIGNAL_EXECUTOR_HW_TIMER
	// todo
#endif

	OutputSignal *next;
};

OutputSignal * addOutputSignal(io_pin_e ioPin);
void initOutputSignal(OutputSignal *signal, io_pin_e ioPin);
void scheduleOutput(OutputSignal *signal, int delay, int dwell);
void initOutputSignalBase(OutputSignal *signal);
void scheduleOutputBase(OutputSignal *signal, int offset, int duration);

#endif /* SPARKOUT_H_ */
