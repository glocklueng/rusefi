/*
 * idle_thread.c
 *
 *  Created on: May 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "idle_controller.h"
#include "rpm_reporter.h"
#include "rficonsole_logic.h"
#include "datalogging.h"
#include "pwm_generator.h"
#include "wave_math.h"

WORKING_AREA(ivThreadStack, 256);

static PwmWave idleValve;

static IdleValveState idle;
static Logging logging;

static void setIdle(int value) {
	if (value < 1 || value > 99)
		return;
	myfloat v = 0.01 * value;
	idleValve.rights[0] = v;
}

static msg_t ivThread(int param) {
	chRegSetThreadName("IdleValve");

	int currentIdleValve = -1;
	while (TRUE) {
		chThdSleepMilliseconds(200);

		int nowSec = GetCurrentSec();

		int newValue = getIdle(&idle, getCurrentRpm(), nowSec);

		newValue = 100 - newValue; // convert algorithm value into actual PMW value

		if (currentIdleValve != newValue) {
			currentIdleValve = newValue;

			queueSimpleMsg(&logging, "setting idle valve PWM ", newValue);
			setIdle(newValue);
		}
	}
	return -1;
}

static void setTargetIdle(int value) {
	setTargetRpm(&idle, value);
	queueSimpleMsg(&logging, "target idle RPM", value);
}

void startIdleThread() {
	wePlainInit("Idle Valve", &idleValve, IDLE_VALVE_PORT, IDLE_VALVE_PIN, 0, 0, 0.5);
	idleValve.waveLen = freq2wave(200);

	idleInit(&idle);
	queueSimpleMsg(&logging, "initial idle", idle.value);


	addConsoleAction1("target", &setTargetIdle);

	chThdCreateStatic(ivThreadStack, sizeof(ivThreadStack), NORMALPRIO,
			ivThread, NULL );

	addConsoleAction1("idle", &setIdle);
}
