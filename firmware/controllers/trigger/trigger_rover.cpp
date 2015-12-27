/*
 * @file trigger_rover.cpp
 *
 * @date Dec 27, 2015
 * todo: ask PhilTheGeek to sign contributor agreement
 */

#include "trigger_rover.h"

void initializeRoverK(TriggerShape *s) {
	s->initialize(FOUR_STROKE_CRANK_SENSOR, false);

	float tooth = 20;

	s->setTriggerSynchronizationGap(2.0);
	s->setThirdTriggerSynchronizationGap(2);
	s->isSynchronizationNeeded = true;

	float base = 0;

	for (int i = 0; i < 2; i++) {
		s->addEvent(base + tooth / 2, T_PRIMARY, TV_RISE);
		s->addEvent(base + tooth, T_PRIMARY, TV_FALL);
		base += tooth;
	}
	base += tooth;
	for (int i = 0; i < 2; i++) {
		s->addEvent(base + tooth / 2, T_PRIMARY, TV_RISE);
		s->addEvent(base + tooth, T_PRIMARY, TV_FALL);
		base += tooth;
	}
	base += tooth;
	for (int i = 0; i < 14; i++) {
		s->addEvent(base + tooth / 2, T_PRIMARY, TV_RISE);
		s->addEvent(base + tooth, T_PRIMARY, TV_FALL);
		base += tooth;
	}
	base += tooth;
	for (int i = 0; i < 3; i++) {
		s->addEvent(base + tooth / 2, T_PRIMARY, TV_RISE);
		s->addEvent(base + tooth, T_PRIMARY, TV_FALL);
		base += tooth;
	}
	base += tooth;
	for (int i = 0; i < 11; i++) {
		s->addEvent(base + tooth / 2, T_PRIMARY, TV_RISE);
		s->addEvent(base + tooth, T_PRIMARY, TV_FALL);
		base += tooth;
	}

}
