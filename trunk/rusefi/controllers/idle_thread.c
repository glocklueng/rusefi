/*
 *  Created on: May 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    idle_thread.c
 * @brief   Idle Air Control valve thread.
 *
 * 			This thread looks at current RPM and decides if it should increase or decrease IAC duty cycle
 */

#include "main.h"
#include "idle_controller.h"
#include "rpm_reporter.h"
#include "rficonsole_logic.h"
#include "datalogging.h"
#include "pwm_generator.h"
#include "wave_math.h"

#define IDLE_AIR_CONTROL_VALVE_PWM_FREQUENCY 200

WORKING_AREA(ivThreadStack, 256);

//static int isIdleActive = TRUE;
static int isIdleActive = FALSE;

static PwmWave idleValve;

static IdleValveState idle;
static Logging log;

static void setIdle(int value) {
	// todoL change parameter type, maybe change parameter validation
	if (value < 1 || value > 99)
		return;
	myfloat v = 0.01 * value;
	idleValve.switchTimes[0] = v;
}

static msg_t ivThread(int param) {
	chRegSetThreadName("IdleValve");

	int currentIdleValve = -1;
	while (TRUE) {
		chThdSleepMilliseconds(200);
		if (!isIdleActive)
			continue;

		int nowSec = GetCurrentSec();

		int newValue = getIdle(&idle, getCurrentRpm(), nowSec);

		// todo: invert wave & eliminate this inversion?
		newValue = 100 - newValue; // convert algorithm value into actual PMW value

		if (currentIdleValve != newValue) {
			currentIdleValve = newValue;

			scheduleSimpleMsg(&log, "setting idle valve PWM ", newValue);
			setIdle(newValue);
		}
	}
	return -1;
}

static void setTargetIdle(int value) {
	setTargetRpm(&idle, value);
	scheduleSimpleMsg(&log, "target idle RPM", value);
}

void startIdleThread() {
	initLogging(&log, "Idle Valve Control", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	wePlainInit("Idle Valve", &idleValve, IDLE_VALVE_PORT, IDLE_VALVE_PIN, 0, 0.5);
	idleValve.period = frequency2period(IDLE_AIR_CONTROL_VALVE_PWM_FREQUENCY);

	idleInit(&idle);
	scheduleSimpleMsg(&log, "initial idle", idle.value);
	if (!isIdleActive)
		printSimpleMsg(&log, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! idle control disabled", 0);

	addConsoleAction1("target", &setTargetIdle);

	chThdCreateStatic(ivThreadStack, sizeof(ivThreadStack), NORMALPRIO, ivThread, NULL);

	addConsoleAction1("idle", &setIdle);
}
