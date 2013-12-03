/**
 * @file	signal_executor_sleep.c
 * @brief   Asynchronous output signal code
 *
 * Here we have the simplest, thread-based implementation of signal executor.
 * TODO: https://sourceforge.net/p/rusefi/tickets/6/
 *
 * @date Feb 10, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "output_pins.h"
#include "signal_executor.h"
#include "rficonsole.h"
#include "datalogging.h"
#include "rpm_calculator.h"
#include "injector_central.h"

#if EFI_WAVE_ANALYZER
#include "wave_chart.h"
/**
 * Signal executors feed digital events right into WaveChart used by Sniffer tab of Dev Console
 */
extern WaveChart waveChart;
#endif /* EFI_WAVE_ANALYZER */

#if EFI_SIGNAL_EXECUTOR_SLEEP

static void signalOutputCallbackI(OutputSignal *signal) {
	chSysLockFromIsr()
	;
	/**
	 * this would awaken the actual output thread
	 */
	chSemSignalI(&signal->hw.signalSemaphore);
	chSysUnlockFromIsr()
	;
}

/**
 *
 * @param	delay	the number of ticks before the output signal
 * 					immediate output if delay is zero
 * @param	dwell	the number of ticks of output duration
 *
 */
void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
	chDbgCheck(signal->initialized, "Signal not initialized");
	chDbgCheck(dwell >= 0, "dwell cannot be negative");

	signal->duration = dwell;
	if (delay == 0) {
		/**
		 * in case of zero delay, we should notify the output thread right away
		 */
		signalOutputCallbackI(signal);
		return;
	}

//	logStartLine(&signal->logging, 0);
//	msgInt(&signal->logging, "msg,spark offset ", offset);
//	msgInt(&signal->logging, "duration ", duration);
//	msgInt(&signal->logging, "now ", GetCurrentTime());
//	msgInt(&signal->logging, "conter ", scheCounter++);
//	logPending(&signal->logging);

// schedule signal output callback after the 'delay'
	chSysLockFromIsr()
	;
	int isArmed = chVTIsArmedI(&signal->hw.signalTimer);
	if (isArmed)
		chVTResetI(&signal->hw.signalTimer);

	/**
	 * this timer implements the delay before the signal output
	 */
	chVTSetI(&signal->hw.signalTimer, delay, (vtfunc_t) &signalOutputCallbackI, (void *) signal);
	chSysUnlockFromIsr()
	;

	time_t now = chTimeNow();

	if (isArmed) {
//		queueSimpleMsg(&signal->logging, "WAS ARMED ", offset);

//		commonSimpleMsg(&signal->logging, "WAS ARMED ", delay);
		resetLogging(&signal->logging);
		append(&signal->logging, "msg");
		append(&signal->logging, DELIMETER);
		appendPrintf(&signal->logging, "%d", now - signal->last_scheduling_time);
		append(&signal->logging, " ticks ago ");
		append(&signal->logging, signal->name);

		append(&signal->logging, " rpm=");
		appendPrintf(&signal->logging, "%d", getCurrentRpm());
		append(&signal->logging, " delay= ");
		appendPrintf(&signal->logging, "%d", delay);

		append(&signal->logging, " dwell=");
		appendPrintf(&signal->logging, "%d", dwell);
		msgInt(&signal->logging, " WAS ARMED ", delay);

		scheduleLogging(&signal->logging);
	}

	signal->last_scheduling_time = now;

}

static msg_t soThread(OutputSignal *signal) {
	chRegSetThreadName(signal->name);
	/**
	 * we have one thread per output signal
	 * When an output signal is needed, this thread is awakened
	 */

	while (1) {
		// sleep till signal is needed
		chSemWait(&signal->hw.signalSemaphore);
		if (signal->duration == 0) {
			// todo: when exactly does this happen?
			chThdSleep(1);
			continue;
		}

#if EFI_DEFAILED_LOGGING
		systime_t now = chTimeNow();
#endif /* EFI_DEFAILED_LOGGING */
		// turn the output level ACTIVE
		// todo: this XOR should go inside the setOutputPinValue method
		setOutputPinValue(signal->ledIndex, TRUE ^ signal->xor);
		// sleep for the needed duration

#if EFI_WAVE_ANALYZER
		addWaveChartEvent(&waveChart, signal->name, "up");
#endif /* EFI_WAVE_ANALYZER */

		chThdSleep(signal->duration);
		// turn off the output
		// todo: this XOR should go inside the setOutputPinValue method
		setOutputPinValue(signal->ledIndex, FALSE ^ signal->xor);

#if EFI_DEFAILED_LOGGING
		systime_t after = chTimeNow();
		debugInt(&signal->logging, "a_time", after - now);
		scheduleLogging(&signal->logging);
#endif /* EFI_DEFAILED_LOGGING */

#if EFI_WAVE_ANALYZER
		addWaveChartEvent(&waveChart, signal->name, "down");
#endif /* EFI_WAVE_ANALYZER */
	}
	// unreachable
	return 0;
}

void initOutputSignal(char *name, OutputSignal *signal, int led, int xor) {
	initLogging(&signal->logging, name);

	signal->ledIndex = led;
	signal->xor = xor;
	signal->name = name;
	signal->duration = 0;
	setOutputPinValue(led, xor); // initial state
	chSemInit(&signal->hw.signalSemaphore, 1);

	chThdCreateStatic(signal->hw.soThreadStack, sizeof(signal->hw.soThreadStack), NORMALPRIO, (tfunc_t) soThread, signal);
	signal->initialized = TRUE;
}

#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */
