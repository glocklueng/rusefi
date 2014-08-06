/**
 * @file	mitsubishi.cpp
 *
 * MITSU_4G93 16
 *
 * @date Aug 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "mitsubishi.h"
#include "thermistors.h"

void setMitsubishiConfiguration(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->engineType = MITSU_4G93;

	engineConfiguration->triggerConfig.triggerType = TT_MITSU;

	engineConfiguration->cylindersCount = 4;
	engineConfiguration->displacement = 1.800;

	engineConfiguration->ignitionMode = IM_INDIVIDUAL_COILS;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	// set_global_trigger_offset_angle 671
	engineConfiguration->globalTriggerAngleOffset = 671;

	// set_cranking_rpm 550
	engineConfiguration->crankingSettings.crankingRpm = 550;
	// set_cranking_charge_angle 70
	engineConfiguration->crankingChargeAngle = 70;
	// set_cranking_timing_angle 715
	engineConfiguration->crankingTimingAngle = 715;

	// set_whole_fuel_map 3
	setWholeFuelMap(engineConfiguration, 3);

	// since CLT is not wired up yet let's just use same value for min and max
	// set_cranking_fuel_max 6 40
	engineConfiguration->crankingSettings.coolantTempMaxC = 37.7; // 6ms at 37.7C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 6;

	// set_cranking_fuel_min 6 -40
	engineConfiguration->crankingSettings.coolantTempMinC = -40; // 6ms at -40C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 6;


	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, -20, 18000, 23.8889, 2100, 48.8889, 1000);
	engineConfiguration->cltThermistorConf.bias_resistor = 2700;

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


	// Frankenstein: high side #1: PE8
	// Frankenstein: high side #2: PE10

	boardConfiguration->ignitionPins[0] = GPIOE_8; // Frankenstein: high side #1
	boardConfiguration->ignitionPins[1] = GPIO_NONE;
	boardConfiguration->ignitionPins[2] = GPIOE_10; // // Frankenstein: high side #2

}


