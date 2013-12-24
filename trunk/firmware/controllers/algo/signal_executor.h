/**
 * @file	signal_executor.h
 * @brief   Asynchronous output signal header
 *
 * @date Feb 10, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef SPARKOUT_H_
#define SPARKOUT_H_

#include "main.h"

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
	/**
	 * output signals use status led hardware layer
	 * index of the output led which is used as output pin
	 */
	int ledIndex;
	/**
	 * active on high or active on low
	 */
	int xor;
	// time in system ticks
	volatile int offset;
	// time in system ticks
	volatile int duration;
#if EFI_PROD_CODE
	Logging logging;
#endif /* EFI_PROD_CODE */
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

void initOutputSignal(char *name, OutputSignal *signal, int led, int xor);
void scheduleOutput(OutputSignal *signal, int delay, int dwell);
void initOutputSignalBase(OutputSignal *signal);
void scheduleOutputBase(OutputSignal *signal, int offset, int duration);

#endif /* SPARKOUT_H_ */
