/*
 * signal_executor.c
 *
 *  Created on: Feb 10, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 *
 */

/**
 * @file	signal_executor.c
 * @brief   Asynchronous output signal code
 */

#include "main.h"
#include "output_pins.h"
#include "signal_executor.h"
#include "rficonsole.h"
#include "datalogging.h"
#include "rpm_reporter.h"
#include "injector_central.h"

#if EFI_WAVE_ANALYZER
#include "wave_chart.h"
extern WaveChart crankChart;
#endif

static OutputSignal sparkOut1;
static OutputSignal sparkOut2;
static OutputSignal injectorOut1;
static OutputSignal injectorOut2;
static OutputSignal injectorOut3;
static OutputSignal injectorOut4;

static OutputSignal* injectors[4] = { &injectorOut1, &injectorOut2, &injectorOut3, &injectorOut4 };

static void signalOutputCallbackI(OutputSignal *signal) {
	chSysLockFromIsr()
	;
	/**
	 * this would awaken the actual output thread
	 */
	chSemSignalI(&signal->signalSemaphore);
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
static void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
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
	int isArmed = chVTIsArmedI(&signal->signalTimer);
	if (isArmed)
		chVTResetI(&signal->signalTimer);

	/**
	 * this timer implements the delay before the signal output
	 */
	chVTSetI(&signal->signalTimer, delay, (vtfunc_t) &signalOutputCallbackI, (void *) signal);
	chSysUnlockFromIsr()
	;

	time_t now = chTimeNow();

	if (isArmed) {
//		queueSimpleMsg(&signal->logging, "WAS ARMED ", offset);

//		commonSimpleMsg(&signal->logging, "WAS ARMED ", delay);
		resetLogging(&signal->logging);
		append(&signal->logging, "msg");
		append(&signal->logging, DELIMETER);
		appendInt(&signal->logging, now - signal->last_scheduling_time);
		append(&signal->logging, " ticks ago ");
		append(&signal->logging, signal->name);

		append(&signal->logging, " rpm=");
		appendInt(&signal->logging, getCurrentRpm());
		append(&signal->logging, " delay= ");
		appendInt(&signal->logging, delay);

		append(&signal->logging, " dwell=");
		appendInt(&signal->logging, dwell);
		msgInt(&signal->logging, " WAS ARMED ", delay);

		scheduleLogging(&signal->logging);
	}

	signal->last_scheduling_time = now;

}

void scheduleSparkOut(int offset, int duration) {
//	scheduleOutput(&sparkOut1, offset, duration);
//	scheduleOutput(&sparkOut2, offset, duration);
}

/**
 * This method schedules asynchronous fuel squirt
 */
void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks, int cylinderId) {
	assertCylinderId(cylinderId, "scheduleFuelInjection");

	if (!isInjectorEnabled(cylinderId))
		return;

	OutputSignal *injector = injectors[cylinderId - 1];

	scheduleOutput(injector, offsetSysTicks, lengthSysTicks);
}

static msg_t soThread(OutputSignal *signal) {
	chRegSetThreadName(signal->name);
	/**
	 * we have one thread per output signal
	 * When an output signal is needed, this thread is awakened
	 */

	while (1) {
		// sleep till signal is needed
		chSemWait(&signal->signalSemaphore);
		if (signal->duration == 0) {
			// todo: when exactly does this happen?
			chThdSleep(1);
			continue;
		}

		int now = chTimeNow();
		// turn the output level ACTIVE
		setOutputPinValue(signal->ledIndex, TRUE ^ signal->xor);
		// sleep for the needed duration

#if EFI_WAVE_ANALYZER
		addWaveChartEvent(&crankChart, signal->name, "up");
#endif

		chThdSleep(signal->duration);
		// turn off the output
		setOutputPinValue(signal->ledIndex, FALSE ^ signal->xor);
		int after = chTimeNow();

#if EFI_DEFAILED_LOGGING
		debugInt(&signal->logging, "a_time", after - now);
		scheduleLogging(&signal->logging);
#endif

#if EFI_WAVE_ANALYZER
		addWaveChartEvent(&crankChart, signal->name, "down");
#endif
	}
	// unreachable
	return 0;
}

static void initOutputSignal(char *name, OutputSignal *signal, int led, int xor) {
	initLogging(&signal->logging, name, signal->logging.DEFAULT_BUFFER, sizeof(signal->logging.DEFAULT_BUFFER));

	signal->ledIndex = led;
	signal->xor = xor;
	signal->name = name;
	signal->duration = 0;
	setOutputPinValue(led, xor); // initial state
	chSemInit(&signal->signalSemaphore, 1);

	chThdCreateStatic(signal->soThreadStack, sizeof(signal->soThreadStack), NORMALPRIO, (tfunc_t) soThread, signal);
	signal->initialized = TRUE;
}

void initOutputSignals() {
	initOutputSignal("Spark Out1", &sparkOut1, SPARKOUT_1_OUTPUT, 1);
	initOutputSignal("Spark Out2", &sparkOut2, SPARKOUT_2_OUTPUT, 1);
	initOutputSignal("Injector 1", &injectorOut1, INJECTOR_1_OUTPUT, 0);
	initOutputSignal("Injector 2", &injectorOut2, INJECTOR_2_OUTPUT, 0);
	initOutputSignal("Injector 3", &injectorOut3, INJECTOR_3_OUTPUT, 0);
	initOutputSignal("Injector 4", &injectorOut4, INJECTOR_4_OUTPUT, 0);
}
