/**
 * @file	toothed_wheel_emulator.c
 * @brief	Missing-tooth wheel signal emulator
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR

#include "toothed_wheel_emulator.h"
#include "dist_emulator.h"

static myfloat switchTimes[2 * TOTAL_TEETH_COUNT];
static int pinStates0[2 * TOTAL_TEETH_COUNT];

static trigger_simulator_s s;

void skippedToothPositionEmulatorShape(PwmConfig *state, int totalTeethCount, int skippedCount) {
	triggerSimulatorInit(&s);

	for (int i = 0; i < 2 * totalTeethCount; i++) {
		switchTimes[i] = 1.0 * (i + 1) / (2 * totalTeethCount);
		if (i < 2 * skippedCount) {
			pinStates0[i] = 0;
		} else {
			pinStates0[i] = i % 2;
		}
		print("pinstate %d: %d\r\n", i, pinStates0[i]);
	}

	int *pinStates[1] = { pinStates0 };

	weComplexInit("position sensor", state, 0, 2 * totalTeethCount, switchTimes, 1, pinStates);
}

#endif /* EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR */
