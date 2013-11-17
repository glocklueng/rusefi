/*
 * injector_control.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "settings.h"

#include "rficonsole.h"
#include "datalogging.h"
#include "main.h"

static volatile int injectionPeriod = 0;
static volatile int crankingInjectionPeriod = 0;
static volatile int injectionOffset = 0;

static Logging logger;

static void printSettings(void) {
	msgInt(&logger, "msg,injectionPeriod ", injectionPeriod);
	msgInt(&logger, "msg,cranking injectionPeriod ", crankingInjectionPeriod);
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

void setInjectionPeriod(int value) {
	injectionPeriod = value;
	printSettings();
}

int getCrankingInjectionPeriod(void) {
	return crankingInjectionPeriod;
}

void setCrankingInjectionPeriod(int value) {
	crankingInjectionPeriod = value;
	printSettings();
}

void initSettings(void) {
	initLogging(&logger, "inje control", logger.DEFAULT_BUFFER, sizeof(logger.DEFAULT_BUFFER));

	setInjectionOffset(0);
	setInjectionPeriod(30);
	//setCrankingInjectionPeriod(TICKS_IN_MS * 1.5);

	addConsoleAction1("p", &setInjectionPeriod);
	addConsoleAction1("cp", &setCrankingInjectionPeriod);
	addConsoleAction1("o", &setInjectionOffset);
}

