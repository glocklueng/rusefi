/**
 * @file	PwmTester.cpp
 * This is a tool to measure rusEfi PWM generation quality
 *
 * @date Apr 29, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "PwmTester.h"
#include "trigger_structure.h"
#include "pwm_generator_logic.h"
#include "engine_configuration.h"
#include "pwm_generator.h"

static Logging logger;

static float _switchTimes[2];

// todo: extract helper for simple PWM?
static int pinStates[2];
static single_wave_s wave(pinStates);
static single_wave_s sr[1] = { wave };

static PwmConfig pwmTest[4] = { PwmConfig(_switchTimes, sr),
		PwmConfig(_switchTimes, sr),
		PwmConfig(_switchTimes, sr),
		PwmConfig(_switchTimes, sr)};

extern board_configuration_s *boardConfiguration;

static void startPwmTest(int freq) {
	scheduleMsg(&logger, "running pwm test @%d", freq);

	// currently this is PB9 by default
	startSimplePwm(&pwmTest[0], "tester", boardConfiguration->injectionPins[0],
			INJECTOR_1_OUTPUT, 0.5, freq / 1000, FALSE);
	// currently this is PB8 by default
	startSimplePwm(&pwmTest[1], "tester", boardConfiguration->injectionPins[1],
			INJECTOR_2_OUTPUT, 0.5, freq / 100, FALSE);
	// currently this is PE3 by default
	startSimplePwm(&pwmTest[2], "tester", boardConfiguration->injectionPins[2],
			INJECTOR_3_OUTPUT, 0.5, freq, FALSE);
	// currently this is PE5 by default
	startSimplePwm(&pwmTest[3], "tester", boardConfiguration->injectionPins[3],
			INJECTOR_4_OUTPUT, 0.5, freq / 33.3, FALSE);
}

void initPwmTester(void) {
	initLogging(&logger, "pwm test");
	addConsoleActionI("pwmtest", startPwmTest);
// un-comment this to start pwm test on start up 	startPwmTest(1000);
}
