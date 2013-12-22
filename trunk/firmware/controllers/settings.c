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

static Logging logger;

extern EngineConfiguration *engineConfiguration;

static void printSettings(void) {
}

static void setAnalogChartMode(int value) {
	engineConfiguration->analogChartMode = value;
	printSettings();
}

static void setIgnitonOffset(int value) {
	engineConfiguration->ignitonOffset = value;
	printSettings();
}

void initSettings(void) {
	initLogging(&logger, "settings control");

	addConsoleActionI("set_ignition_offset", &setIgnitonOffset);
	addConsoleActionI("set_analog_chart_mode", &setAnalogChartMode);
}

