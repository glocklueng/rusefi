/**
 * @file	honda_accord.c
 *
 * @date Jan 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "engine_controller.h"
#include "toothed_wheel_emulator.h"

void setHondaAccordConfiguration(engine_configuration_s *engineConfiguration) {

}

void setHondaAccordConfiguration2(engine_configuration2_s *engineConfiguration2) {


	EventHandlerConfiguration *config = &engineConfiguration2->engineEventConfiguration;

	float x = 10;

	resetEventList(&config->ignitionEvents);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 180);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 360);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_4_OUTPUT), x + 540);


	trigger_shape_s *s = &engineConfiguration2->triggerShape;
	int TOTAL_TEETH_COUNT = 24;
	int SKIPPED_TEETH_COUNT = 2;
	engineConfiguration2->triggerShape.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
	skippedToothTriggerShape(s, TOTAL_TEETH_COUNT, SKIPPED_TEETH_COUNT);
}

