/*
 * console_loop.c
 *
 *  Created on: Mar 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "status_loop.h"

#include "adc_inputs.h"
#if WAVE_ANALYZER
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

volatile int fullLog;
volatile int needToReportStatus = FALSE;
static Logging logging;

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

int prevAdc0 = -1;
int prevAdc1 = -1;
int prevAdc2 = -1;
int prevAdc3 = -1;
int prevAdc4 = -1;
int prevAdc5 = -1;
int prevAdc6 = -1;
int prevAdc7 = -1;
int prevNow = -1;
int prevRpm = -1;
int prevWave = -1;
int prevSkips = -1;
int prevRpmDiff = -1;
systime_t prevCrankWidthTime = -1;
systime_t prevCrankPeriodTime = -1;
int prevWW = -1;
int prevWP = -1;

static void printSensors() {
	int adc0 = getAdcValue(0); /* PA6 - white */
	int adc1 = getAdcValue(1); /* PA7 - blue TP */
	int adc2 = getAdcValue(2); /* PC4 - green */
	int adc3 = getAdcValue(3); /* PC5 - yellow */
	int adc4 = getAdcValue(4); /* PB0 - blue */
//	int adc5 = getAdcValue(5); /* PB1 - white MAF */
	int adc6 = getAdcValue(6); /* PC2 - green */
	int adc7 = getAdcValue(7); /* PC3 - yellow */

	//	debugInt("adc6", adc6);

	debugFloat(&logging, "vref", getVRef(), 2);

	//	debugInt("adc0", adc0);
	//	debugInt("adc1", adc1);
	//	debugInt("adc2", adc2);
	//	debugInt("adc3", adc3);

	// blue, O2
	//	debugInt("adc4", adc4);

	// white, MAF
	myfloat maf = getMaf();
	debugFloat(&logging, "maf", maf, 2);

	// white
	myfloat volts_0 = adcToVolts2(adc0);
	//	debugInt("adc0", (int)(volts_0 * 100));
	myfloat map = getHondaMAPValue(adc0);
	//	logFloat(LP_MAP, map);

	// blue, 1st board
	myfloat volts_1 = adcToVolts2(adc1);
	int tpsValue = getTpsValue(volts_1);
	logInt(&logging, LP_THROTTLE, tpsValue);

	// green
	myfloat temp2 = getFtemp(adc2);
	logFloat(&logging, LP_ECT, temp2);

	// yellow
	myfloat volts3 = adcToVolts2(adc3);
//		myfloat resistance3 = getR2InVoltageDividor(volts3);
//		myfloat temp3 = tempKtoF(getTempK(resistance3));
	//	print("adc3,%d,", (int)(volts3 * 100));
	//	logFloat(LP_IAT, temp3);
}

void printState() {
//	if (needToReportStatus) {
//		needToReportStatus = FALSE;
//		debugInt(&logging, "wavemode0", getWaveMode(0));
//		debugInt(&logging, "wavemode1", getWaveMode(1));
//	}

	if (!fullLog)
		return;

	systime_t crankWidthTime = getCrankWidthTime();
	systime_t crankPeriodTime = getCrankPeriodTime();

//	int ignitionW = getWidthEventTime(0);
//	int ignitionP = wGetPeriodStart(0);
//	int wW = getWidthEventTime(0);
//	int wP = wGetPeriodStart(0);

	// current time, in milliseconds
	int nowMs = GetSysclockCounter() / MS_DIVIDER;
	int rpm = getCurrentRpm();
//	int skips = getFilterSkips();
//	int rpmDiff = getCurrentRpmEventDiff();

//	int wave0 = getWaveWidth(0);
//	int wOffset0 = getWaveOffset(0);
//	int wave1 = getWaveWidth(1);
//	int wOffset1 = getWaveOffset(1);

//	int oneToZero = getOneToZeroTime();
//	int wS = wGetPeriodStart(0);
//	int crankStart = getCrankStart();

	if (1
//			&& prevNow == nowMs

//			&& prevAdc0 == adc0
//			&& prevAdc1 == adc1
//			&& prevAdc2 == adc2
//			&& prevAdc3 == adc3
//			&& prevAdc4 == adc4
//			&& prevAdc5 == adc5
//			&& prevAdc6 == adc6
//			&& prevAdc7 == adc7

			&& prevRpm == rpm && prevCrankPeriodTime == crankPeriodTime
			&& prevCrankWidthTime == crankWidthTime
//			&& prevWW == wW
//			&& prevWP == wP

//			prevWave == wave0 &&
//			prevSkips == skips &&
//			prevRpmDiff == rpmDiff
					)
		return;
	prevNow = nowMs;
//	prevAdc0 = adc0;
//	prevAdc1 = adc1;
//	prevAdc2 = adc2;
//	prevAdc3 = adc3;
//	prevAdc4 = adc4;
//	prevAdc5 = adc5;
//	prevAdc6 = adc6;
//	prevAdc7 = adc7;

	prevRpm = rpm;

	prevCrankPeriodTime = crankPeriodTime;
	prevCrankWidthTime = crankWidthTime;
//	prevWW = wW;
//	prevWP = wP;

	logStartLine(&logging);

	myfloat sec = ((myfloat) nowMs) / 1000;
	debugFloat(&logging, "time", sec, 3);

//	debugInt("crankW", crankWidthTime);
//	debugInt("crankP", crankPeriodTime);
//	debugInt("wW", wW);
//	debugInt("wP", wP);

	//	debugInt("temp", MS_DIVIDER * 3.6); good news - it is 360

//	print("skips,%d,timediff,%4d,", skips, rpmDiff);

//	print("dW,%4d,wS,%4d,crank,%d,", oneToZero, wS, crankStart);

//	print("wave0,%5d,%5d,", wave0, wOffset0);

//	print("wave0,%5d,%5d,wave1,%5d,%5d,", wave0, wOffset0, wave1, wOffset1);

	debugInt(&logging, "rpm", rpm);

	debugFloat(&logging, "table_ign", getAdvance(rpm, getMaf()), 2);
	debugFloat(&logging, "table_inj", getFuel(rpm, getMaf()), 2);

	printSensors();

#ifdef WAVE_ANALYZER
	printWave(&logging);
#endif

	printLine(&logging);
}

void initStatusLoop() {
	setFullLog(INITIAL_FULL_LOG);

	addConsoleAction1("fl", &setFullLog);
	addConsoleAction("status", printStatus);
}
