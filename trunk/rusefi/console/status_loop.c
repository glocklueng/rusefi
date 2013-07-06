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

#include "datalogging.h"
#include "crank_input.h"
#include "rficonsole_logic.h"
#include "advance_map.h"

#include "fuel_map.h"
#include "main_loop.h"

#define INITIAL_FULL_LOG TRUE
//#define INITIAL_FULL_LOG FALSE

volatile int fullLog;
volatile int needToReportStatus = FALSE;
static int prevCkpEventCounter = -1;

static Logging log;
static char LOGGING_BUFFER[500];

static char* boolean2string(int value) {
	return value ? "YES" : "NO";
}

void setFullLog(int value) {
	print("Setting full logging: %s\r\n", boolean2string(value));
	fullLog = value;
}

static void printStatus() {
	needToReportStatus = TRUE;
}

static void printSensors() {
//	int adc0 = getAdcValue(0); /* PA6 - white */
//	int adc1 = getAdcValue(1); /* PA7 - blue TP */
//	int adc2 = getAdcValue(2); /* PC4 - green */
//	int adc3 = getAdcValue(3); /* PC5 - yellow */
//	int adc4 = getAdcValue(4); /* PB0 - blue */
////	int adc5 = getAdcValue(5); /* PB1 - white MAF */
//	int adc6 = getAdcValue(6); /* PC2 - green */
//	int adc7 = getAdcValue(7); /* PC3 - yellow VREF */

	//	debugInt("adc6", adc6);

	debugFloat(&log, "vref", getVRef(), 2);

	//	debugInt("adc0", adc0);
	//	debugInt("adc1", adc1);
	//	debugInt("adc2", adc2);
	//	debugInt("adc3", adc3);

	// blue, O2
	//	debugInt("adc4", adc4);

	// white, MAF
	myfloat maf = getMaf();
	debugFloat(&log, "maf", maf, 2);

	// white
//	myfloat volts_0 = adcToVolts2(adc0);
	//	debugInt("adc0", (int)(volts_0 * 100));
//	myfloat map = getHondaMAPValue(adc0);
	//	logFloat(LP_MAP, map);

	// blue, 1st board
//	myfloat volts_1 = adcToVolts2(adc1);
//	int tpsValue = getTpsValue(volts_1);
//	logInt(&log, LP_THROTTLE, tpsValue);

	// green
//	myfloat temp2 = getFtemp(adc2);
//	logFloat(&log, LP_ECT, temp2);

	// yellow
//	myfloat volts3 = adcToVolts2(adc3);
//		myfloat resistance3 = getR2InVoltageDividor(volts3);
//		myfloat temp3 = tempKtoF(getTempK(resistance3));
	//	print("adc3,%d,", (int)(volts3 * 100));
	//	logFloat(LP_IAT, temp3);
}

static void checkIfShouldHalt() {
#if CH_DBG_ENABLED
	if (dbg_panic_msg != NULL ) {
		print("my FATAL [%s]\r\n", dbg_panic_msg);
		while (TRUE) {
		}
		chSysHalt();
	}
#endif
}

void printState() {
	checkIfShouldHalt();
	printPending();

//	if (needToReportStatus) {
//		needToReportStatus = FALSE;
//		debugInt(&logging, "wavemode0", getWaveMode(0));
//		debugInt(&logging, "wavemode1", getWaveMode(1));
//	}

	if (!fullLog)
		return;

	int currentCkpEventCounter = getCrankEventCounter();

	// current time, in milliseconds
	int nowMs = GetSysclockCounter() / TICKS_IN_MS;
	int rpm = getCurrentRpm();

	if (1
			&& prevCkpEventCounter == currentCkpEventCounter
					)
		return;
//	prevNow = nowMs;
	prevCkpEventCounter = currentCkpEventCounter;

	resetLogging(&log);

	myfloat sec = ((myfloat) nowMs) / 1000;
	debugFloat(&log, "time", sec, 3);


	debugInt(&log, "rpm", rpm);

	debugFloat(&log, "table_spark", getAdvance(rpm, getMaf()), 2);
	debugFloat(&log, "table_fuel", getFuel(rpm, getMaf()), 2);

	printSensors();

#ifdef EFI_WAVE_ANALYZER
	printWave(&log);
#endif

	printLine(&log);
}

void initStatusLoop() {
	initLogging(&log, "status loop", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
	setFullLog(INITIAL_FULL_LOG);

	addConsoleAction1("fl", &setFullLog);
	addConsoleAction("status", printStatus);
}
