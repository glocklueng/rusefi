/**
 * @file	mazda_626.cpp
 * MAZDA_626
 * set_engine_type 28
 *
 * @date Jan 16, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "mazda_626.h"
#include "engine_math.h"
#include "honda_accord.h"

void setMazda626EngineConfiguration(engine_configuration_s *engineConfiguration) {
	board_configuration_s *boardConfiguration = &engineConfiguration->bc;
	engineConfiguration->trigger.type = TT_MAZDA_DOHC_1_4;

	setFrankenso_01_LCD(boardConfiguration);
	setFrankenso0_1_joystick(engineConfiguration);

	setSingleCoilDwell(engineConfiguration);
	engineConfiguration->ignitionMode = IM_ONE_COIL;

	/**
	 * I-O mapping is a copy of Custom engine type
	 */

	/**
	 * Frankenso analog #1 PC2 ADC12
	 * Frankenso analog #2 PC1 ADC11
	 * Frankenso analog #3
	 * Frankenso analog #4 PC3 ADC13
	 * Frankenso analog #5
	 * Frankenso analog #6
	 * Frankenso analog #7 PA4 ADC4
	 * Frankenso analog #8
	 * Frankenso analog #9
	 * Frankenso analog #10 PA6 ADC6
	 * Frankenso analog #11 PC5 ADC15
	 * Frankenso analog #12 VBatt
	 */


	/**
	 * http://rusefi.com/wiki/index.php?title=Manual:Hardware_Frankenso_board
	 */
	// Frankenso low out #1: PE6
	// Frankenso low out #2: PE5
	// Frankenso low out #3: PD7 Main Relay
	// Frankenso low out #4: PC13 Idle valve solenoid
	// Frankenso low out #5: PE3
	// Frankenso low out #6: PE4
	// Frankenso low out #7: PE1 (do not use with discovery!)
	// Frankenso low out #8: PE2 injector #2
	// Frankenso low out #9: PB9 injector #1
	// Frankenso low out #10: PE0 (do not use with discovery!)
	// Frankenso low out #11: PB8 injector #3
	// Frankenso low out #12: PB7 injector #4

	boardConfiguration->mainRelayPin = GPIOD_7;
	boardConfiguration->idleValvePin = GPIOC_13;

	boardConfiguration->fanPin = GPIOE_5;

	boardConfiguration->injectionPins[0] = GPIOB_9; // #1
	boardConfiguration->injectionPins[1] = GPIOE_2; // #2
	boardConfiguration->injectionPins[2] = GPIOB_8; // #3
	boardConfiguration->injectionPins[3] = GPIOB_7; // #4

	boardConfiguration->ignitionPins[0] = GPIOC_7;

}
