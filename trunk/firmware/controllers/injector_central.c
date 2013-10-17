/*
 *  Created on: Sep 8, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    injector_central.c
 */

#include "main.h"
#include "engine.h"
#include "datalogging.h"
#include "injector_central.h"
#include "rficonsole_logic.h"

static Logging log;

static int is_injector_enabled[NUMBER_OF_CYLINDERS];

int isInjectorEnabled(int cylinderId) {
	return is_injector_enabled[cylinderId];
}

static void printStatus() {
	for (int id = 0; id < NUMBER_OF_CYLINDERS; id++) {
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

void initInjectorCentral(void) {
	initLogging(&log, "InjectorCentral", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	for (int i = 0; i < NUMBER_OF_CYLINDERS; i++)
		is_injector_enabled[i] = true;
	printStatus();
	addConsoleAction2I("injector", setInjectorEnabled);
}
