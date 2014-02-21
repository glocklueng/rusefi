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
	 * cam sensor is primary
	 */
	triggerAddEvent(s, 20, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 340, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 360, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 380, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 400, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 720, T_PRIMARY, TV_HIGH);

}
