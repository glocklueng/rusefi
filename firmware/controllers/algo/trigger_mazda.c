/**
 * @file	trigger_mazda.c
 *
 * @date Feb 18, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "trigger_mazda.h"

void initializeMazdaMiataNbShape(trigger_shape_s *s) {
	triggerShapeInit(s);

	/**
	 * cam sensor is primary, crank sensor is secondary
	 */
	triggerAddEvent(s, 20, T_PRIMARY, TV_LOW);

	triggerAddEvent(s, 66, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 70, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 136, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 140, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 246, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 250, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 316, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 320, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, 340, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 360, T_PRIMARY, TV_LOW);

	triggerAddEvent(s, 380, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 400, T_PRIMARY, TV_LOW);

	triggerAddEvent(s, 426, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 430, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 496, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 500, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 606, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 610, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 676, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 680, T_PRIMARY, TV_LOW);

	triggerAddEvent(s, 720, T_PRIMARY, TV_HIGH);

	s->shaftPositionEventCount = 6 + 16;
}
