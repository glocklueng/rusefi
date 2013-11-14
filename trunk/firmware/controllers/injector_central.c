/*
 * @file    injector_central.c
 * @brief	Some utilities related to fuel injection
 *
 *
 *  Created on: Sep 8, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "engines.h"
#include "datalogging.h"
#include "injector_central.h"
#include "rficonsole_logic.h"

static Logging log;

int isInjectionEnabled = TRUE;
myfloat globalFuelCorrection = 1;

static int is_injector_enabled[NUMBER_OF_CYLINDERS];

void assertCylinderId(int cylinderId, char *msg) {
	int isValid = cylinderId >= 1 && cylinderId <= NUMBER_OF_CYLINDERS;
	if (!isValid) {
		//scheduleSimpleMsg(&log, "cid=", cylinderId);
		print("ERROR [%s] cid=%d\r\n", msg, cylinderId);
		chDbgAssert(isValid, "Cylinder ID", null);
	}
}

/**
 * @param cylinderId - from 1 to NUMBER_OF_CYLINDERS
 */
int isInjectorEnabled(int cylinderId) {
	assertCylinderId(cylinderId, "isInjectorEnabled");
	return is_injector_enabled[cylinderId - 1];
}

static void printStatus(void) {
	for (int id = 1; id <= NUMBER_OF_CYLINDERS; id++) {
		resetLogging(&log);

		append(&log, "injector");
		appendInt(&log, id);
		append(&log, DELIMETER);
		appendInt(&log, isInjectorEnabled(id));
		append(&log, DELIMETER);
		scheduleLogging(&log);
	}
}

static void setInjectorEnabled(int id, int value) {
	chDbgCheck(id >=0 && id < NUMBER_OF_CYLINDERS, "injector id");
	is_injector_enabled[id] = value;
	printStatus();
}

static void setGlobalFuelCorrection(int value) {
	if (value < 10 || value > 500)
		return;
	scheduleSimpleMsg(&log, "setting fuel mult=", value);
	globalFuelCorrection = value / 100.0;
}

void initInjectorCentral(void) {
	initLogging(&log, "InjectorCentral", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	for (int i = 0; i < NUMBER_OF_CYLINDERS; i++)
		is_injector_enabled[i] = true;
	printStatus();
	addConsoleAction2I("injector", setInjectorEnabled);

	addConsoleAction1("gfc", setGlobalFuelCorrection);
}
