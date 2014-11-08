/**
 * @file ec2.h
 *
 * this is a mess because some code is still in C and some is
 * already in C++. trigger structure is C++
 * TODO: rename? merge? Do something with this file
 *
 * @date Apr 26, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef EC2_H_
#define EC2_H_

#include "engine_configuration.h"
#include "event_registry.h"
#include "trigger_structure.h"

class FuelSchedule {
public:
	FuelSchedule();
	void clear();
	ActuatorEventList events;

	void addFuelEvents(trigger_shape_s *s,
			injection_mode_e mode DECLATE_ENGINE_PARAMETER);
	void registerInjectionEvent(trigger_shape_s *s,
			io_pin_e pin, float angle DECLATE_ENGINE_PARAMETER);

	uint8_t hasEvents[PWM_PHASE_MAX_COUNT];

};

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
class engine_configuration2_s {
	// todo: move these fields into Engine class, eliminate this class
public:
	engine_configuration2_s();

	// todo: this should go, too
	engine_configuration_s *engineConfiguration;

	trigger_shape_s triggerShape;

	FuelSchedule crankingInjectionEvents;
	FuelSchedule injectionEvents;

	/**
	 * We are alternating two event lists in order to avoid a potential issue around revolution boundary
	 * when an event is scheduled within the next revolution.
	 */
	IgnitionEventList ignitionEvents[2];
};

void initializeIgnitionActions(float advance, float dwellAngle,
		engine_configuration2_s *engineConfiguration2, IgnitionEventList *list DECLATE_ENGINE_PARAMETER);

void setDefaultNonPersistentConfiguration(engine_configuration2_s *engineConfiguration2);
void printConfiguration(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2);

#endif /* EC2_H_ */
