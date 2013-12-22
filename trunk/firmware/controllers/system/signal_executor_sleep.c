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
#include "engine_math.h"

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

static void commonSchedule(VirtualTimer *timer, int delay, vtfunc_t callback, void *param) {
	if (delay == 0) {
		/**
		 * in case of zero delay, we should invoke the callback
		 */
		callback(param);
		return;
	}

	lockAnyContext();
	int isArmed = chVTIsArmedI(timer);
	if (isArmed)
		chVTResetI(timer);

	chVTSetI(timer, delay, callback, param);
	unlockAnyContext();
}

void scheduleByAngle(VirtualTimer *timer, float angle, vtfunc_t callback, void *param) {
	int delay = getOneDegreeTime(getCurrentRpm()) * angle;
	commonSchedule(timer, delay, callback, param);
}

/**
 *
 * @param	delay	the number of ticks before the output signal
 * 					immediate output if delay is zero
 * @param	dwell	the number of ticks of output duration
 *
 */
void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
	chDbgCheck(dwell >= 0, "dwell cannot be negative");

	scheduleOutputBase(signal, delay, dwell);

	commonSchedule(&signal->hw.signalTimer, delay, (vtfunc_t) &signalOutputCallbackI, (void *) signal);

	time_t now = chTimeNow();

	signal->last_scheduling_time = now;

}

static void turnHi(OutputSignal *signal) {
#if EFI_DEFAILED_LOGGING
	signal->hi_time = chTimeNow();
#endif /* EFI_DEFAILED_LOGGING */
	// turn the output level ACTIVE
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(signal->ledIndex, TRUE ^ signal->xor);
	// sleep for the needed duration

#if EFI_WAVE_ANALYZER
	addWaveChartEvent(&waveChart, signal->name, "up");
#endif /* EFI_WAVE_ANALYZER */
}

static void turnLow(OutputSignal *signal) {
	// turn off the output
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(signal->ledIndex, FALSE ^ signal->xor);

#if EFI_DEFAILED_LOGGING
	systime_t after = chTimeNow();
	debugInt(&signal->logging, "a_time", after - signal->hi_time);
	scheduleLogging(&signal->logging);
#endif /* EFI_DEFAILED_LOGGING */

#if EFI_WAVE_ANALYZER
	addWaveChartEvent(&waveChart, signal->name, "down");
#endif /* EFI_WAVE_ANALYZER */
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

		turnHi(signal);

		commonSchedule(&signal->hw.signalTimerDown, signal->duration, (vtfunc_t) &turnLow, (void*)signal);
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

	chThdCreateStatic(signal->hw.soThreadStack, sizeof(signal->hw.soThreadStack), NORMALPRIO, (tfunc_t) soThread,
			signal);
	initOutputSignalBase(signal);
}

#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */
