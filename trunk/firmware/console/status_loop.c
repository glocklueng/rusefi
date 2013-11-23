/**
 * @file	status_loop.c
 *
 *  Created on: Mar 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "status_loop.h"

#include "adc_inputs.h"
#if EFI_WAVE_ANALYZER
#include "wave_analyzer.h"
#endif

#include "sensors.h"
#include "rpm_calculator.h"
#include "thermistors.h"
#include "output_pins.h"

#include "datalogging.h"
#include "shaft_position_input.h"
#include "rficonsole_logic.h"
#include "advance_map.h"

#include "wave_math.h"

#include "fuel_map.h"
#include "main_loop.h"
#include "engine_math.h"
#include "idle_thread.h"

#define INITIAL_FULL_LOG TRUE
//#define INITIAL_FULL_LOG FALSE

volatile int fullLog;
volatile int needToReportStatus = FALSE;
static int prevCkpEventCounter = -1;

static Logging logger;
static Logging logger2;
static char LOGGING_BUFFER[500];
#define FULL_LOGGING_KEY "fl"

static time_t timeOfPreviousWarning = -10 * CH_FREQUENCY;

static char* boolean2string(int value) {
	return value ? "YES" : "NO";
}

void setFullLog(int value) {
	print("Setting full logging: %s\r\n", boolean2string(value));
	printSimpleMsg(&logger, FULL_LOGGING_KEY, value);
	fullLog = value;
}

static void printStatus(void) {
	needToReportStatus = TRUE;
}

//float getTCharge1(myfloat tps) {
//	myfloat cltK = tempCtoKelvin(getCoolantTemperature());
//	myfloat iatK = tempCtoKelvin(getIntakeAirTemperature());
//	return getTCharge(getCurrentRpm(), tps, cltK, iatK);
//}

static void printSensors(void) {
	debugFloat(&logger, "vref", getVRef(), 2);

// white, MAF
	myfloat maf = getMaf();
	debugFloat(&logger, "maf", maf, 2);

#if ENGINE_HAS_MAP_SENSOR
	myfloat map = getMap();
	logFloat(&logger, LP_MAP, map);
#endif

	myfloat tps = getTPS();
	logInt(&logger, LP_THROTTLE, tps);

#if ENGINE_HAS_COOLANT_SENSOR
	myfloat coolantTemp = getCoolantTemperature();
	logFloat(&logger, LP_ECT, coolantTemp);
#endif

	myfloat airTemp = getIntakeAirTemperature();
	logFloat(&logger, LP_IAT, airTemp);

//	debugFloat(&logger, "tch", getTCharge1(tps), 2);
}

#if EFI_CUSTOM_PANIC_METHOD
extern char *dbg_panic_file;
extern int dbg_panic_line;
#endif

void onDbgPanic(void) {
	setOutputPinValue(LED_FATAL, 1);
}

int hasFatalError(void) {
	return dbg_panic_msg != NULL ;
}

static void checkIfShouldHalt(void) {
#if CH_DBG_ENABLED
	if (hasFatalError()) {
		setOutputPinValue(LED_FATAL, 1);
#if EFI_CUSTOM_PANIC_METHOD
		print("my FATAL [%s] at %s:%d\r\n", dbg_panic_msg, dbg_panic_file, dbg_panic_line);
#else
		print("my FATAL [%s] at %s:%d\r\n", dbg_panic_msg);
#endif
		chThdSleepSeconds(1);
		while (TRUE) {
		}
		chSysHalt();
	}
#endif
}

static int timeOfPreviousReport = -1;

void printState(void) {
	if (!is_serial_ready())
		return;
	checkIfShouldHalt();
	printPending();

	pokeAdcInputs();

	if (!fullLog)
		return;

	systime_t nowSeconds = chTimeNowSeconds();

	int currentCkpEventCounter = getCrankEventCounter();
	if (prevCkpEventCounter == currentCkpEventCounter && timeOfPreviousReport == nowSeconds)
		return;

	timeOfPreviousReport = nowSeconds;

	// current time, in milliseconds
	int nowMs = chTimeNow() / TICKS_IN_MS;
	int rpm = getCurrentRpm();

	prevCkpEventCounter = currentCkpEventCounter;

	myfloat sec = ((myfloat) nowMs) / 1000;
	debugFloat(&logger, "time", sec, 3);

	debugInt(&logger, "ckp_c", currentCkpEventCounter);

	debugInt(&logger, "rpm", rpm);

	debugInt(&logger, "idl", getIdleSwitch());

//	debugFloat(&logger, "table_spark", getAdvance(rpm, getMaf()), 2);

	if (MAF_MODE)
		debugFloat(&logger, "table_fuel", getFuel(rpm, getMaf()), 2);
	else {
#if ENGINE_HAS_MAP_SENSOR
		myfloat map = getMap();
		myfloat fuel = getDefaultFuel(rpm, map);
		debugFloat(&logger, "d_fuel", fuel, 2);
#endif
	}

	debugFloat(&logger, "af", getAfr(), 2);

	printSensors();

#if EFI_WAVE_ANALYZER
	printWave(&logger);
#endif

	printLine(&logger);
}

/*
 * command example:
 * sfm 3500 400
 * that would be 'show fuel for rpm 3500 maf 4.0'
 */

static void showFuelMap(int rpm, int key100) {
	myfloat key = key100 / 100.0;

	float baseFuel = getBaseFuel(rpm, key);

	float iatCorrection = getIatCorrection(getIntakeAirTemperature());
	float cltCorrection = getCltCorrection(getCoolantTemperature());
	float injectorLag = getInjectorLag(getVBatt());
	print("baseFuel=%f\r\n", baseFuel);

	print("iatCorrection=%f cltCorrection=%f injectorLag=%d\r\n", iatCorrection, cltCorrection,
			(int) (100 * injectorLag));

	myfloat value = getFuel(rpm, key);

	print("fuel map rpm=%d, key=%f: %d\r\n", rpm, key, (int) (100 * value));

	scheduleSimpleMsg(&logger2, "fuel map value *100 = ", 100 * value);
}

void initStatusLoop(void) {
	initLogging(&logger, "status loop", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
	initLogging(&logger2, "main event handler", logger2.DEFAULT_BUFFER, sizeof(logger2.DEFAULT_BUFFER));

	setFullLog(INITIAL_FULL_LOG);

	addConsoleAction2I("sfm", showFuelMap);

	addConsoleAction1(FULL_LOGGING_KEY, &setFullLog);
	addConsoleAction("status", printStatus);
}

void warning(char *msg, float value) {
	time_t now = chTimeNow();
	if (overflowDiff(now, timeOfPreviousWarning) < CH_FREQUENCY)
		return; // we just had another warning, let's not spam
	timeOfPreviousWarning = now;

	scheduleSimpleMsg(&logger, msg, 1000 * value);
}
