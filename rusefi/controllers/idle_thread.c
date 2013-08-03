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
#include "idle_thread.h"
#include "pin_repository.h"

#define IDLE_AIR_CONTROL_VALVE_PWM_FREQUENCY 200

static WORKING_AREA(ivThreadStack, 512);

static int isIdleActive = TRUE;
//static int isIdleActive = FALSE;

/**
 * here we keep the value we got from IDLE SWITCH input
 */
static volatile int idleSwitchState;

static PwmWave idleValve;

static IdleValveState idle;
static Logging log;

int getIdleSwitch() {
	return idleSwitchState;
}

void idleDebug(char *msg, int value) {
	printSimpleMsg(&log, msg, value);
	scheduleLogging(&log);
}

static void setIdle(int value) {
	// todoL change parameter type, maybe change parameter validation
	if (value < 1 || value > 999)
		return;
	scheduleSimpleMsg(&log, "setting idle valve PWM ", value);
	myfloat v = 0.001 * value;
	idleValve.switchTimes[0] = 1 - v;
}

static msg_t ivThread(int param) {
	chRegSetThreadName("IdleValve");

	int currentIdleValve = -1;
	while (TRUE) {
		chThdSleepMilliseconds(100);

		idleSwitchState = palReadPad(IDLE_SWITCH_PORT, IDLE_SWITCH_PIN);

		if (!isIdleActive)
			continue;

		int nowSec = GetCurrentSec();

		int newValue = getIdle(&idle, getCurrentRpm(), nowSec);

		// todo: invert wave & eliminate this inversion?
		newValue = 1000 - newValue; // convert algorithm value into actual PMW value

		if (currentIdleValve != newValue) {
			currentIdleValve = newValue;

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
		printSimpleMsg(&log,
				"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! idle control disabled", 0);

	addConsoleAction1("target", &setTargetIdle);

	chThdCreateStatic(ivThreadStack, sizeof(ivThreadStack), NORMALPRIO, ivThread, NULL);

	mySetPadMode("idle switch", IDLE_SWITCH_PORT, IDLE_SWITCH_PIN, PAL_MODE_INPUT);

	addConsoleAction1("idle", &setIdle);
}
