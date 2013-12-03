/*
 * injector_control.c
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "settings.h"

#include "rficonsole.h"
#include "datalogging.h"
#include "main.h"

static volatile int crankingInjectionPeriod = 0;
static volatile int injectionOffset = 0;

static Logging logger;

static void printSettings(void) {
	msgInt(&logger, "msg,injectionOffset ", injectionOffset);

	printLine(&logger);
}

int getInjectionOffset(void) {
	return injectionOffset;
}

void setInjectionOffset(int value) {
	injectionOffset = value;
	printSettings();
}

void initSettings(void) {
	// todo: this whole method is legacy stuff
	// todo: the whole file is prettu much legacy pre-TunerStudio stuff
	initLoggingExt(&logger, "inje control", logger.DEFAULT_BUFFER, sizeof(logger.DEFAULT_BUFFER));

	setInjectionOffset(0);
	//setCrankingInjectionPeriod(TICKS_IN_MS * 1.5);

	addConsoleActionI("o", &setInjectionOffset);
}

