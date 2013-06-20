/*
 * sparkout.c
 *
 *  Created on: Feb 10, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "status_leds.h"
#include "sparkout.h"
#include "rficonsole.h"
#include "datalogging.h"
#include "rpm_reporter.h"

static OutputSignal sparkOut1;
static OutputSignal sparkOut2;
static OutputSignal injectorOut1;
static OutputSignal injectorOut2;
static OutputSignal injectorOut3;
static OutputSignal injectorOut4;

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
 *
 * @param	delay	the number of ticks before the output signal
 * 					immediate output if delay is zero
 * @param	dwell	the number of ticks of output duration
 *
 */
static void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
	if (!signal->initialized)
		chDbgPanic("Signal not initialized");

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
	chVTSetI(&signal->signalTimer, delay, &signalOutputCallbackI, signal);
	chSysUnlockFromIsr()
	;

	time_t now = chTimeNow();

	if (isArmed) {
//		queueSimpleMsg(&signal->logging, "WAS ARMED ", offset);

//		commonSimpleMsg(&signal->logging, "WAS ARMED ", delay);
		logStartLine(&signal->logging);
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

		logPending(&signal->logging);
	}

	signal->last_scheduling_time = now;

}

void scheduleSparkOut(int offset, int duration) {
	scheduleOutput(&sparkOut1, offset, duration);
	scheduleOutput(&sparkOut2, offset, duration);
}

void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks) {
// it's batch injection and currently all injectors are wired to the same output pin
//	scheduleOutput(&injectorOut1, offsetSysTicks, lengthSysTicks);
//	scheduleOutput(&injectorOut2, offsetSysTicks, lengthSysTicks);
	scheduleOutput(&injectorOut3, offsetSysTicks, lengthSysTicks);
//	scheduleOutput(&injectorOut4, offsetSysTicks, lengthSysTicks);
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

		// turn the output level ACTIVE
		setStatusLed(signal->ledIndex, TRUE ^ signal->xor);
		// sleep for the needed duration
		chThdSleep(signal->duration);
		// turn off the output
		setStatusLed(signal->ledIndex, FALSE ^ signal->xor);
	}
	// unreachable
	return 0;
}

static void initOutputSignal(char *name, OutputSignal *signal, int led, int xor) {
	signal->ledIndex = led;
	signal->xor = xor;
	signal->name = name;
	signal->duration = 0;
	setStatusLed(led, xor); // initial state
	chSemInit(&signal->signalSemaphore, 1);

	chThdCreateStatic(signal->soThreadStack, sizeof(signal->soThreadStack),
			NORMALPRIO, soThread, signal);
	signal->initialized = TRUE;
}

void initOutputSignals() {
	initOutputSignal("Spark Out1", &sparkOut1, LED_SPARKOUT_1, 1);
	initOutputSignal("Spark Out2", &sparkOut2, LED_SPARKOUT_2, 1);
	initOutputSignal("Injector 1", &injectorOut1, LED_INJECTOR_1, 0);
	initOutputSignal("Injector 2", &injectorOut2, LED_INJECTOR_2, 0);
	initOutputSignal("Injector 3", &injectorOut3, LED_INJECTOR_3, 0);
	initOutputSignal("Injector 4", &injectorOut4, LED_INJECTOR_4, 0);
}

void pokeOutputSignals() {
//	print("%d\r\n", sparkOutDuration);
}
