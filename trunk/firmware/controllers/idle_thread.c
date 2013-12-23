/**
 * @file    idle_thread.c
 * @brief   Idle Air Control valve thread.
 *
 * 			This thread looks at current RPM and decides if it should increase or decrease IAC duty cycle
 *
 *
 * @date May 23, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "idle_controller.h"
#include "rpm_calculator.h"
#include "rficonsole_logic.h"
#include "datalogging.h"
#include "pwm_generator.h"
#include "wave_math.h"
#include "idle_thread.h"
#include "pin_repository.h"
#include "pinout.h"

#define IDLE_AIR_CONTROL_VALVE_PWM_FREQUENCY 200

static WORKING_AREA(ivThreadStack, UTILITY_THREAD_STACK_SIZE);

static int isIdleActive = EFI_IDLE_CONTROL;

/**
 * here we keep the value we got from IDLE SWITCH input
 */
static volatile int idleSwitchState;

static PwmConfig idleValve;

static IdleValveState idle;
static Logging logger;

int getIdleSwitch() {
	return idleSwitchState;
}

void idleDebug(char *msg, int value) {
	printSimpleMsg(&logger, msg, value);
	scheduleLogging(&logger);
}

static void setIdle(int value) {
	// todoL change parameter type, maybe change parameter validation
	if (value < 1 || value > 999)
		return;
	scheduleSimpleMsg(&logger, "setting idle valve PWM ", value);
	myfloat v = 0.001 * value;
	idleValve.multiWave.switchTimes[0] = 1 - v;
}

static msg_t ivThread(int param) {
	chRegSetThreadName("IdleValve");

	int currentIdleValve = -1;
	while (TRUE) {
		chThdSleepMilliseconds(100);

		idleSwitchState = palReadPad(IDLE_SWITCH_PORT, IDLE_SWITCH_PIN);

		if (!isIdleActive)
			continue;

		int nowSec = chTimeNowSeconds();

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
	scheduleSimpleMsg(&logger, "target idle RPM", value);
}

void startIdleThread() {
	initLogging(&logger, "Idle Valve Control");

	wePlainInit("Idle Valve", &idleValve, IDLE_VALVE_PORT, IDLE_VALVE_PIN, 0, 0.5, IDLE_AIR_CONTROL_VALVE_PWM_FREQUENCY);

	idleInit(&idle);
	scheduleSimpleMsg(&logger, "initial idle", idle.value);
	if (!isIdleActive)
		printSimpleMsg(&logger,
				"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! idle control disabled", 0);

	addConsoleActionI("target", &setTargetIdle);

	chThdCreateStatic(ivThreadStack, sizeof(ivThreadStack), NORMALPRIO, (tfunc_t)ivThread, NULL);

	mySetPadMode("idle switch", IDLE_SWITCH_PORT, IDLE_SWITCH_PIN, PAL_MODE_INPUT);

	addConsoleActionI("idle", &setIdle);
}
