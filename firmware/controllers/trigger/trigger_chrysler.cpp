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

	triggerAddEvent(s, 5 , T_SECONDARY, TV_HIGH); // 1
	triggerAddEvent(s, 8, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 11, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 14, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, 18, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 21, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 24, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 29, T_SECONDARY, TV_LOW);


	triggerAddEvent(s, 40, T_SECONDARY, TV_HIGH); // 2
	triggerAddEvent(s, 45, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 50, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 55, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, 60, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 65, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 70, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 75, T_SECONDARY, TV_LOW);


	triggerAddEvent(s, 79, T_SECONDARY, TV_HIGH); // 3
	triggerAddEvent(s, 83, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, 87, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 91, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, 95, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, 99, T_SECONDARY, TV_LOW);
	triggerAddEvent(s,103, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s,106, T_SECONDARY, TV_LOW);


	triggerAddEvent(s,109, T_SECONDARY, TV_HIGH); // 4
	triggerAddEvent(s,112, T_SECONDARY, TV_LOW);
	triggerAddEvent(s,115, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s,119, T_SECONDARY, TV_LOW);

	triggerAddEvent(s,123, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s,127, T_SECONDARY, TV_LOW);
	triggerAddEvent(s,131, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s,135, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, base + 60 , T_PRIMARY, TV_HIGH);
	triggerAddEvent(s, base + 210, T_PRIMARY, TV_LOW); // width = 150
	triggerAddEvent(s, base + 420, T_PRIMARY, TV_HIGH); // width = 210
	triggerAddEvent(s, base + 630, T_PRIMARY, TV_LOW); // width = 210

	s->shaftPositionEventCount = 4 + 16 + 8 + 8;
}

