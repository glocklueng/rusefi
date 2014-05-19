/**
 * @file	signal_executor.h
 * @brief   Asynchronous output signal header
 *
 * @date Feb 10, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef SPARKOUT_H_
#define SPARKOUT_H_

#include "rusefi_enums.h"
#include "global.h"
#include "efifeatures.h"
#include "io_pins.h"
#include "scheduler.h"

#if EFI_PROD_CODE
#include "datalogging.h"
#endif /* EFI_PROD_CODE */

#if EFI_SIGNAL_EXECUTOR_SLEEP
#include "signal_executor_sleep.h"
#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */

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
	int initialized;

	/**
	 * We are alternating instances so that events which extend into next revolution are not overriden while
	 * scheduling next revolution events
	 */
	scheduling_s signalTimerUp[2];
	scheduling_s signalTimerDown[2];

	executor_status_t status;

#if EFI_SIGNAL_EXECUTOR_HW_TIMER
	// todo
#endif

//	OutputSignal *next;
};

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin);
void scheduleOutput(OutputSignal *signal, float delayMs, float durationMs);
void initOutputSignalBase(OutputSignal *signal);
void scheduleOutputBase(OutputSignal *signal, float delayMs, float durationMs);

void turnPinHigh(OutputSignal *signal);
void turnPinLow(OutputSignal *signal);

void initSignalExecutor(void);
void initSignalExecutorImpl(void);
void scheduleByAngle(scheduling_s *timer, float angle, schfunc_t callback, void *param);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPARKOUT_H_ */
