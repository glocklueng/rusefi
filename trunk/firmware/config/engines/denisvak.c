/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    denisvak.c
 */

#include "main.h"
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

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	skippedToothPositionEmulatorShape(state);
}

void configureInjection(InjectionConfiguration *injectionConfiguration) {
	injectionConfiguration->fireAtEventIndex[0] = 1;
	injectionConfiguration->fireAtEventIndex[2 * 15] = 2;
	injectionConfiguration->fireAtEventIndex[2 * 30] = 3;
	injectionConfiguration->fireAtEventIndex[2 * 45] = 4;
}

#endif /* EFI_ENGINE_DENISVAK */
