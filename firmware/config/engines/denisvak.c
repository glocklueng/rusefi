/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    denisvak.c
 */

#include "main.h"
#include "print.h"
#include "engine_controller.h"
#include "denisvak.h"
#include "adc_inputs.h"
#include "fuel_map.h"

#if EFI_ENGINE_DENISVAK

float getVRef(void) {
	return 12;
}

myfloat getMap(void) {
	// PA6 adc input
	int adc0 = getAdcValue(ADC_LOGIC_MAP);
	float volts = adcToVolts(adc0);
	return volts;
//	return 3;
}

float getFuelMs(int rpm) {
	if (isCranking()) {
		return 5;
	} else {
		return 1.8;//getFuel(rpm, getMap());
	}
}

static myfloat switchTimes[2 * TOTAL_TEETH_COUNT];
static int pinStates0[2 * TOTAL_TEETH_COUNT];

void confgiureShaftPositionEmulatorShape(PwmConfig *state) {

	for (int i = 0; i < 2 * TOTAL_TEETH_COUNT; i++) {
		switchTimes[i] = 1.0 * (i + 1) / (2 * TOTAL_TEETH_COUNT);
		if (i < 4) {
			pinStates0[i] = 0;
		} else {
			pinStates0[i] = i % 2;
		}
		print("pinstate %d: %d\r\n", i, pinStates0[i]);
	}

	print("last %d\r\n", pinStates0[119]);
	print("last %d\r\n", pinStates0[119] == 1);

	int *pinStates[1] = { pinStates0 };

	weComplexInit("position sensor", state, 0, 2 * TOTAL_TEETH_COUNT, switchTimes, 1, pinStates);
}

void configureInjection(InjectionConfiguration *injectionConfiguration) {
	injectionConfiguration->fireAtEventIndex[0] = 1;
	injectionConfiguration->fireAtEventIndex[2 * 15] = 2;
	injectionConfiguration->fireAtEventIndex[2 * 30] = 3;
	injectionConfiguration->fireAtEventIndex[2 * 45] = 4;
}

#endif /* EFI_ENGINE_DENISVAK */
