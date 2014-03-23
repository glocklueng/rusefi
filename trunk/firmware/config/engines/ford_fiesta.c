/**
 * @file	ford_fiesta.c
 * @brief	European 1990 Ford Fiesta
 *
 * FORD_FIESTA = 4
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"

#if EFI_SUPPORT_FORD_FIESTA || defined(__DOXYGEN__)

#include "ford_fiesta.h"
#include "engine_configuration.h"
#include "engine_math.h"

void setFordFiestaDefaultEngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;
	// only crankshaft sensor so far
	engineConfiguration->rpmMultiplier = 1;

	engineConfiguration->triggerConfig.totalToothCount = 36;
	engineConfiguration->triggerConfig.skippedToothCount = 1;

	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;
}

void setFordFiestaengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	resetOutputSignals();

	EventHandlerConfiguration *config = &engineConfiguration2->engineEventConfiguration;

	// injector 1 activated at the 1st tooth event while cranking
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), 0);
	// injector 2 activated at the 36th st tooth event while cranking (do not forget - there are 70 events overall, 35 ups and 46 downs
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), 360);

	// injector 1 activated at the 1st tooth event while normal running
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), 0);
	// injector 2 activated at the 36th tooth event while normal running
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), 180);


	initializeIgnitionActions(engineConfiguration, engineConfiguration2);

}

#endif /* EFI_SUPPORT_FORD_FIESTA */
