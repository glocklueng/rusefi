/*
 * console_loop.c
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

#include "rpm_reporter.h"
#include "thermistors.h"
#include "output_pins.h"

#include "datalogging.h"
#include "crank_input.h"
#include "rficonsole_logic.h"
#include "advance_map.h"

#include "fuel_map.h"
#include "main_loop.h"
#include "engine_math.h"
#include "idle_thread.h"

#define INITIAL_FULL_LOG TRUE
//#define INITIAL_FULL_LOG FALSE

volatile int fullLog;
volatile int needToReportStatus = FALSE;
static int prevCkpEventCounter = -1;

static Logging log;
static char LOGGING_BUFFER[500];
#define FULL_LOGGING_KEY "fl"

static char* boolean2string(int value) {
	return value ? "YES" : "NO";
}

void setFullLog(int value) {
	print("Setting full logging: %s\r\n", boolean2string(value));
	printSimpleMsg(&log, FULL_LOGGING_KEY, value);
	fullLog = value;
}

static void printStatus() {
	needToReportStatus = TRUE;
}

static void printSensors() {
	debugFloat(&log, "vref", getVRef(), 2);

// white, MAF
	myfloat maf = getMaf();
	debugFloat(&log, "maf", maf, 2);

	myfloat map = getMap();
	logFloat(&log, LP_MAP, map);

	myfloat tps = getTPS();
	logInt(&log, LP_THROTTLE, tps);

	myfloat coolantTemp = getCoolantTemperature();
	logFloat(&log, LP_ECT, coolantTemp);
	myfloat airTemp = getIntakeAirTemperature();
	logFloat(&log, LP_IAT, airTemp);

	myfloat tcharge = getTCharge(getCurrentRpm(), tps, coolantTemp, airTemp);
	debugFloat(&log, "tch", tcharge, 2);
}

#if EFI_CUSTOM_PANIC_METHOD
extern char *dbg_panic_file;
extern int dbg_panic_line;
#endif

static void checkIfShouldHalt() {
#if CH_DBG_ENABLED
	if (dbg_panic_msg != NULL) {
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

void printState() {
	checkIfShouldHalt();
	printPending();

	pokeAdcInputs();

	if (!fullLog)
		return;

	int nowSeconds = chTimeNow() / SECOND_AS_TICKS;

	int currentCkpEventCounter = getCrankEventCounter();
	if (prevCkpEventCounter == currentCkpEventCounter && timeOfPreviousReport == nowSeconds)
		return;

	timeOfPreviousReport = nowSeconds;

	// current time, in milliseconds
	int nowMs = GetSysclockCounter() / TICKS_IN_MS;
	int rpm = getCurrentRpm();

	prevCkpEventCounter = currentCkpEventCounter;

	myfloat sec = ((myfloat) nowMs) / 1000;
	debugFloat(&log, "time", sec, 3);

	debugInt(&log, "ckp_c", currentCkpEventCounter);

	debugInt(&log, "rpm", rpm);


	debugInt(&log, "idl", getIdleSwitch());

//	debugFloat(&log, "table_spark", getAdvance(rpm, getMaf()), 2);

	if (MAF_MODE)
		debugFloat(&log, "table_fuel", getFuel(rpm, getMaf()), 2);
	else {
		myfloat map = getMap();
		myfloat fuel = getDefaultFuel(rpm, map);
		debugFloat(&log, "d_fuel", fuel, 2);
	}

	debugFloat(&log, "af", getAfr(), 2);

	printSensors();

#if EFI_WAVE_ANALYZER
	printWave(&log);
#endif

	printLine(&log);
}

static void showFuelMap(int rpm, int maf100) {
	myfloat maf = maf100 / 100.0;
	myfloat value = getFuel(rpm, maf);
	print("fuel map rpm=%d, maf=%d: %d\r\n", rpm, maf100, (int)(100 * value));
}

void initStatusLoop() {
	initLogging(&log, "status loop", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));

	setFullLog(INITIAL_FULL_LOG);

	addConsoleAction2I("sfm", showFuelMap);
	showFuelMap(2400, 280);

	addConsoleAction1(FULL_LOGGING_KEY, &setFullLog);
	addConsoleAction("status", printStatus);
}
