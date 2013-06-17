/*
 * injector_control.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "injector_control.h"

#include "rficonsole.h"
#include "datalogging.h"

volatile int injectionPeriod = 0;
volatile int crankingInjectionPeriod = 0;
volatile int injectionOffset = 0;
volatile int injectorDivider = 0;

static Logging msg;

static void printSettings() {
	logStartLine(&msg);

	msgInt(&msg, "msg,injectionPeriod ", injectionPeriod);
	msgInt(&msg, "msg,cranking injectionPeriod ", crankingInjectionPeriod);
	msgInt(&msg, "msg,injectionOffset ", injectionOffset);
	msgInt(&msg, "msg,injDivider ", injectorDivider);

	printLine(&msg);
}

int getInjectionOffset() {
	return injectionOffset;
}

void setInjectionOffset(int value) {
	injectionOffset = value;
	printSettings();
}

int getInjectionPeriod() {
	return injectionPeriod;
}

void setInjectionPeriod(int value) {
	injectionPeriod = value;
	printSettings();
}

int getCrankingInjectionPeriod() {
	return crankingInjectionPeriod;
}

void setCrankingInjectionPeriod(int value) {
	crankingInjectionPeriod = value;
	printSettings();
}
int getInjectionDivider() {
	return injectorDivider;
}

void setInjectionDivider(int value) {
	injectorDivider = value;
	printSettings();
}

void pokeControl() {
//	print("state %d counter %d\r\n", inState, crankingCount);
}

void initInjectorsControl() {

	setInjectionOffset(-12);
	setInjectionPeriod(30);
	setCrankingInjectionPeriod(150);
	setInjectionDivider(4);

	addConsoleAction1("p", &setInjectionPeriod);
	addConsoleAction1("cp", &setCrankingInjectionPeriod);
	addConsoleAction1("o", &setInjectionOffset);
	addConsoleAction1("d", &setInjectionDivider);
}

