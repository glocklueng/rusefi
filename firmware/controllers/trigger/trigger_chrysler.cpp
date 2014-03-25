/**
 * @file	trigger_chrysler.cpp
 *
 * @date Mar 24, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "trigger_chrysler.h"

void configureNeonTriggerShape(trigger_shape_s *s) {
	triggerShapeInit(s);

	// voodoo magic - we always need 720 at the end
	int base = 720 - 630;

	triggerAddEvent(s, base + 60 , T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, base + 210, T_PRIMARY, TV_LOW);
	triggerAddEvent(s, base + 420, T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, base + 630, T_PRIMARY, TV_LOW);

	s->shaftPositionEventCount = 4;
}

