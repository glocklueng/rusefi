/**
 * @file	dodge_neon.c
 *
 * DODGE_NEON_1995 = 2
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"

#if EFI_SUPPORT_DODGE_NEON || defined(__DOXYGEN__)

#include "dodge_neon.h"
#include "engine_configuration.h"
#include "thermistors.h"
#include "engine_math.h"

void setDodgeNeonEngineConfiguration(engine_configuration_s *engineConfiguration,
		board_configuration_s *boardConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_DODGE_NEON;

	// set_rpm_hard_limit 400
	engineConfiguration->rpmHardLimit = 4000; // yes, 4k. let's play it safe for now
	// set_cranking_rpm 550
	engineConfiguration->crankingSettings.crankingRpm = 550;

	// since CLT is not ready let's just use same value for min and max
	// set_cranking_fuel_max 10 40
	engineConfiguration->crankingSettings.coolantTempMaxC = 37.7; // 5ms at 37.7C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 10;

	// set_cranking_fuel_min 10 -40
	engineConfiguration->crankingSettings.coolantTempMinC = -40; // 26ms at -40C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 10;

	engineConfiguration->triggerConfig.syncRatioFrom = 0.72 * 0.8;
	engineConfiguration->triggerConfig.syncRatioTo = 0.72 * 1.3;

	engineConfiguration->triggerConfig.isSynchronizationNeeded = TRUE;
	engineConfiguration->triggerConfig.useRiseEdge = FALSE;
	engineConfiguration->needSecondTriggerInput = FALSE;


	// set_cranking_injection_mode 0
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	// set_injection_mode 1
	engineConfiguration->injectionMode = IM_SEQUENTIAL;

	// set_ignition_mode 2
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	// set_firing_order 2
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	// set_global_trigger_offset_angle 510
	engineConfiguration->globalTriggerAngleOffset = 510;
	// set_ignition_offset 557
	engineConfiguration->ignitionOffset = -163;
	 // set_injection_offset 510
	engineConfiguration->injectionOffset = 510;

	// Frankenstein: low side - inj #1: PC14
	// Frankenstein: low side - inj #2: PC15
	// Frankenstein: low side - inj #3: PE6
	// Frankenstein: low side - inj #4: PC13
	// Frankenstein: low side - inj #5: PE4
	// Frankenstein: low side - inj #6: PE5
	// Frankenstein: low side - inj #7: PE2
	// Frankenstein: low side - inj #8: PE3
	// Frankenstein: low side - inj #9: PE0
	// Frankenstein: low side - inj #10: PE1
	// Frankenstein: low side - inj #11: PB8
	// Frankenstein: low side - inj #12: PB9

	boardConfiguration->injectionPins[0] = GPIOB_9; // Frankenstein: low side - inj #12
	boardConfiguration->injectionPins[1] = GPIOB_8; // Frankenstein: low side - inj #11
	boardConfiguration->injectionPins[2] = GPIOE_3; // Frankenstein: low side - inj #8
	boardConfiguration->injectionPins[3] = GPIOE_5; // Frankenstein: low side - inj #6

	boardConfiguration->fuelPumpPin = GPIOC_13; // Frankenstein: low side - inj #4
	boardConfiguration->fuelPumpPinMode = OM_DEFAULT;

	// set_injection_pin_mode 0
	boardConfiguration->injectionPinMode = OM_DEFAULT;

	// Frankenstein: high side #1: PE8
	// Frankenstein: high side #2: PE10

	boardConfiguration->ignitionPins[0] = GPIOE_8; // Frankenstein: high side #1
	boardConfiguration->ignitionPins[1] = GPIO_NONE;
	boardConfiguration->ignitionPins[2] = GPIOE_10; // // Frankenstein: high side #2

	// set_ignition_pin_mode 1
	boardConfiguration->ignitionPinMode = OM_INVERTED;

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, 0, 32500, 30, 7550, 100, 700);
	engineConfiguration->cltThermistorConf.bias_resistor = 2700;

	engineConfiguration->analogChartFrequency = 7;
}

void setDodgeNeonengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
}

#endif /* EFI_SUPPORT_DODGE_NEON */

