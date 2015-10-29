/**
 * @file	trigger_mitsubishi.cpp
 *
 * @date Aug 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "trigger_mitsubishi.h"

void configureFordAspireTriggerShape(TriggerShape * s) {
	s->initialize(FOUR_STROKE_CAM_SENSOR, true);
	s->isSynchronizationNeeded = false;

	float x = 121.90;
	float y = 110.86;

	s->addEvent(x + y - 180, T_SECONDARY, TV_HIGH);
	s->addEvent(x, T_SECONDARY, TV_LOW);
	s->addEvent(x + y, T_SECONDARY, TV_HIGH);
	s->addEvent(x + 180, T_SECONDARY, TV_LOW);
	s->addEvent(360, T_PRIMARY, TV_HIGH);

	s->addEvent(x + 180 + y, T_SECONDARY, TV_HIGH);
	s->addEvent(x + 360, T_SECONDARY, TV_LOW);
	s->addEvent(x + 360 + y, T_SECONDARY, TV_HIGH);
	s->addEvent(x + 540, T_SECONDARY, TV_LOW);
	s->addEvent(720, T_PRIMARY, TV_LOW);
}

void initializeMitsubishi4g18(TriggerShape *s) {
	s->initialize(FOUR_STROKE_CAM_SENSOR, true);
	s->useRiseEdge = false;

	s->setTriggerSynchronizationGap(1.6666);

	int secondaryWidth = 70;

	s->addEvent(180.0 - 131 + 5, T_PRIMARY, TV_HIGH);
	s->addEvent(180.0 - secondaryWidth, T_SECONDARY, TV_HIGH);
	s->addEvent(180.0, T_SECONDARY, TV_LOW);
	s->addEvent(180.0 + 49 + 5, T_PRIMARY, TV_LOW);

	s->addEvent(360.0 - secondaryWidth, T_SECONDARY, TV_HIGH);
	s->addEvent(360.0, T_SECONDARY, TV_LOW);

	s->addEvent(540.0 - 131 + 5, T_PRIMARY, TV_HIGH);
	s->addEvent(540.0 - secondaryWidth, T_SECONDARY, TV_HIGH);
	s->addEvent(540.0 - 131 + 5 + 90, T_PRIMARY, TV_LOW);
	s->addEvent(540.0, T_SECONDARY, TV_LOW);

	s->addEvent(720.0 - secondaryWidth, T_SECONDARY, TV_HIGH);
	s->addEvent(720.0, T_SECONDARY, TV_LOW);
}
