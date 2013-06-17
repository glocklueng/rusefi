/*
 * main_loop.c
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "main_loop.h"
#include "status_leds.h"
#include "engine_controller.h"
#include "injector_control.h"
#include "crank_input.h"
#include "rpm_reporter.h"
#include "ckp_events.h"
#include "sparkout.h"
#include "rficonsole.h"
#include "advance_map.h"
#include "adc_inputs.h"
#include "fuel_map.h"


//static int advance = 0;
static Logging logging;

//static void setAdvance(int value) {
//	if (value < -40 || value > 50) {
//		print("Invalid: %d\r\n", value);
//		return;
//	}
//	print("Setting advance: %d\r\n", value);
//	advance = value;
//}

void onEveryMillisecondTimerSignal(int ignore) {
	if (!isCranking())
		setStatusLed(LED_CRANKING, FALSE);
	if (getCurrentRpm() == 0) {
		setStatusLed(LED_RPM, FALSE);
		setStatusLed(LED_DEBUG, FALSE);
	}
}

myfloat getMaf() {
	int adc5 = getAdcValue(5); /* PB1 - white MAF */
	return adcToVolts2(adc5);
}

myfloat getVRef() {
	int adc7 = getAdcValue(7);
	myfloat volts_7 = adcToVolts2(adc7);
	return volts_7;
}

static int getWaveLengthByRpm(int rpm) {
	/**
	 * we are dividing 1163100, should be fine with integer precision
	 */
	return (int) (STROKE_TIME_CONSTANT * ASPIRE_MAGIC_DUTY_CYCLE * MS_DIVIDER)
			/ rpm;
}

static int getWaveLengthByRpm2(int rpm) {
	/**
	 * we are dividing 1163100, should be fine with integer precision
	 */
	return (int) (STROKE_TIME_CONSTANT * (1 - ASPIRE_MAGIC_DUTY_CYCLE)
			* MS_DIVIDER) / rpm;
}

static int getWaveLength() {
	return getWaveLengthByRpm(getCurrentRpm());
}

static void onCrankingShaftSignal(int ckpSignalType) {
	setStatusLed(LED_CRANKING, TRUE);
	if (ckpSignalType != CKP_PRIMARY_FALL)
		return;

	/**
	 * while cranking, ignition wave is same as the *MAGIC* wave
	 * our implementation sets the wave width based on current RPM value
	 *
	 */
	int duration = getWaveLength();
	scheduleSparkOut(0, duration);
	scheduleFuelInjection(MS_DIVIDER,
			getCrankingInjectionPeriod() * MS_DIVIDER / 10);
}

static int getAdvanceByRpm2(int rpm, int advance) {
	return (int) (advance * STROKE_TIME_CONSTANT * MS_DIVIDER / 90 / rpm);
}

//static int getAdvanceByRpm(int rpm) {
//	return getAdvanceByRpm2(rpm, advance);
//}

int shaftCounter = 0;

static void onRunningShaftSignal(int ckpSignalType) {
	if (ckpSignalType != CKP_PRIMARY_FALL)
		return;
	/**
	 * while cranking, ignition wave is same as *MAGIC* wave
	 * for a couple resolutions after cranking, ignition width is variable and finally
	 * while running, ignition width is always 3.6ms
	 */

	/**
	 * at 1000 rpm, wave length is 1163.1 systicks = 11.63 ms
	 * dwell is 360 systicks
	 * 220
	 */

	shaftCounter++;

	int rpm = getCurrentRpm();

	if (rpm > 15000) {
		queueSimpleMsg(&logging, "CRAZY RPM ", rpm);
		return;
	}

	int timeTillTDC = getWaveLength();

	float advance = getAdvance(rpm, getMaf());

	//advance = 0;
	int advanceTime = getAdvanceByRpm2(rpm, advance);

	int dwell = MS_DIVIDER * 4;
	scheduleSparkOut(timeTillTDC - advanceTime - dwell, dwell);

	if (shaftCounter % getInjectionDivider() != 0)
		return;


//	int injectionPeriod = getInjectionPeriod() * MS_DIVIDER / 10;

	int injectionPeriod = getFuel(rpm, getMaf()) * MS_DIVIDER;

	int offset = getInjectionOffset();
	int advanceTime2 = getAdvanceByRpm2(getCurrentRpm(), offset);

	int timeTillTDC2 = getWaveLengthByRpm2(getCurrentRpm());

	scheduleFuelInjection(timeTillTDC2 + advanceTime2 - injectionPeriod,
			injectionPeriod);
}

static void onShaftSignal(int ckpSignalType) {
	int rpmBeforeUpdate = getCurrentRpm();

	if (rpmBeforeUpdate == 0)
		return;

	if (isCranking()) {
		onCrankingShaftSignal(ckpSignalType);
		return;
	}

	onRunningShaftSignal(ckpSignalType);
}

void initMainLoop() {
//	addConsoleAction1("sa", setAdvance);
//	initTimers();
	registerCkpListener(&onShaftSignal, "main loop");
}

