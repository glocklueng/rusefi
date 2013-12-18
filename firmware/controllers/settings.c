/**
 * @file settings.c
 * @brief This file is about configuring engine via the human-readable protocol
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "settings.h"

#include "rficonsole.h"
#include "datalogging.h"
#include "main.h"
#include "engine_configuration.h"

static volatile int injectionOffset = 0;

static Logging logger;

extern EngineConfiguration *engineConfiguration;

static void printSettings(void) {
	appendPrintf(&logger, "msg,injectionOffset %d%s", injectionOffset, DELIMETER);

	printLine(&logger);
}

static void setIgnitonOffset(int value) {
	engineConfiguration->ignitonOffset = value;
	printSettings();
}

void initSettings(void) {
	initLogging(&logger, "settings control");

	addConsoleActionI("set_ignition_offset", &setIgnitonOffset);
}

