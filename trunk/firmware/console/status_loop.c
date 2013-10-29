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
#include "shaft_position_input.h"
#include "rficonsole_logic.h"
#include "advance_map.h"
#include "print.h"

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
static Logging log2;
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

static void printStatus(void) {
	needToReportStatus = TRUE;
}

//float getTCharge1(myfloat tps) {
//	myfloat cltK = tempCtoKelvin(getCoolantTemperature());
//	myfloat iatK = tempCtoKelvin(getIntakeAirTemperature());
//	return getTCharge(getCurrentRpm(), tps, cltK, iatK);
//}

static void printSensors(void) {
	debugFloat(&log, "vref", getVRef(), 2);

// white, MAF
	myfloat maf = getMaf();
	debugFloat(&log, "maf", maf, 2);

#if ENGINE_HAS_MAP_SENSOR
	myfloat map = getMap();
	logFloat(&log, LP_MAP, map);
#endif

	myfloat tps = getTPS();
	logInt(&log, LP_THROTTLE, tps);

#if ENGINE_HAS_COOLANT_SENSOR
	myfloat coolantTemp = getCoolantTemperature();
	logFloat(&log, LP_ECT, coolantTemp);
#endif

	myfloat airTemp = getIntakeAirTemperature();
	logFloat(&log, LP_IAT, airTemp);

//	debugFloat(&log, "tch", getTCharge1(tps), 2);
}

#if EFI_CUSTOM_PANIC_METHOD
extern char *dbg_panic_file;
extern int dbg_panic_line;
#endif

static void checkIfShouldHalt(void) {
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
	debugFloat(&log, "time", sec, 3);

	debugInt(&log, "ckp_c", currentCkpEventCounter);

	debugInt(&log, "rpm", rpm);

	debugInt(&log, "idl", getIdleSwitch());

//	debugFloat(&log, "table_spark", getAdvance(rpm, getMaf()), 2);

	if (MAF_MODE)
		debugFloat(&log, "table_fuel", getFuel(rpm, getMaf()), 2);
	else {
#if ENGINE_HAS_MAP_SENSOR
		myfloat map = getMap();
		myfloat fuel = getDefaultFuel(rpm, map);
		debugFloat(&log, "d_fuel", fuel, 2);
#endif
	}

	debugFloat(&log, "af", getAfr(), 2);

	printSensors();

#if EFI_WAVE_ANALYZER
	printWave(&log);
#endif

	printLine(&log);
}

/*
 * command example:
 * sfm 3500 400
 * that would be 'show fuel for rpm 3500 maf 4.0'
 */

static void showFuelMap(int rpm, int key100) {
	myfloat key = key100 / 100.0;
	myfloat value = getFuel(rpm, key);
	print("fuel map rpm=%d, key=%f: %d\r\n", rpm, key, (int) (100 * value));

	scheduleSimpleMsg(&log2, "fuel map value *100 = ", 100 * value);
}

void initStatusLoop(void) {
	initLogging(&log, "status loop", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
	initLogging(&log2, "main event handler", log2.DEFAULT_BUFFER, sizeof(log2.DEFAULT_BUFFER));

	setFullLog(INITIAL_FULL_LOG);

	addConsoleAction2I("sfm", showFuelMap);
	showFuelMap(2400, 280);

	addConsoleAction1(FULL_LOGGING_KEY, &setFullLog);
	addConsoleAction("status", printStatus);
}
