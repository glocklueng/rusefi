/**
 * @file	trigger_chrysler.cpp
 *
 * @date Mar 24, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "trigger_chrysler.h"

void configureNeon2003TriggerShape(TriggerShape *s) {
	s->reset(FOUR_STROKE_CAM_SENSOR, false);

	// voodoo magic - we always need 720 at the end
	int base = 10;
	float b = 0;
	s->useRiseEdge = true;

	s->gapBothDirections = true;

	// are these non-default values really needed here now that the gap is finally precise?
	s->setTriggerSynchronizationGap2(0.5 * CHRYSLER_NGC_GAP, 1.5 * CHRYSLER_NGC_GAP);

	/*
	s->addEvent(base + 26, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 62, T_PRIMARY, TV_LOW);

	s->addEvent(base + 98, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 134, T_PRIMARY, TV_LOW);

	s->addEvent(base + 180, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 314, T_PRIMARY, TV_LOW);

	s->addEvent(base + 350, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 386, T_PRIMARY, TV_LOW);

	s->addEvent(base + 422, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 458, T_PRIMARY, TV_LOW);

	s->addEvent(base + 494, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 530, T_PRIMARY, TV_LOW);

	s->addEvent(base + 674, T_PRIMARY, TV_HIGH);
	s->addEvent(base + 710, T_PRIMARY, TV_LOW);
	 *
	 */

	s->addEvent(143.0712499, T_PRIMARY, TV_HIGH);
	s->addEvent(182.684791, T_PRIMARY, TV_LOW);

	s->addEvent(215.424166, T_PRIMARY, TV_HIGH);
	s->addEvent(256.247395, T_PRIMARY, TV_LOW);

	s->addEvent(288.659999, T_PRIMARY, TV_HIGH);
	s->addEvent(326.778229, T_PRIMARY, TV_LOW);

	s->addEvent(361.522083, T_PRIMARY, TV_HIGH);
	s->addEvent(508.960416, T_PRIMARY, TV_LOW);

	s->addEvent(545.635, T_PRIMARY, TV_HIGH);
	s->addEvent(582.98864, T_PRIMARY, TV_LOW);

	s->addEvent(617.22989, T_PRIMARY, TV_HIGH);
	s->addEvent(653.38625, T_PRIMARY, TV_LOW);

	s->addEvent(684.1080, T_PRIMARY, TV_HIGH);
	s->addEvent(720, T_PRIMARY, TV_LOW);
}

void configureNeon1995TriggerShape(TriggerShape *s) {
	s->reset(FOUR_STROKE_CAM_SENSOR, true);

	s->setTriggerSynchronizationGap(0.72);

	s->useRiseEdge = false;

	// voodoo magic - we always need 720 at the end
	int base = 720 - 560;

	s->initialState[T_PRIMARY] = 1;

	s->addEvent(base - 720 + 600, T_SECONDARY, TV_HIGH);
	s->addEvent(base - 720 + 604, T_SECONDARY, TV_LOW);
	s->addEvent(base - 720 + 616, T_SECONDARY, TV_HIGH);
	s->addEvent(base - 720 + 620, T_SECONDARY, TV_LOW);
	s->addEvent(base - 720 + 643, T_SECONDARY, TV_HIGH);
	s->addEvent(base - 720 + 648, T_SECONDARY, TV_LOW);
	s->addEvent(base - 720 + 671, T_SECONDARY, TV_HIGH);
	s->addEvent(base - 720 + 676, T_SECONDARY, TV_LOW);

	s->addEvent(base + 0, T_PRIMARY, TV_LOW);

	s->addEvent(base + 20, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 60, T_SECONDARY, TV_LOW);
	s->addEvent(base + 75, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 79, T_SECONDARY, TV_LOW);
	s->addEvent(base + 101, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 106, T_SECONDARY, TV_LOW);
	s->addEvent(base + 130, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 135, T_SECONDARY, TV_LOW);

	s->addEvent(base + 200, T_PRIMARY, TV_HIGH); // width = 150

	s->addEvent(base + 236, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 239, T_SECONDARY, TV_LOW);
	s->addEvent(base + 250, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 255, T_SECONDARY, TV_LOW);
	s->addEvent(base + 277, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 282, T_SECONDARY, TV_LOW);
	s->addEvent(base + 305, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 310, T_SECONDARY, TV_LOW);

	s->addEvent(base + 374, T_SECONDARY, TV_HIGH);

	s->addEvent(base + 395, T_PRIMARY, TV_LOW); // width =

	s->addEvent(base + 418, T_SECONDARY, TV_LOW);
	s->addEvent(base + 436, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 441, T_SECONDARY, TV_LOW);
	s->addEvent(base + 463, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 468, T_SECONDARY, TV_LOW);
	s->addEvent(base + 492, T_SECONDARY, TV_HIGH);
	s->addEvent(base + 497, T_SECONDARY, TV_LOW);

	s->addEvent(base + 560, T_PRIMARY, TV_HIGH); // width =
}
