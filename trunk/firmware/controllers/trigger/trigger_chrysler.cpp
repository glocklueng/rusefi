/**
 * @file	trigger_chrysler.cpp
 *
 * @date Mar 24, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "trigger_chrysler.h"

void configureNeonTriggerShape(trigger_shape_s *s) {
	triggerShapeInit(s);

	triggerAddEvent(s, 60, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 210, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, 420, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, 630, T_PRIMARY, TV_LOW);
	// voodoo magic - we always need 720 at the end
	triggerAddEvent(s, 720, T_PRIMARY, TV_LOW);

	s->shaftPositionEventCount = 4;
}

