/**
 * @file	dodge_neon.cpp
 *
 * DODGE_NEON_1995 = 2
 *
 * DODGE_NEON_2003 = 23
 *
 * This config overrides some values of the default configuration which is set by setDefaultConfiguration() method
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

// setFrankenso_01_LCD
#include "honda_accord.h"

// http://rusefi.com/forum/viewtopic.php?f=3&t=360&start=40
static float dodge_map_advance_table[16][16] = {
{/*0 engineLoad=1.2*//*0 800.0*/-4.498, /*1 1213.0*/-11.905, /*2 1626.0*/-23.418, /*3 2040.0*/-25.357, /*4 2453.0*/-25.441, /*5 2866.0*/-25.468, /*6 3280.0*/-29.425, /*7 3693.0*/-32.713, /*8 4106.0*/-35.556, /*9 4520.0*/-37.594, /*10 4933.0*/-36.165, /*11 5346.0*/-30.578, /*12 5760.0*/-29.145, /*13 6173.0*/-29.065, /*14 6586.0*/-27.071, /*15 7000.0*/-28.282},
{/*1 engineLoad=1.413333*//*0 800.0*/-4.87, /*1 1213.0*/-12.138, /*2 1626.0*/-23.389, /*3 2040.0*/-25.501, /*4 2453.0*/-25.441, /*5 2866.0*/-25.468, /*6 3280.0*/-29.125, /*7 3693.0*/-33.074, /*8 4106.0*/-34.203, /*9 4520.0*/-37.769, /*10 4933.0*/-35.899, /*11 5346.0*/-30.519, /*12 5760.0*/-28.88, /*13 6173.0*/-28.74, /*14 6586.0*/-27.189, /*15 7000.0*/-27.826},
{/*2 engineLoad=1.626666*//*0 800.0*/-4.817, /*1 1213.0*/-12.262, /*2 1626.0*/-23.925, /*3 2040.0*/-25.501, /*4 2453.0*/-25.5, /*5 2866.0*/-25.468, /*6 3280.0*/-29.364, /*7 3693.0*/-33.489, /*8 4106.0*/-34.839, /*9 4520.0*/-37.545, /*10 4933.0*/-35.875, /*11 5346.0*/-30.353, /*12 5760.0*/-29.052, /*13 6173.0*/-28.37, /*14 6586.0*/-27.072, /*15 7000.0*/-26.828},
{/*3 engineLoad=1.839999*//*0 800.0*/-4.537, /*1 1213.0*/-12.421, /*2 1626.0*/-23.214, /*3 2040.0*/-25.394, /*4 2453.0*/-25.412, /*5 2866.0*/-25.485, /*6 3280.0*/-29.425, /*7 3693.0*/-33.427, /*8 4106.0*/-34.091, /*9 4520.0*/-36.887, /*10 4933.0*/-36.047, /*11 5346.0*/-30.079, /*12 5760.0*/-28.453, /*13 6173.0*/-28.074, /*14 6586.0*/-27.189, /*15 7000.0*/-26.641},
{/*4 engineLoad=2.053332*//*0 800.0*/-4.522, /*1 1213.0*/-11.76, /*2 1626.0*/-23.915, /*3 2040.0*/-25.415, /*4 2453.0*/-25.551, /*5 2866.0*/-25.14, /*6 3280.0*/-29.346, /*7 3693.0*/-32.917, /*8 4106.0*/-34.815, /*9 4520.0*/-37.211, /*10 4933.0*/-35.817, /*11 5346.0*/-29.694, /*12 5760.0*/-28.799, /*13 6173.0*/-27.818, /*14 6586.0*/-28.098, /*15 7000.0*/-27.662},
{/*5 engineLoad=2.266665*//*0 800.0*/-4.678, /*1 1213.0*/-11.912, /*2 1626.0*/-23.486, /*3 2040.0*/-25.379, /*4 2453.0*/-25.551, /*5 2866.0*/-25.527, /*6 3280.0*/-29.856, /*7 3693.0*/-33.511, /*8 4106.0*/-34.786, /*9 4520.0*/-37.963, /*10 4933.0*/-35.917, /*11 5346.0*/-31.073, /*12 5760.0*/-28.361, /*13 6173.0*/-28.468, /*14 6586.0*/-27.188, /*15 7000.0*/-26.729},
{/*6 engineLoad=2.479998*//*0 800.0*/-4.517, /*1 1213.0*/-12.029, /*2 1626.0*/-23.477, /*3 2040.0*/-25.455, /*4 2453.0*/-25.382, /*5 2866.0*/-25.898, /*6 3280.0*/-29.147, /*7 3693.0*/-33.578, /*8 4106.0*/-34.12, /*9 4520.0*/-36.279, /*10 4933.0*/-36.432, /*11 5346.0*/-31.362, /*12 5760.0*/-28.084, /*13 6173.0*/-28.463, /*14 6586.0*/-27.691, /*15 7000.0*/-27.83},
{/*7 engineLoad=2.693331*//*0 800.0*/-4.532, /*1 1213.0*/-12.262, /*2 1626.0*/-23.935, /*3 2040.0*/-25.489, /*4 2453.0*/-25.595, /*5 2866.0*/-26.816, /*6 3280.0*/-30.251, /*7 3693.0*/-33.533, /*8 4106.0*/-34.794, /*9 4520.0*/-37.882, /*10 4933.0*/-36.104, /*11 5346.0*/-30.079, /*12 5760.0*/-28.545, /*13 6173.0*/-29.304, /*14 6586.0*/-27.07, /*15 7000.0*/-28.324},
{/*8 engineLoad=2.906664*//*0 800.0*/-4.532, /*1 1213.0*/-12.036, /*2 1626.0*/-23.418, /*3 2040.0*/-25.513, /*4 2453.0*/-25.382, /*5 2866.0*/-25.357, /*6 3280.0*/-29.934, /*7 3693.0*/-33.467, /*8 4106.0*/-34.748, /*9 4520.0*/-37.288, /*10 4933.0*/-36.38, /*11 5346.0*/-29.516, /*12 5760.0*/-28.799, /*13 6173.0*/-28.407, /*14 6586.0*/-26.951, /*15 7000.0*/-28.203},
{/*9 engineLoad=3.119997*//*0 800.0*/-4.532, /*1 1213.0*/-11.978, /*2 1626.0*/-23.73, /*3 2040.0*/-25.501, /*4 2453.0*/-25.624, /*5 2866.0*/-26.328, /*6 3280.0*/-30.015, /*7 3693.0*/-33.187, /*8 4106.0*/-34.881, /*9 4520.0*/-38.044, /*10 4933.0*/-35.81, /*11 5346.0*/-29.843, /*12 5760.0*/-29.306, /*13 6173.0*/-28.997, /*14 6586.0*/-27.109, /*15 7000.0*/-29.339},
{/*10 engineLoad=3.33333*//*0 800.0*/-4.527, /*1 1213.0*/-12.131, /*2 1626.0*/-23.486, /*3 2040.0*/-25.43, /*4 2453.0*/-25.551, /*5 2866.0*/-26.276, /*6 3280.0*/-29.639, /*7 3693.0*/-33.005, /*8 4106.0*/-34.253, /*9 4520.0*/-37.788, /*10 4933.0*/-36.077, /*11 5346.0*/-30.188, /*12 5760.0*/-29.087, /*13 6173.0*/-28.481, /*14 6586.0*/-27.348, /*15 7000.0*/-27.777},
{/*11 engineLoad=3.546663*//*0 800.0*/-4.889, /*1 1213.0*/-12.175, /*2 1626.0*/-23.271, /*3 2040.0*/-25.357, /*4 2453.0*/-25.551, /*5 2866.0*/-25.485, /*6 3280.0*/-29.899, /*7 3693.0*/-32.802, /*8 4106.0*/-34.786, /*9 4520.0*/-38.686, /*10 4933.0*/-35.722, /*11 5346.0*/-31.347, /*12 5760.0*/-28.891, /*13 6173.0*/-28.333, /*14 6586.0*/-27.149, /*15 7000.0*/-27.236},
{/*12 engineLoad=3.759996*//*0 800.0*/-4.537, /*1 1213.0*/-12.073, /*2 1626.0*/-23.896, /*3 2040.0*/-25.525, /*4 2453.0*/-25.595, /*5 2866.0*/-25.451, /*6 3280.0*/-30.428, /*7 3693.0*/-33.714, /*8 4106.0*/-34.08, /*9 4520.0*/-37.526, /*10 4933.0*/-35.817, /*11 5346.0*/-30.733, /*12 5760.0*/-28.718, /*13 6173.0*/-28.518, /*14 6586.0*/-27.518, /*15 7000.0*/-26.561},
{/*13 engineLoad=3.973329*//*0 800.0*/-4.86, /*1 1213.0*/-11.883, /*2 1626.0*/-23.428, /*3 2040.0*/-25.489, /*4 2453.0*/-25.536, /*5 2866.0*/-25.613, /*6 3280.0*/-29.895, /*7 3693.0*/-33.648, /*8 4106.0*/-34.758, /*9 4520.0*/-37.988, /*10 4933.0*/-36.047, /*11 5346.0*/-30.225, /*12 5760.0*/-28.698, /*13 6173.0*/-28.487, /*14 6586.0*/-27.111, /*15 7000.0*/-27.708},
{/*14 engineLoad=4.186662*//*0 800.0*/-4.683, /*1 1213.0*/-11.898, /*2 1626.0*/-23.506, /*3 2040.0*/-25.562, /*4 2453.0*/-25.61, /*5 2866.0*/-25.519, /*6 3280.0*/-29.95, /*7 3693.0*/-33.582, /*8 4106.0*/-34.548, /*9 4520.0*/-36.201, /*10 4933.0*/-35.788, /*11 5346.0*/-30.053, /*12 5760.0*/-28.292, /*13 6173.0*/-28.259, /*14 6586.0*/-27.269, /*15 7000.0*/-26.863},
{/*15 engineLoad=4.3999950000000005*//*0 800.0*/-4.85, /*1 1213.0*/-12.24, /*2 1626.0*/-24.091, /*3 2040.0*/-25.394, /*4 2453.0*/-25.323, /*5 2866.0*/-25.544, /*6 3280.0*/-29.915, /*7 3693.0*/-33.104, /*8 4106.0*/-36.016, /*9 4520.0*/-37.933, /*10 4933.0*/-36.254, /*11 5346.0*/-29.712, /*12 5760.0*/-28.651, /*13 6173.0*/-28.045, /*14 6586.0*/-27.228, /*15 7000.0*/-27.784}
};


void setDodgeNeon1995EngineConfiguration(engine_configuration_s *engineConfiguration,
		board_configuration_s *boardConfiguration) {

	engineConfiguration->triggerConfig.triggerType = TT_DODGE_NEON_1995;

	engineConfiguration->algorithm = LM_ALPHA_N;

	engineConfiguration->hasIatSensor = false;

	// set_rpm_hard_limit 4000
	engineConfiguration->rpmHardLimit = 4000; // yes, 4k. let's play it safe for now
	// set_cranking_rpm 550
	engineConfiguration->crankingSettings.crankingRpm = 550;

	// set_cranking_fuel 5
	engineConfiguration->crankingSettings.baseCrankingFuel = 5;

	/**
	 * that's 1995 config
	 */

	// set_whole_fuel_map 9
	setWholeFuelMap(engineConfiguration, 9);
	setWholeTimingTable(engineConfiguration, 12);

	// set_cranking_injection_mode 0
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	// set_injection_mode 1
	engineConfiguration->injectionMode = IM_SEQUENTIAL;

	// set_ignition_mode 2
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	// set_firing_order 2
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	// set_global_trigger_offset_angle 497
	engineConfiguration->globalTriggerAngleOffset = 497;
	// set_ignition_offset 350
	engineConfiguration->ignitionOffset = 350;
	 // set_injection_offset 510
	engineConfiguration->injectionOffset = 510;

	/**
	 * that's 1995 config
	 */

	// set_cranking_charge_angle 70
	engineConfiguration->crankingChargeAngle = 70;
	// set_cranking_timing_angle 0
	engineConfiguration->crankingTimingAngle = 0;

	// Frankenstein: low side - out #1: PC14
	// Frankenstein: low side - out #2: PC15
	// Frankenstein: low side - out #3: PE6
	// Frankenstein: low side - out #4: PC13
	// Frankenstein: low side - out #5: PE4
	// Frankenstein: low side - out #6: PE5
	// Frankenstein: low side - out #7: PE2
	// Frankenstein: low side - out #8: PE3
	// Frankenstein: low side - out #9: PE0
	// Frankenstein: low side - out #10: PE1
	// Frankenstein: low side - out #11: PB8
	// Frankenstein: low side - out #12: PB9

	boardConfiguration->injectionPins[0] = GPIOB_9; // Frankenstein: low side - out #12
	boardConfiguration->injectionPins[1] = GPIOB_8; // Frankenstein: low side - out #11
	boardConfiguration->injectionPins[2] = GPIOE_3; // Frankenstein: low side - out #8
	boardConfiguration->injectionPins[3] = GPIOE_5; // Frankenstein: low side - out #6

	boardConfiguration->fuelPumpPin = GPIOC_13; // Frankenstein: low side - out #4
	boardConfiguration->fuelPumpPinMode = OM_DEFAULT;

	// set_injection_pin_mode 0
	boardConfiguration->injectionPinMode = OM_DEFAULT;

	// Frankenstein: high side #1: PE8
	// Frankenstein: high side #2: PE10

	boardConfiguration->ignitionPins[0] = GPIOE_8; // Frankenstein: high side #1
	boardConfiguration->ignitionPins[1] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[2] = GPIOE_10; // // Frankenstein: high side #2

	// set_ignition_pin_mode 0
	boardConfiguration->ignitionPinMode = OM_DEFAULT;

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, 0, 32500, 30, 7550, 100, 700);
	engineConfiguration->cltThermistorConf.bias_resistor = 2700;

	engineConfiguration->analogChartFrequency = 7;
}

void setDodgeNeonNGCEngineConfiguration(engine_configuration_s *engineConfiguration,
		board_configuration_s *boardConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_DODGE_NEON_2003;
	setFrankenso_01_LCD(boardConfiguration);

	// set_global_trigger_offset_angle 46
	engineConfiguration->globalTriggerAngleOffset = 46;
	engineConfiguration->needSecondTriggerInput = false;

	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->injectionMode = IM_SEQUENTIAL;
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->displacement = 1.996;
	engineConfiguration->cylindersCount = 4;

	/**
	 * that's NGC config
	 *
	 * set_cranking_fuel 5
	 */
	engineConfiguration->crankingSettings.baseCrankingFuel = 5;

	/**
	 * 77C
	 * 1200 rpm
	 * fuel 3
	 *
	 * 88C
	 * fuel 2.8
	 *
	 * set_whole_fuel_map 12
	 */
	setWholeFuelMap(engineConfiguration, 12);
	setWholeTimingTable(engineConfiguration, 12);

	// set_cranking_charge_angle 70
	engineConfiguration->crankingChargeAngle = 70;
	// set_cranking_timing_angle 710
	engineConfiguration->crankingTimingAngle = 710;


	/**
	 * bosch 4G1139
	 * http://forum.2gn.org/viewtopic.php?t=21657
	 */
	engineConfiguration->injectorFlow = 199;

	// I want to start with a simple Alpha-N
	engineConfiguration->algorithm = LM_ALPHA_N;
	setFuelLoadBin(engineConfiguration, 0, 100);
	setTimingLoadBin(engineConfiguration, 0, 100);

	boardConfiguration->malfunctionIndicatorPin = GPIO_UNASSIGNED;

	/**
	 * PA4 Wideband O2 Sensor
	 */
	engineConfiguration->afrSensor.afrAdcChannel = EFI_ADC_4;

	commonFrankensoAnalogInputs(engineConfiguration);
	engineConfiguration->vbattDividerCoeff = ((float) (8.2 + 33)) / 8.2 * 2;

	// Frankenso low out #1: PE6
	// Frankenso low out #2: PE5
	// Frankenso low out #3: PD7 coolant fan relay
	// Frankenso low out #4: PC13 idle valve solenoid
	// Frankenso low out #5: PE3 fuel pump relay
	// Frankenso low out #6: PE4
	// Frankenso low out #7: PE1 (do not use with discovery!)
	// Frankenso low out #8: PE2 injector #3
	// Frankenso low out #9: PB9 injector #2
	// Frankenso low out #10: PE0 (do not use with discovery!)
	// Frankenso low out #11: PB8 injector #1
	// Frankenso low out #12: PB7 injector #4

	boardConfiguration->fanPin = GPIOD_7;

	boardConfiguration->injectionPins[0] = GPIOB_8;
	boardConfiguration->injectionPins[1] = GPIOB_9;
	boardConfiguration->injectionPins[2] = GPIOE_2;
	boardConfiguration->injectionPins[3] = GPIOB_7;

	boardConfiguration->ignitionPins[0] = GPIOC_9;
	boardConfiguration->ignitionPins[1] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[2] = GPIOE_8;
	boardConfiguration->ignitionPins[3] = GPIO_UNASSIGNED;

	boardConfiguration->idleValvePin = GPIOC_13;
	boardConfiguration->idleSolenoidFrequency = 300;

	boardConfiguration->fuelPumpPin = GPIOE_3;
	boardConfiguration->fuelPumpPinMode = OM_DEFAULT;

	boardConfiguration->gps_rx_pin = GPIO_UNASSIGNED;
	boardConfiguration->gps_tx_pin = GPIO_UNASSIGNED;

	boardConfiguration->triggerInputPins[0] = GPIOA_5;
	boardConfiguration->triggerInputPins[1] = GPIOC_6;

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, 0, 32500, 30, 7550, 100, 700);
	engineConfiguration->cltThermistorConf.bias_resistor = 10000;

	setThermistorConfiguration(&engineConfiguration->iatThermistorConf, 0, 32500, 30, 7550, 100, 700);
	engineConfiguration->iatThermistorConf.bias_resistor = 10000;

	/**
	 * MAP D17/W5
	 */
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_0;

	boardConfiguration->adcHwChannelEnabled[0] = ADC_FAST; // ADC0 - PA0 - MAP
	boardConfiguration->adcHwChannelEnabled[1] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[4] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[11] = ADC_SLOW; // IAT
	boardConfiguration->adcHwChannelEnabled[12] = ADC_SLOW; // CLT
	boardConfiguration->adcHwChannelEnabled[13] = ADC_SLOW; // AFR
	boardConfiguration->adcHwChannelEnabled[14] = ADC_SLOW; // VBatt
	boardConfiguration->adcHwChannelEnabled[15] = ADC_SLOW; // TPS



	/**
	 * TPS
	 */
	engineConfiguration->tpsAdcChannel = EFI_ADC_15;
	engineConfiguration->tpsMin = 125; // convert 12to10 bit (ADC/4)
	engineConfiguration->tpsMax = 625; // convert 12to10 bit (ADC/4)

	/**
	 * IAT D15/W7
	 */
	engineConfiguration->iatAdcChannel = EFI_ADC_11;

	/**
	 * CLT D13/W9
	 */
	engineConfiguration->cltAdcChannel = EFI_ADC_12;
}

#endif /* EFI_SUPPORT_DODGE_NEON */

