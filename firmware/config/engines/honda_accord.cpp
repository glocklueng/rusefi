/**
 * @file	honda_accord.cpp
 *
 * 1993 Honda Prelude 1993
 * http://rusefi.com/wiki/index.php?title=Vehicle:Honda_Prelude_1993
 * http://rusefi.com/forum/viewtopic.php?f=3&t=887
 *
 * 1995 Honda Accord EX
 * http://rusefi.com/wiki/index.php?title=Vehicle:Honda_Accord_1995
 * http://rusefi.com/forum/viewtopic.php?f=3&t=621
 *
 * set_engine_type 6
 * set_engine_type 17
 *
 * @date Jan 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "trigger_decoder.h"
#include "thermistors.h"
#include "honda_accord.h"
#include "engine_math.h"
#include "settings.h"

void setFrankenso_01_LCD(board_configuration_s *boardConfiguration) {
	boardConfiguration->HD44780_rs = GPIOE_7;
	boardConfiguration->HD44780_e = GPIOE_9;
	boardConfiguration->HD44780_db4 = GPIOE_11;
	boardConfiguration->HD44780_db5 = GPIOE_13;
	boardConfiguration->HD44780_db6 = GPIOE_15;
	boardConfiguration->HD44780_db7 = GPIOB_10;
}

EXTERN_ENGINE;

static void setHondaAccordConfigurationCommon(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->map.sensor.type = MT_DENSO183;
	boardConfiguration->isFastAdcEnabled = true;

	engineConfiguration->ignitionMode = IM_ONE_COIL;
	engineConfiguration->injectionMode = IM_BATCH;

	engineConfiguration->idleMode = IM_MANUAL;

	engineConfiguration->HD44780height = 4;

	engineConfiguration->specs.cylindersCount = 4;
	engineConfiguration->specs.displacement = 2.156;

	// Keihin 06164-P0A-A00
	engineConfiguration->injector.flow = 248;

//	engineConfiguration->algorithm = LM_SPEED_DENSITY;
	// I want to start with a simple Alpha-N
	setAlgorithm(LM_ALPHA_N PASS_ENGINE_PARAMETER);
	setFuelLoadBin(0, 100 PASS_ENGINE_PARAMETER);

	/**
	 * 18K Ohm @ -20C
	 * 2.1K Ohm @ 24C
	 * 100 Ohm @ 120C
	 */
	setCommonNTCSensor(&engineConfiguration->clt);
	engineConfiguration->clt.config.bias_resistor = 1500; // same as OEM ECU

	setCommonNTCSensor(&engineConfiguration->iat);
	engineConfiguration->iat.config.bias_resistor = 1500; // same as OEM ECU

	// set_cranking_charge_angle 35
	engineConfiguration->crankingChargeAngle = 70;
	// set_cranking_timing_angle 0
	engineConfiguration->crankingTimingAngle = -45;

	// set_global_trigger_offset_angle 34
	engineConfiguration->globalTriggerAngleOffset = 34;

	// set_rpm_hard_limit 4000
	engineConfiguration->rpmHardLimit = 4000; // yes, 4k. let's play it safe for now
	// set_cranking_rpm 2000
	engineConfiguration->cranking.rpm = 500;


	// set_ignition_offset 350
//	engineConfiguration->ignitionOffset = 350;
	 // set_injection_offset 510
//	engineConfiguration->injectionOffset = 510;


	/**
	 * ADC inputs:
	 *
	 * Inp1/ADC12 PC2: CLT
	 * Inp2/ADC11 PC1: AIT/IAT
	 * Inp3/ADC0 PA0: MAP
	 * Inp4/ADC13 PC3: AFR green wire
	 * Inp6/ADC1 PA1: TPS
	 * Inp12/ADC14 PC4: VBatt
	 */

	/**
	 * wideband O2 Sensor
	 */
	engineConfiguration->afr.hwChannel = EFI_ADC_13;

	/**
	 * VBatt
	 */
	engineConfiguration->vbattAdcChannel = EFI_ADC_14;
	engineConfiguration->vbattDividerCoeff = ((float) (10 + 39)) / 10 * 2;

	//	todo engineConfiguration->afr.hwChannel = 14;


	/**
	 * MAP D17/W5 blue wire
	 */
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_0;
	/**
	 * IAT D15/W7 green wire
	 */
	engineConfiguration->iat.adcChannel = EFI_ADC_11;
	/**
	 * CLT D13/W9 yellow wire
	 */
	engineConfiguration->clt.adcChannel = EFI_ADC_12;
	/**
	 * TPS D11/W11 blue wire
	 */
	engineConfiguration->tpsAdcChannel = EFI_ADC_1;


	/**
	 * Outputs
	 */
	// Frankenso low out #1: PE6
	// Frankenso low out #2: PE5
	// Frankenso low out #3: PD7
	// Frankenso low out #4: PC13
	// Frankenso low out #5: PE3 Fuel Relay
	// Frankenso low out #6: PE4 radiator fan - blue wire
	// Frankenso low out #7: PD3 idle air valve solenoid - green wire
	// Frankenso low out #8: PE2 MIL - white wire
	// Frankenso low out #9: PB9 Injector #2
	// Frankenso low out #10: PD5 Injector #3
	// Frankenso low out #11: PB8 injector #1
	// Frankenso low out #12: PB7 injector #4
	boardConfiguration->fuelPumpPin = GPIOE_3;
	boardConfiguration->fuelPumpPinMode = OM_DEFAULT;
	boardConfiguration->malfunctionIndicatorPin = GPIOE_2;
	boardConfiguration->malfunctionIndicatorPinMode = OM_DEFAULT;
	boardConfiguration->fanPin = GPIOE_4; // blue wire

	boardConfiguration->idle.solenoidPin = GPIOD_3; // green wire

	boardConfiguration->injectionPins[0] = GPIOB_8;
	boardConfiguration->injectionPins[1] = GPIOB_9;
	boardConfiguration->injectionPins[2] = GPIOD_5;
	boardConfiguration->injectionPins[3] = GPIOB_7;

	boardConfiguration->ignitionPins[0] = GPIOE_14; // white wire
	boardConfiguration->ignitionPins[1] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[2] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[3] = GPIO_UNASSIGNED;


	setFrankenso_01_LCD(boardConfiguration);
	setFrankenso0_1_joystick(engineConfiguration);

	boardConfiguration->idle.solenoidFrequency = 500;
}

void setHondaAccordConfigurationTwoWires(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->engineType = HONDA_ACCORD_CD_TWO_WIRES;
	engineConfiguration->trigger.type = TT_HONDA_ACCORD_CD_TWO_WIRES;
	setHondaAccordConfigurationCommon(PASS_ENGINE_PARAMETER_F);
}

void setHondaAccordConfigurationThreeWires(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->engineType = HONDA_ACCORD_CD;
	engineConfiguration->trigger.type = TT_HONDA_ACCORD_CD;
	setHondaAccordConfigurationCommon(PASS_ENGINE_PARAMETER_F);
}

void setHondaAccordConfigurationDip(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->engineType = HONDA_ACCORD_CD_DIP;
	engineConfiguration->trigger.type = TT_HONDA_ACCORD_CD_DIP;
	setHondaAccordConfigurationCommon(PASS_ENGINE_PARAMETER_F);
}
