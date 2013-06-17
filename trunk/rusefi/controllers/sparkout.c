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

static OutputSignal sparkOut;
static OutputSignal injectorOut1;
static OutputSignal injectorOut2;
static OutputSignal injectorOut3;
static OutputSignal injectorOut4;

//// this signal is invoked on the interrupt thread
//// we cannot sleep on this thread - so, let's notify the thread which can sleep
//// technically, we can use another timer to turn the spark off...
//static void sparkOutCallback(OutputSignal *signal) {
//	chSemSignalI(&signal->signalSemaphore);
//}

static void sparkOutCallbackI(OutputSignal *signal) {
	chSysLockFromIsr()
	;
	chSemSignalI(&signal->signalSemaphore);
	chSysUnlockFromIsr();
}

static void scheduleSignal(OutputSignal *signal, int offset, int duration) {
	if (!signal->initialized)
		chDbgPanic("Not initialized");

	signal->duration = duration;
	if (offset == 0) {
		sparkOutCallbackI(signal);
		return;
	}

//	logStartLine(&signal->logging, 0);
//	msgInt(&signal->logging, "msg,spark offset ", offset);
//	msgInt(&signal->logging, "duration ", duration);
//	msgInt(&signal->logging, "now ", GetCurrentTime());
//	msgInt(&signal->logging, "conter ", scheCounter++);
//	logPending(&signal->logging);

// schedule spark out callback after the 'offset'
	chSysLockFromIsr()
	;
	int isArmed = chVTIsArmedI(&signal->signalTimer);
	if (isArmed)
		chVTResetI(&signal->signalTimer);

	chVTSetI(&signal->signalTimer, offset, &sparkOutCallbackI, signal);
	chSysUnlockFromIsr();

	if (isArmed)
		queueSimpleMsg(&signal->logging, "WAS ARMED ", offset);
}

void scheduleSparkOut(int offset, int duration) {
//	scheduleSignal(&sparkOut, offset, duration);
}

void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks) {
	scheduleSignal(&injectorOut1, offsetSysTicks, lengthSysTicks);
	scheduleSignal(&injectorOut2, offsetSysTicks, lengthSysTicks);
	scheduleSignal(&injectorOut3, offsetSysTicks, lengthSysTicks);
	scheduleSignal(&injectorOut4, offsetSysTicks, lengthSysTicks);
}

static msg_t soThread(OutputSignal *signal) {
	chRegSetThreadName("SparkOut");

	while (1) {
		chSemWait(&signal->signalSemaphore);
		if (signal->duration == 0) {
			// todo: when exactly does this happen?
			chThdSleep(1);
			continue;
		}

		setStatusLed(signal->led, TRUE ^ signal->xor);
		chThdSleep(signal->duration);
		setStatusLed(signal->led, FALSE ^ signal->xor);

	}
	return 0;
}

static void initOutputSignal(OutputSignal *signal, int led, int xor) {
	signal->led = led;
	signal->xor = xor;
	signal->duration = 0;
	setStatusLed(led, xor); // initial state
	chSemInit(&signal->signalSemaphore, 1);

	chThdCreateStatic(signal->soThreadStack, sizeof(signal->soThreadStack),
			NORMALPRIO, soThread, signal);
	signal->initialized = TRUE;
}

void initOutputSignals() {
	initOutputSignal(&sparkOut, LED_SPARKOUT, 1);
	initOutputSignal(&injectorOut1, LED_INJECTOR_1, 0);
	initOutputSignal(&injectorOut2, LED_INJECTOR_2, 0);
	initOutputSignal(&injectorOut3, LED_INJECTOR_3, 0);
	initOutputSignal(&injectorOut4, LED_INJECTOR_4, 0);
}

void pokeSparkOut() {
//	print("%d\r\n", sparkOutDuration);
}
