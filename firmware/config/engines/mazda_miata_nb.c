/**
 * @file	mazda_miata_nb.c
 *
 * MAZDA_MIATA_NB = 9
 *
 * @date Feb 18, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "mazda_miata_nb.h"

void setMazdaMiataNbEngineConfiguration(engine_configuration_s *engineConfiguration) {
	// set_rpm_hard_limit 3000
	engineConfiguration->rpmHardLimit = 3000; // yes, 3k. let's play it safe for now


	engineConfiguration->triggerConfig.triggerType = TT_MAZDA_MIATA_NB;
	engineConfiguration->triggerConfig.isSynchronizationNeeded = TRUE;

	engineConfiguration->triggerConfig.syncRatioFrom = 0.11 * 0.7;
	engineConfiguration->triggerConfig.syncRatioTo = 0.11 * 1.3;
	engineConfiguration->triggerConfig.useRiseEdge = FALSE;
	engineConfiguration->globalTriggerAngleOffset = 320;

	// set_cranking_injection_mode 0
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	// set_injection_mode 1
	engineConfiguration->injectionMode = IM_SEQUENTIAL;
	// set_ignition_mode 2
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	// set_firing_order 2
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	engineConfiguration->cltThermistorConf.bias_resistor = 2700;
	engineConfiguration->iatThermistorConf.bias_resistor = 2700;

//	boardConfiguration->fuelPumpPin = GPIOC_13;

// 10 deg before TDC is default timing
}

void setMazdaMiataNb_configuration2_s(engine_configuration_s *engineConfiguration,
		engine_configuration2_s *engineConfiguration2) {
}

