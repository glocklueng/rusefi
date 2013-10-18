/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    denisvak.c
 */

#include "main.h"
#include "print.h"

#if EFI_ENGINE_DENISVAK

float getVRef(void) {
	return 12;
}

float getFuelMs() {
	return 1;
}

void initMainEventListener() {

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

#endif /* EFI_ENGINE_DENISVAK */
