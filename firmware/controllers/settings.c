/**
 * @file settings.c
 * @brief This file is about configuring engine via the human-readable protocol
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "settings.h"

#include "eficonsole.h"
#include "engine_configuration.h"
#include "flash_main.h"
#include "engine_controller.h"
#include "rusefi.h"

static Logging logger;

static char LOGGING_BUFFER[1000];

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

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

char* getConfigurationName(engine_configuration_s *engineConfiguration) {
	switch (engineConfiguration->engineType) {
#if EFI_SUPPORT_DODGE_NEON
	case DODGE_NEON_1995:
		return "Dodge Neon";
#endif /* EFI_SUPPORT_DODGE_NEON */
#if EFI_SUPPORT_FORD_ASPIRE
	case FORD_ASPIRE_1996:
		return "Ford Aspire";
#endif /* EFI_SUPPORT_FORD_ASPIRE */
#if EFI_SUPPORT_FORD_FIESTA
	case FORD_FIESTA:
		return "Ford Fiesta";
#endif /* EFI_SUPPORT_FORD_FIESTA */
#if EFI_SUPPORT_NISSAN_PRIMERA
	case NISSAN_PRIMERA:
		return "Nissan Primera";
#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
	case HONDA_ACCORD:
		return "Honda Accord";
	case FORD_INLINE_6_1995:
		return "Ford 1995 inline 6";
	case GY6_139QMB:
		return "Gy6 139qmb";
	case MAZDA_MIATA_NB:
		return "Mazda Miata NB";
	default:
		return NULL;
	}
}

/**
 * @brief	Prints current engine configuration to human-readable console.
 */
void printConfiguration(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {

	resetLogging(&logger);
	appendPrintf(&logger, "msg%s%s", DELIMETER, getConfigurationName(engineConfiguration));
	printLine(&logger);

	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
//		print("line %d (%f): ", k, engineConfiguration->fuelKeyBins[k]);
//		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
//			print("%f ", engineConfiguration->fuelTable[k][r]);
//		}
//		print("\r\n");
	}

	printFloatArray("RPM bin: ", engineConfiguration->fuelRpmBins, FUEL_RPM_COUNT);

	printFloatArray("Y bin: ", engineConfiguration->fuelLoadBins, FUEL_LOAD_COUNT);

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
	scheduleSimpleMsg(&logger, "fixedModeTiming: ", (int) engineConfiguration->fixedModeTiming);
	scheduleMsg(&logger, "crankingChargeAngle=%f", engineConfiguration->crankingChargeAngle);
	scheduleMsg(&logger, "globalTriggerOffsetAngle=%f", engineConfiguration->globalTriggerOffsetAngle);

	scheduleSimpleMsg(&logger, "analogChartMode: ", engineConfiguration->analogChartMode);

	scheduleMsg(&logger, "crankingRpm: %d", engineConfiguration->crankingSettings.crankingRpm);

	scheduleMsg(&logger, "injectionPinMode: %d", engineConfiguration->injectionPinMode);
	scheduleMsg(&logger, "ignitionPinMode: %d", engineConfiguration->ignitionPinMode);
	scheduleMsg(&logger, "idlePinMode: %d", engineConfiguration->idlePinMode);
	scheduleMsg(&logger, "fuelPumpPinMode: %d", engineConfiguration->fuelPumpPinMode);
	scheduleMsg(&logger, "malfunctionIndicatorPinMode: %d", engineConfiguration->malfunctionIndicatorPinMode);
	scheduleMsg(&logger, "analogInputDividerCoefficient: %f", engineConfiguration->analogInputDividerCoefficient);


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
	engineConfiguration->timingMode = (timing_mode_e) value;
	doPrintConfiguration();
}

static void setEngineType(int value) {
	engineConfiguration->engineType = (engine_type_e) value;
	resetConfiguration((engine_type_e) value);
	writeToFlash();
	doPrintConfiguration();
	scheduleReset();
}

static void setInjectionPinMode(int value) {
	engineConfiguration->injectionPinMode = (pin_output_mode_e) value;
	doPrintConfiguration();
}

static void setIgnitionPinMode(int value) {
	engineConfiguration->ignitionPinMode = (pin_output_mode_e) value;
	doPrintConfiguration();
}

static void setIdlePinMode(int value) {
	engineConfiguration->idlePinMode = (pin_output_mode_e) value;
	doPrintConfiguration();
}

static void setIgnitonOffset(int value) {
	engineConfiguration->ignitonOffset = value;
	doPrintConfiguration();
}

static void setFuelPumpPinMode(int value) {
	engineConfiguration->fuelPumpPinMode = (pin_output_mode_e) value;
	doPrintConfiguration();
}

static void setMalfunctionIndicatorPinMode(int value) {
	engineConfiguration->malfunctionIndicatorPinMode = (pin_output_mode_e) value;
	doPrintConfiguration();
}

static void setAnalogChartMode(int value) {
	engineConfiguration->analogChartMode = value;
	doPrintConfiguration();
}

/**
 * For example
 * set_cranking_fuel_min 15 0
 * would be 15ms @ 0C
 */
static void setCrankingFuleMin(int timeMs, int tempC) {
	engineConfiguration->crankingSettings.coolantTempMinC = tempC;
	engineConfiguration->crankingSettings.fuelAtMinTempMs = timeMs;
	printTemperatureInfo();
}

static void setCrankingFuleMax(int timeMs, int tempC) {
	engineConfiguration->crankingSettings.coolantTempMaxC = tempC;
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = timeMs;
	printTemperatureInfo();
}

static void setGlobalTriggerOffsetAngle(int value) {
	engineConfiguration->globalTriggerOffsetAngle = value;
	doPrintConfiguration();
}

void initSettings(void) {
	initLoggingExt(&logger, "settings control", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));

	addConsoleActionI("set_ignition_offset", setIgnitonOffset);
	addConsoleActionI("set_global_trigger_offset_angle", setGlobalTriggerOffsetAngle);
	addConsoleActionI("set_analog_chart_mode", setAnalogChartMode);
	addConsoleActionI("set_fixed_mode_timing", setFixedModeTiming);
	addConsoleActionI("set_timing_mode", setTimingMode);
	addConsoleActionI("set_engine_type", setEngineType);

	addConsoleActionI("set_injection_pin_mode", setInjectionPinMode);
	addConsoleActionI("set_ignition_pin_mode", setIgnitionPinMode);
	addConsoleActionI("set_idle_pin_mode", setIdlePinMode);
	addConsoleActionI("set_fuel_pump_pin_mode", setFuelPumpPinMode);
	addConsoleActionI("set_malfunction_indicator_pin_mode", setMalfunctionIndicatorPinMode);
	// todo: start saving values into flash right away?


	addConsoleActionII("set_cranking_fuel_min", setCrankingFuleMin);
	addConsoleActionII("set_cranking_fuel_max", setCrankingFuleMax);
}

