/**
 * @file	PwmTester.cpp
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

static float _switchTimes[2];

// todo: extract helper for simple PWM?
static int pinStates[2];
static single_wave_s wave(pinStates);
static single_wave_s sr[1] = { wave };

static PwmConfig pwmTest(_switchTimes, sr);

extern board_configuration_s *boardConfiguration;

void initPwmTester(void) {
	startSimplePwm(&pwmTest, "tester", boardConfiguration->injectionPins[0], INJECTOR_1_OUTPUT, 0.5, 100

	);

}
