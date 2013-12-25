/**
 * @file	toothed_wheel_emulator.c
 * @brief	Missing-tooth wheel signal emulator
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#include "toothed_wheel_emulator.h"
#include "dist_emulator.h"

void skippedToothTriggerShape(trigger_shape_s *s, int totalTeethCount, int skippedCount) {
	triggerShapeInit(s);

	float toothWidth = 0.5;

	for (int i = 0; i < totalTeethCount - skippedCount - 1; i++) {
		float angleDown = 720.0 / totalTeethCount * (i + toothWidth);
		float angleUp = 720.0 / totalTeethCount * (i + 1);
		triggerAddEvent(s, angleDown, T_PRIMARY, 1);
		triggerAddEvent(s, angleUp, T_PRIMARY, 0);
	}

	float angleDown = 720.0 / totalTeethCount * (totalTeethCount - skippedCount + toothWidth);
	triggerAddEvent(s, angleDown, T_PRIMARY, 1);
	triggerAddEvent(s, 720, T_PRIMARY, 0);
}
