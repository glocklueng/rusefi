/*
 * main_loop.c
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "main_loop.h"
#include "output_pins.h"
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

#define RPM_HARD_LIMIT 8000
static int isControlActive = TRUE;

/**
 * ignition order, same as fuel injection order: 1-3-4-2
 */
static int FIRING_ORDER[NUMBER_OF_CYLINDERS] = { 1, 3, 4, 2 };

/**
 * this is not cylinder number - this is the index of a cylinder in the ignition sequence
 */
static int currentCylinderIndex;

static int shaftCounter = 0;
static Logging log;

void onEveryMillisecondTimerSignal(int ignore) {
	if (!isCranking())
		setOutputPinValue(LED_CRANKING, FALSE);
	if (getCurrentRpm() == 0) {
		setOutputPinValue(LED_RPM, FALSE);
		setOutputPinValue(LED_DEBUG, FALSE);
	}
}

myfloat getMaf() {
	int mafAdc = getAdcValue(ADC_CHANNEL_MAF);
	return adcToVolts2(mafAdc);
}

myfloat getVRef() {
	int mafVref = getAdcValue(ADC_CHANNEL_VREF);
	return adcToVolts2(mafVref);
}

static int getShortWaveLengthByRpm(int rpm) {
	/**
	 * we are dividing 1163100, should be fine with integer precision
	 */
	return (int) (STROKE_TIME_CONSTANT * ASPIRE_MAGIC_DUTY_CYCLE) / rpm;
}

static int getFullWaveLengthByRpm(int rpm) {
	return STROKE_TIME_CONSTANT / rpm;
}

static int getWaveLengthByRpm2(int rpm) {
	/**
	 * we are dividing 1163100, should be fine with integer precision
	 */
	return (int) (STROKE_TIME_CONSTANT * (1 - ASPIRE_MAGIC_DUTY_CYCLE)) / rpm;
}

static int getShortWaveLength() {
	return getShortWaveLengthByRpm(getCurrentRpm());
}

static void onCrankingShaftSignal(int ckpSignalType) {
	setOutputPinValue(LED_CRANKING, TRUE);
	if (ckpSignalType != CKP_PRIMARY_UP)
		return;

	/**
	 * while cranking, ignition wave is same as the *MAGIC* wave
	 * our implementation sets the wave width based on current RPM value
	 *
	 */
	int duration = getShortWaveLength();
	scheduleSparkOut(0, duration);
	for (int id = 1; id <= NUMBER_OF_CYLINDERS; id++)
		scheduleFuelInjection(TICKS_IN_MS, getCrankingInjectionPeriod() * TICKS_IN_MS / 10, id);
}

static int convertAngleToSysticks(int rpm, int advance) {
	return (int) (advance * STROKE_TIME_CONSTANT / 90 / rpm);
}

//static int getAdvanceByRpm(int rpm) {
//	return getAdvanceByRpm2(rpm, advance);
//}

static int getSparkDwell(int rpm) {
	int defaultDwell = TICKS_IN_MS * 4;
	if (rpm <= 4500)
		return defaultDwell;
	rpm -= 4500;
	// for each 2000 rpm above 4500 rom we reduce dwell by 1 ms
	int dec = rpm * TICKS_IN_MS / 2000;
	return defaultDwell - dec;
}

static void scheduleSpark(int rpm, int ckpSignalType) {
	int timeTillNextRise = getFullWaveLengthByRpm(rpm);

	float advance = getAdvance(rpm, getMaf());

	//advance = 0;
	int sparkAdvance = convertAngleToSysticks(rpm, advance);

	int dwell = getSparkDwell(rpm);
	chDbgCheck(dwell > 0, "invalid dwell");

	int sparkDelay = timeTillNextRise + sparkAdvance - dwell;
	if (sparkDelay < 0) {
		scheduleSimpleMsg(&log, "Negative spark delay", sparkDelay);
		return;
	}
	scheduleSparkOut(sparkDelay, dwell);
}

static void scheduleFuel(int rpm, CkpEvents ckpSignalType) {
	if (currentCylinderIndex >= NUMBER_OF_CYLINDERS) {
		scheduleSimpleMsg(&log, "what currentCylinderIndex? ", currentCylinderIndex);
		return;
	}

	/**
	 * ID is between 1 and NUMBER_OF_CYLINDERS
	 */
	int cylinderId = FIRING_ORDER[currentCylinderIndex];

//	scheduleSimpleMsg(&log, "will squirt index ", currentCylinderIndex);
	scheduleSimpleMsg(&log, "will squirt id ", cylinderId);

	int injectionPeriod = getFuel(rpm, getMaf()) * TICKS_IN_MS;

	int offset = getInjectionOffset();
	int advanceTime2 = convertAngleToSysticks(getCurrentRpm(), offset);

	int timeTillTDC2 = getWaveLengthByRpm2(getCurrentRpm());

	int delay = 0;//timeTillTDC2 + advanceTime2 - injectionPeriod;
	if (delay < 0) {
		/**
		 * we are here if injection period is so long that in order
		 * to get desired injection advance we should have started in the past
		 * in this case we ignore the desired injection advance and just inject
		 * right away
		 */
		resetLogging(&log);
		append(&log, "msg");
		append(&log, DELIMETER);
		append(&log, "ERROR: negative delay? rpm=");
		appendInt(&log, getCurrentRpm());
		append(&log, " delay=");
		appendInt(&log, delay);
		//		append(&logging, " timeTillTDC2=");
		//		appendInt(&logging, timeTillTDC2);
		//		append(&logging, " advanceTime2= ");
		//		appendInt(&logging, advanceTime2);
		//		append(&logging, " injectionPeriod= ");
		//		appendInt(&logging, injectionPeriod);
		scheduleLogging(&log);

		delay = 0;
	}

	scheduleFuelInjection(delay, injectionPeriod, cylinderId);

}

static void onRunningShaftSignal(int ckpSignalType) {
	int rpm = getCurrentRpm();

	if (rpm > RPM_HARD_LIMIT) {
		scheduleSimpleMsg(&log, "RPM above hard limit ", rpm);
		return;
	}

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

	/**
	 * with -15 spark advance at higher RPMs, 'CKP_PRIMARY_FALL' happens too late - we have to work with 'CKP_PRIMARY_RISE'
	 */
	if (ckpSignalType != CKP_PRIMARY_DOWN)
		return;

	scheduleSpark(rpm, ckpSignalType);

	scheduleFuel(rpm, ckpSignalType);
}

/**
 * This is the main entry point into the primary CKP signal. Both injection and ignition are controlled from this method.
 */
static void onShaftSignal(int ckpSignalType) {
	if (!isControlActive)
		return;

	if (ckpSignalType == CKP_SECONDARY_DOWN) {
		/**
		 * that's because we increment before handing the event, so this '-1' would be processed as 0
		 */
		currentCylinderIndex = -1;
		return;
	}

	if (ckpSignalType == CKP_PRIMARY_DOWN) {
		currentCylinderIndex++;
	}

//	scheduleSimpleMsg(&log, "event ", currentCylinderIndex);

	if (isCranking()) {
		onCrankingShaftSignal(ckpSignalType);
	} else {
		onRunningShaftSignal(ckpSignalType);
	}
}

void initMainLoop() {
	initLogging(&log, "main event handler", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));
	if (!isControlActive)
		printSimpleMsg(&log, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! control disabled",
				0);

	registerCkpListener(&onShaftSignal, "main loop");
}

