/**
 * @file	custom_engine.cpp
 *
 * @date Jan 18, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef CONFIG_ENGINES_CUSTOM_ENGINE_CPP_
#define CONFIG_ENGINES_CUSTOM_ENGINE_CPP_

#include "custom_engine.h"
#include "honda_accord.h"
#include "allsensors.h"

EXTERN_ENGINE;

void setCustomEngineConfiguration(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->trigger.type = TT_ONE_PLUS_ONE;

	board_configuration_s * boardConfiguration = &engineConfiguration->bc;
	setFrankenso_01_LCD(boardConfiguration);
	setFrankenso0_1_joystick(engineConfiguration);

	/**
	 * Frankenso analog #1 PC2 ADC12 CLT
	 * Frankenso analog #2 PC1 ADC11 IAT
	 * Frankenso analog #3 PA0 ADC0
	 * Frankenso analog #4 PC3 ADC13 WBO / O2
	 * Frankenso analog #5 PA2 ADC2 TPS
	 * Frankenso analog #6 PA1 ADC1
	 * Frankenso analog #7 PA4 ADC4
	 * Frankenso analog #8 PA3 ADC3
	 * Frankenso analog #9 PA7 ADC7
	 * Frankenso analog #10 PA6 ADC6
	 * Frankenso analog #11 PC5 ADC15
	 * Frankenso analog #12 PC4 ADC14 VBatt
	 */
	engineConfiguration->tpsAdcChannel = EFI_ADC_2;
	engineConfiguration->cltAdcChannel = EFI_ADC_12;
	engineConfiguration->iatAdcChannel = EFI_ADC_11;
	engineConfiguration->afr.hwChannel = EFI_ADC_13;

	boardConfiguration->adcHwChannelEnabled[14] = ADC_SLOW;
	engineConfiguration->vbattAdcChannel = EFI_ADC_14;

	setCommonNTCSensor(&engineConfiguration->clt);
	engineConfiguration->clt.bias_resistor = 2700;
	setCommonNTCSensor(&engineConfiguration->iat);
	engineConfiguration->iat.bias_resistor = 2700;


	/**
	 * http://rusefi.com/wiki/index.php?title=Manual:Hardware_Frankenso_board
	 */
	// Frankenso low out #1: PE6
	// Frankenso low out #2: PE5
	// Frankenso low out #3: PD7 Main Relay
	// Frankenso low out #4: PC13 Idle valve solenoid
	// Frankenso low out #5: PE3
	// Frankenso low out #6: PE4 fuel pump relay
	// Frankenso low out #7: PE1 (do not use with discovery!)
	// Frankenso low out #8: PE2 injector #2
	// Frankenso low out #9: PB9 injector #1
	// Frankenso low out #10: PE0 (do not use with discovery!)
	// Frankenso low out #11: PB8 injector #3
	// Frankenso low out #12: PB7 injector #4

	boardConfiguration->fuelPumpPin = GPIOE_4;
	boardConfiguration->mainRelayPin = GPIOD_7;
	boardConfiguration->idleValvePin = GPIOC_13;

	boardConfiguration->fanPin = GPIOE_5;

	boardConfiguration->injectionPins[0] = GPIOB_9; // #1
	boardConfiguration->injectionPins[1] = GPIOE_2; // #2
	boardConfiguration->injectionPins[2] = GPIOB_8; // #3
	boardConfiguration->injectionPins[3] = GPIOB_7; // #4

#if EFI_PWM_TESTER
	boardConfiguration->injectionPins[4] = GPIOC_8; // #5
	boardConfiguration->injectionPins[5] = GPIOD_10; // #6
	boardConfiguration->injectionPins[6] = GPIOD_9;
	boardConfiguration->injectionPins[7] = GPIOD_11;
	boardConfiguration->injectionPins[8] = GPIOD_0;
	boardConfiguration->injectionPins[9] = GPIOB_11;
	boardConfiguration->injectionPins[10] = GPIOC_7;
	boardConfiguration->injectionPins[11] = GPIOE_4;

	/**
	 * We want to initialize all outputs for test
	 */
	engineConfiguration->specs.cylindersCount = 12;

	engineConfiguration->displayMode = DM_NONE;
#else
	boardConfiguration->injectionPins[4] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[5] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[6] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[7] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[8] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[9] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[10] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[11] = GPIO_UNASSIGNED;

	boardConfiguration->ignitionPins[0] = GPIOE_14;
	boardConfiguration->ignitionPins[1] = GPIO_UNASSIGNED; // todo: update this value
	boardConfiguration->ignitionPins[2] = GPIOC_7;
	boardConfiguration->ignitionPins[3] = GPIO_UNASSIGNED; // todo: update this value
#endif

	// todo: 8.2 or 10k?
	engineConfiguration->vbattDividerCoeff = ((float) (10 + 33)) / 10 * 2;

}

#endif /* CONFIG_ENGINES_CUSTOM_ENGINE_CPP_ */
