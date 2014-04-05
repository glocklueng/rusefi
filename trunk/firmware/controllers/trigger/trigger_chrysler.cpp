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
	int base = 720 - 560;

//	triggerAddEvent(s, 5 , T_SECONDARY, TV_HIGH); // 1
//	triggerAddEvent(s, 8, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, 11, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 14, T_SECONDARY, TV_LOW);
//
//	triggerAddEvent(s, 18, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 21, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, 24, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 29, T_SECONDARY, TV_LOW);
//
//
//	triggerAddEvent(s, 40, T_SECONDARY, TV_HIGH); // 2
//	triggerAddEvent(s, 45, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, 50, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 55, T_SECONDARY, TV_LOW);
//
//	triggerAddEvent(s, 60, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 65, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, 70, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 75, T_SECONDARY, TV_LOW);
//
//
//	triggerAddEvent(s, 79, T_SECONDARY, TV_HIGH); // 3
//	triggerAddEvent(s, 83, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, 87, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 91, T_SECONDARY, TV_LOW);
//
//	triggerAddEvent(s, 95, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, 99, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s,103, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s,106, T_SECONDARY, TV_LOW);
//
//
//	triggerAddEvent(s,109, T_SECONDARY, TV_HIGH); // 4
//	triggerAddEvent(s,112, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s,115, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s,119, T_SECONDARY, TV_LOW);
//
//	triggerAddEvent(s,131, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s,135, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, base + 0, T_PRIMARY, TV_LOW);

	triggerAddEvent(s, base + 20, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 60, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, base + 75, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 79, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, base + 101, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 106, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, base + 130, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 135, T_SECONDARY, TV_LOW);

	triggerAddEvent(s, base + 200, T_PRIMARY, TV_HIGH); // width = 150

	triggerAddEvent(s, base + 236, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 239, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, base + 250, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 255, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, base + 277, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 282, T_SECONDARY, TV_LOW);
	triggerAddEvent(s, base + 305, T_SECONDARY, TV_HIGH);
	triggerAddEvent(s, base + 310, T_SECONDARY, TV_LOW);

//	triggerAddEvent(s, base + 374, T_SECONDARY, TV_HIGH);

	triggerAddEvent(s, base + 395, T_PRIMARY, TV_LOW); // width =

//	triggerAddEvent(s, base + 418, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, base + 436, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, base + 441, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, base + 463, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, base + 448, T_SECONDARY, TV_LOW);
//	triggerAddEvent(s, base + 492, T_SECONDARY, TV_HIGH);
//	triggerAddEvent(s, base + 497, T_SECONDARY, TV_LOW);


	triggerAddEvent(s, base + 560, T_PRIMARY, TV_HIGH); // width =

	s->shaftPositionEventCount = 4 + 8 + 8;
}

