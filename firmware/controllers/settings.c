/**
 * @file settings.c
 * @brief This file is about configuring engine via the human-readable protocol
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "settings.h"

#include "rficonsole.h"
#include "datalogging.h"
#include "engine_configuration.h"
#include "flash_main.h"

static Logging logger;

static char LOGGING_BUFFER[1000];

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

static void printIntArray(int array[], int size) {
	for (int j = 0; j < size; j++)
		print("%d ", array[j]);
	print("\r\n");
}

void printFloatArray(char *prefix, float array[], int size) {
//	appendMsgPrefix(&logger);
//	appendPrintf(&logger, prefix);
//	for (int j = 0; j < size; j++)
//		appendPrintf(&logger, "%f ", array[j]);
//	appendPrintf(&logger, DELIMETER);
//	scheduleLogging(&logger);
}

char* getConfigurationName(EngineConfiguration *engineConfiguration) {
	switch (engineConfiguration->engineType) {
	case FORD_ASPIRE_1996:
		return "Ford Aspire";
	case FORD_FIESTA:
		return "Ford Fiesta";
	default:
		return NULL;
	}
}

/**
 * @brief	Prints current engine configuration to human-readable console.
 */
void printConfiguration(EngineConfiguration *engineConfiguration, EngineConfiguration2 *engineConfiguration2) {

	resetLogging(&logger);
	appendPrintf(&logger, "msg%s%s", DELIMETER, getConfigurationName(engineConfiguration));
	printLine(&logger);

	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
//		print("line %d (%f): ", k, engineConfiguration->fuelKeyBins[k]);
//		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
//			print("%f ", engineConfiguration->fuelTable[k][r]);
//		}
//		print("\r\n");
	}

	printFloatArray("RPM bin: ", engineConfiguration->fuelRpmBins, FUEL_RPM_COUNT);

	printFloatArray("Y bin: ", engineConfiguration->fuelKeyBins, FUEL_MAF_COUNT);

	printFloatArray("CLT: ", engineConfiguration->cltFuelCorr, CLT_CURVE_SIZE);
	printFloatArray("CLT bins: ", engineConfiguration->cltFuelCorrBins, CLT_CURVE_SIZE);

	printFloatArray("IAT: ", engineConfiguration->iatFuelCorr, IAT_CURVE_SIZE);
	printFloatArray("IAT bins: ", engineConfiguration->iatFuelCorrBins, IAT_CURVE_SIZE);

	printFloatArray("vBatt: ", engineConfiguration->battInjectorLagCorr, VBAT_INJECTOR_CURVE_SIZE);
	printFloatArray("vBatt bins: ", engineConfiguration->battInjectorLagCorrBins, VBAT_INJECTOR_CURVE_SIZE);

//	appendMsgPrefix(&logger);

	scheduleSimpleMsg(&logger, "rpmHardLimit: ", engineConfiguration->rpmHardLimit);

	scheduleSimpleMsg(&logger, "tpsMin: ", engineConfiguration->tpsMin);
	scheduleSimpleMsg(&logger, "tpsMax: ", engineConfiguration->tpsMax);

	scheduleSimpleMsg(&logger, "timingMode: ", engineConfiguration->timingMode);
	scheduleSimpleMsg(&logger, "fixedModeTiming: ", engineConfiguration->fixedModeTiming);
	scheduleSimpleMsg(&logger, "crankingChargeAngle: ", engineConfiguration->crankingChargeAngle);

	scheduleSimpleMsg(&logger, "analogChartMode: ", engineConfiguration->analogChartMode);

	scheduleSimpleMsg(&logger, "crankingRpm: ", engineConfiguration->crankingSettings.crankingRpm);
//	appendPrintf(&logger, DELIMETER);
//	scheduleLogging(&logger);
}

static void doPrintConfiguration(void) {
	printConfiguration(engineConfiguration, engineConfiguration2);
}

static void setFixedModeTiming(int value) {
	engineConfiguration->fixedModeTiming = value;
	doPrintConfiguration();
}

static void setTimingMode(int value) {
	engineConfiguration->timingMode = value;
	doPrintConfiguration();
}

static void setEngineType(int value) {
	engineConfiguration->engineType = value;
	resetConfiguration(value);
	writeToFlash();
	doPrintConfiguration();
}

static void setIgnitonOffset(int value) {
	engineConfiguration->ignitonOffset = value;
	doPrintConfiguration();
}

static void setAnalogChartMode(int value) {
	engineConfiguration->analogChartMode = value;
	doPrintConfiguration();
}

void initSettings(void) {
	initLoggingExt(&logger, "settings control", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));

	addConsoleActionI("set_ignition_offset", &setIgnitonOffset);
	addConsoleActionI("set_analog_chart_mode", &setAnalogChartMode);
	addConsoleActionI("set_fixed_mode_timing", &setFixedModeTiming);
	addConsoleActionI("set_timing_mode", &setTimingMode);
	addConsoleActionI("set_engine_type", &setEngineType);
}

