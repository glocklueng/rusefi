/**
 * @file	mazda_miata.cpp
 *
 * FORD_ESCORT_GT = 14
 * MIATA_1990 = 19
 * MIATA_1994 = 20
 * MIATA_1996 = 21
 *
 * @date Apr 11, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "mazda_miata.h"
#include "engine_math.h"

// setFrankenso_01_LCD
#include "honda_accord.h"

static float miata_maf_fuel_table[16][16] = {
{/*0 engineLoad=1.2*//*0 800.0*/1.53, /*1 1213.0*/0.92, /*2 1626.0*/0.74, /*3 2040.0*/0.69, /*4 2453.0*/0.69, /*5 2866.0*/0.67, /*6 3280.0*/0.67, /*7 3693.0*/0.67, /*8 4106.0*/0.67, /*9 4520.0*/1.02, /*10 4933.0*/0.98, /*11 5346.0*/0.98, /*12 5760.0*/0.92, /*13 6173.0*/0.89, /*14 6586.0*/0.82, /*15 7000.0*/0.87},
{/*1 engineLoad=1.413333*//*0 800.0*/2.98, /*1 1213.0*/2.07, /*2 1626.0*/1.74, /*3 2040.0*/1.55, /*4 2453.0*/1.43, /*5 2866.0*/1.18, /*6 3280.0*/0.0, /*7 3693.0*/0.0, /*8 4106.0*/0.0, /*9 4520.0*/0.0, /*10 4933.0*/0.0, /*11 5346.0*/0.0, /*12 5760.0*/0.0, /*13 6173.0*/0.0, /*14 6586.0*/0.0, /*15 7000.0*/0.0},
{/*2 engineLoad=1.626666*//*0 800.0*/4.9, /*1 1213.0*/3.45, /*2 1626.0*/2.76, /*3 2040.0*/2.35, /*4 2453.0*/2.08, /*5 2866.0*/1.84, /*6 3280.0*/0.0, /*7 3693.0*/0.0, /*8 4106.0*/0.0, /*9 4520.0*/0.0, /*10 4933.0*/0.0, /*11 5346.0*/0.0, /*12 5760.0*/0.0, /*13 6173.0*/0.0, /*14 6586.0*/0.0, /*15 7000.0*/0.0},
{/*3 engineLoad=1.839999*//*0 800.0*/6.94, /*1 1213.0*/4.81, /*2 1626.0*/3.79, /*3 2040.0*/3.14, /*4 2453.0*/2.72, /*5 2866.0*/2.42, /*6 3280.0*/1.93, /*7 3693.0*/1.8, /*8 4106.0*/0.0, /*9 4520.0*/0.0, /*10 4933.0*/0.0, /*11 5346.0*/0.0, /*12 5760.0*/0.0, /*13 6173.0*/0.0, /*14 6586.0*/0.0, /*15 7000.0*/0.0},
{/*4 engineLoad=2.053332*//*0 800.0*/11.94, /*1 1213.0*/6.67, /*2 1626.0*/5.15, /*3 2040.0*/4.23, /*4 2453.0*/3.63, /*5 2866.0*/3.19, /*6 3280.0*/2.83, /*7 3693.0*/2.59, /*8 4106.0*/2.39, /*9 4520.0*/2.24, /*10 4933.0*/0.0, /*11 5346.0*/0.0, /*12 5760.0*/0.0, /*13 6173.0*/0.0, /*14 6586.0*/0.0, /*15 7000.0*/0.0},
{/*5 engineLoad=2.266665*//*0 800.0*/12.63, /*1 1213.0*/10.51, /*2 1626.0*/6.91, /*3 2040.0*/5.63, /*4 2453.0*/4.8, /*5 2866.0*/4.21, /*6 3280.0*/3.75, /*7 3693.0*/3.4, /*8 4106.0*/3.09, /*9 4520.0*/2.87, /*10 4933.0*/2.8, /*11 5346.0*/2.68, /*12 5760.0*/2.52, /*13 6173.0*/2.38, /*14 6586.0*/2.29, /*15 7000.0*/0.0},
{/*6 engineLoad=2.479998*//*0 800.0*/12.11, /*1 1213.0*/12.5, /*2 1626.0*/10.04, /*3 2040.0*/7.24, /*4 2453.0*/6.11, /*5 2866.0*/5.32, /*6 3280.0*/4.73, /*7 3693.0*/4.28, /*8 4106.0*/3.89, /*9 4520.0*/3.61, /*10 4933.0*/3.54, /*11 5346.0*/3.32, /*12 5760.0*/3.13, /*13 6173.0*/2.92, /*14 6586.0*/2.82, /*15 7000.0*/0.0},
{/*7 engineLoad=2.693331*//*0 800.0*/12.09, /*1 1213.0*/12.19, /*2 1626.0*/12.43, /*3 2040.0*/10.69, /*4 2453.0*/7.92, /*5 2866.0*/6.87, /*6 3280.0*/6.09, /*7 3693.0*/5.49, /*8 4106.0*/4.97, /*9 4520.0*/4.59, /*10 4933.0*/4.44, /*11 5346.0*/4.21, /*12 5760.0*/3.97, /*13 6173.0*/3.7, /*14 6586.0*/3.55, /*15 7000.0*/0.0},
{/*8 engineLoad=2.906664*//*0 800.0*/12.09, /*1 1213.0*/12.18, /*2 1626.0*/12.34, /*3 2040.0*/12.48, /*4 2453.0*/11.36, /*5 2866.0*/9.48, /*6 3280.0*/7.68, /*7 3693.0*/6.89, /*8 4106.0*/6.23, /*9 4520.0*/5.76, /*10 4933.0*/5.65, /*11 5346.0*/5.32, /*12 5760.0*/4.97, /*13 6173.0*/4.6, /*14 6586.0*/4.4, /*15 7000.0*/0.0},
{/*9 engineLoad=3.119997*//*0 800.0*/12.08, /*1 1213.0*/12.17, /*2 1626.0*/12.34, /*3 2040.0*/12.41, /*4 2453.0*/12.76, /*5 2866.0*/12.47, /*6 3280.0*/11.02, /*7 3693.0*/9.67, /*8 4106.0*/8.29, /*9 4520.0*/7.23, /*10 4933.0*/7.0, /*11 5346.0*/6.82, /*12 5760.0*/6.44, /*13 6173.0*/6.06, /*14 6586.0*/5.76, /*15 7000.0*/0.0},
{/*10 engineLoad=3.33333*//*0 800.0*/12.08, /*1 1213.0*/12.18, /*2 1626.0*/12.34, /*3 2040.0*/12.43, /*4 2453.0*/12.7, /*5 2866.0*/12.93, /*6 3280.0*/12.78, /*7 3693.0*/12.4, /*8 4106.0*/11.4, /*9 4520.0*/10.16, /*10 4933.0*/9.44, /*11 5346.0*/9.01, /*12 5760.0*/8.36, /*13 6173.0*/7.83, /*14 6586.0*/7.45, /*15 7000.0*/0.0},
{/*11 engineLoad=3.546663*//*0 800.0*/12.09, /*1 1213.0*/12.17, /*2 1626.0*/12.34, /*3 2040.0*/12.43, /*4 2453.0*/12.7, /*5 2866.0*/12.89, /*6 3280.0*/12.72, /*7 3693.0*/12.55, /*8 4106.0*/12.98, /*9 4520.0*/12.96, /*10 4933.0*/12.3, /*11 5346.0*/11.59, /*12 5760.0*/10.9, /*13 6173.0*/10.07, /*14 6586.0*/9.59, /*15 7000.0*/0.0},
{/*12 engineLoad=3.759996*//*0 800.0*/12.08, /*1 1213.0*/12.18, /*2 1626.0*/12.34, /*3 2040.0*/12.43, /*4 2453.0*/12.7, /*5 2866.0*/12.93, /*6 3280.0*/12.72, /*7 3693.0*/12.63, /*8 4106.0*/12.87, /*9 4520.0*/13.56, /*10 4933.0*/14.76, /*11 5346.0*/14.62, /*12 5760.0*/14.14, /*13 6173.0*/13.39, /*14 6586.0*/12.19, /*15 7000.0*/0.0},
{/*13 engineLoad=3.973329*//*0 800.0*/12.09, /*1 1213.0*/12.17, /*2 1626.0*/12.34, /*3 2040.0*/12.43, /*4 2453.0*/12.71, /*5 2866.0*/12.92, /*6 3280.0*/12.74, /*7 3693.0*/12.57, /*8 4106.0*/12.88, /*9 4520.0*/13.82, /*10 4933.0*/15.15, /*11 5346.0*/15.57, /*12 5760.0*/16.22, /*13 6173.0*/16.05, /*14 6586.0*/15.59, /*15 7000.0*/0.0},
{/*14 engineLoad=4.186662*//*0 800.0*/12.08, /*1 1213.0*/12.18, /*2 1626.0*/12.34, /*3 2040.0*/12.4, /*4 2453.0*/12.71, /*5 2866.0*/12.92, /*6 3280.0*/12.71, /*7 3693.0*/12.53, /*8 4106.0*/12.97, /*9 4520.0*/13.55, /*10 4933.0*/14.87, /*11 5346.0*/15.67, /*12 5760.0*/16.16, /*13 6173.0*/16.2, /*14 6586.0*/15.89, /*15 7000.0*/0.0},
{/*15 engineLoad=4.399995*//*0 800.0*/12.08, /*1 1213.0*/12.17, /*2 1626.0*/12.34, /*3 2040.0*/12.43, /*4 2453.0*/12.74, /*5 2866.0*/12.91, /*6 3280.0*/12.71, /*7 3693.0*/12.54, /*8 4106.0*/12.97, /*9 4520.0*/13.53, /*10 4933.0*/14.87, /*11 5346.0*/15.48, /*12 5760.0*/16.1, /*13 6173.0*/16.18, /*14 6586.0*/15.93, /*15 7000.0*/0.0}
};


static void setDefaultCrankingFuel(engine_configuration_s *engineConfiguration) {
	// todo: set cranking parameters method based on injectors and displacement?

	// since CLT is not wired up yet let's just use same value for min and max
	// set_cranking_fuel_max 6 40
	engineConfiguration->crankingSettings.coolantTempMaxC = 37.7; // 6ms at 37.7C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 6;

	// set_cranking_fuel_min 6 -40
	engineConfiguration->crankingSettings.coolantTempMinC = -40; // 6ms at -40C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 6;
}

static void commonMiataNa(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_MAZDA_MIATA_NA;

	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	setFuelLoadBin(engineConfiguration, 1.2, 4.4);
	setFuelRpmBin(engineConfiguration, 800, 7000);

	boardConfiguration->idleSolenoidFrequency = 160;

	engineConfiguration->globalTriggerAngleOffset = 114;

	// Frankenstein: high side #1 is PE8
	// Frankenstein: high side #2 is PE10
	// Frankenstein: high side #3 is PE12
	// Frankenstein: high side #4 is PE14
	// Frankenstein: high side #5 is PC9
	// Frankenstein: high side #6 is PC7

	boardConfiguration->ignitionPins[0] = GPIOE_12; // Frankenstein: high side #3
	boardConfiguration->ignitionPins[1] = GPIOE_14; // Frankenstein: high side #4
	boardConfiguration->ignitionPins[2] = GPIO_NONE;
	boardConfiguration->ignitionPins[3] = GPIO_NONE;
	boardConfiguration->ignitionPinMode = OM_DEFAULT;

	setDefaultCrankingFuel(engineConfiguration);

	boardConfiguration->triggerSimulatorPinModes[0] = OM_OPENDRAIN;
	boardConfiguration->triggerSimulatorPinModes[1] = OM_OPENDRAIN;
}

static void common079721_2351(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {

	engineConfiguration->digitalChartSize = 150;

	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	boardConfiguration->fuelPumpPin = GPIO_NONE; // fuel pump is not controlled by ECU on this engine

	// set_cranking_injection_mode 0
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	// set_injection_mode 2
	engineConfiguration->injectionMode = IM_BATCH;

	// Frankenstein analog input #1: adc1
	// Frankenstein analog input #2: adc3
	// Frankenstein analog input #3: adc13
	// Frankenstein analog input #4: adc11
	// todo: see https://docs.google.com/spreadsheet/ccc?key=0Arl1FeMZcfisdEdGdUlHdWh6cVBoSzFIbkxqa1QtZ3c
	// Frankenstein analog input #5: adc
	// Frankenstein analog input #6: adc
	// Frankenstein analog input #7: adc
	// Frankenstein analog input #8: adc
	// Frankenstein analog input #9: adc
	// Frankenstein analog input #10: adc
	// Frankenstein analog input #11: adc
	// Frankenstein analog input #12: adc
	engineConfiguration->mafAdcChannel = EFI_ADC_1;
	engineConfiguration->tpsAdcChannel = EFI_ADC_3;
	engineConfiguration->cltAdcChannel = EFI_ADC_11;
}

void setMiata1990(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	common079721_2351(engineConfiguration, boardConfiguration);

	commonMiataNa(engineConfiguration, boardConfiguration);


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
	boardConfiguration->injectionPins[2] = GPIO_NONE;
	boardConfiguration->injectionPins[3] = GPIO_NONE;
	boardConfiguration->injectionPins[4] = GPIO_NONE;
	boardConfiguration->injectionPins[5] = GPIO_NONE;
	boardConfiguration->injectionPinMode = OM_DEFAULT;


// todo: idleValvePin
}

void setFordEscortGt(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_FORD_ESCORT_GT;

	common079721_2351(engineConfiguration, boardConfiguration);

	// set_global_trigger_offset_angle 256
	engineConfiguration->globalTriggerAngleOffset = 256;
	// set_ignition_offset 170
	engineConfiguration->ignitionOffset = 170;
	// set_injection_offset 510
	engineConfiguration->injectionOffset = 59;

	setSingleCoilDwell(engineConfiguration);
	engineConfiguration->ignitionMode = IM_ONE_COIL;

	boardConfiguration->triggerSimulatorPinModes[0] = OM_OPENDRAIN;
	boardConfiguration->triggerSimulatorPinModes[1] = OM_OPENDRAIN;

	// Frankenstein: high side #1 is PE8
	// Frankenstein: high side #2 is PE10
	// Frankenstein: high side #3 is PE12
	// Frankenstein: high side #4 is PE14
	// Frankenstein: high side #5 is PC9
	// Frankenstein: high side #6 is PC7

	boardConfiguration->ignitionPins[0] = GPIOE_12; // Frankenstein: high side #3
	boardConfiguration->ignitionPins[1] = GPIO_NONE;
	boardConfiguration->ignitionPins[2] = GPIO_NONE;
	boardConfiguration->ignitionPins[3] = GPIO_NONE;
	boardConfiguration->ignitionPinMode = OM_DEFAULT;

	// set_whole_fuel_map 3
	setWholeFuelMap(engineConfiguration, 3);

	setDefaultCrankingFuel(engineConfiguration);
}

/**
 * Frankenso board
 * set_engine_type 20
 */
void setMiata1994(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	commonMiataNa(engineConfiguration, boardConfiguration);
	engineConfiguration->displacement = 1.839;

	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = miata_maf_fuel_table[k][r];
		}
	}


//	boardConfiguration->triggerSimulatorPins[0] = GPIOD_2; // 2G - YEL/BLU
//	boardConfiguration->triggerSimulatorPins[1] = GPIOB_3; // 2E - WHT - four times
//	boardConfiguration->triggerSimulatorPinModes[0] = OM_OPENDRAIN;
//	boardConfiguration->triggerSimulatorPinModes[1] = OM_OPENDRAIN;
//
//	boardConfiguration->triggerInputPins[0] = GPIO_NONE;
//	boardConfiguration->triggerInputPins[1] = GPIO_NONE;
//
//	boardConfiguration->is_enabled_spi_1 = false;
//	boardConfiguration->is_enabled_spi_2 = false;
//	boardConfiguration->is_enabled_spi_3 = false;

	/**
	 * Outputs
	 */
	// Frankenso low out #:
	// Frankenso low out #:
	// Frankenso low out #:
	// Frankenso low out #:
	// Frankenso low out #5: PE3
	// Frankenso low out #6: PE4
	// Frankenso low out #7: PE1 (do not use with discovery!)
	// Frankenso low out #:
	// Frankenso low out #9: PB9
	// Frankenso low out #10: PE0 (do not use with discovery!)
	// Frankenso low out #11: PB8
	// Frankenso low out #12: PB7


	boardConfiguration->idleValvePin = GPIOB_9;
	boardConfiguration->o2heaterPin = GPIO_NONE;

	boardConfiguration->fuelPumpPin = GPIOE_4;

	boardConfiguration->injectionPins[0] = GPIOE_3;
	boardConfiguration->injectionPins[1] = GPIOE_2;
	boardConfiguration->injectionPins[2] = GPIOB_8;
	boardConfiguration->injectionPins[3] = GPIOB_7;

	boardConfiguration->ignitionPins[0] = GPIOE_12;
	boardConfiguration->ignitionPins[1] = GPIO_NONE;
	boardConfiguration->ignitionPins[2] = GPIO_NONE;
	boardConfiguration->ignitionPins[3] = GPIO_NONE;
	boardConfiguration->ignitionPinMode = OM_DEFAULT;

	setFrankenso_01_LCD(boardConfiguration);

}

/**
 * Tom tomiata, Frankenstein board
 */
void setMiata1996(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	commonMiataNa(engineConfiguration, boardConfiguration);
	engineConfiguration->displacement = 1.839;

	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = miata_maf_fuel_table[k][r];
		}
	}


	engineConfiguration->mafAdcChannel = EFI_ADC_1;
	engineConfiguration->cltAdcChannel = EFI_ADC_3;
	engineConfiguration->tpsAdcChannel = EFI_ADC_13;

	boardConfiguration->ignitionPins[0] = GPIOE_12; // Frankenstein: high side #3
	boardConfiguration->ignitionPins[1] = GPIOE_14; // Frankenstein: high side #4
	boardConfiguration->ignitionPins[2] = GPIO_NONE;
	boardConfiguration->ignitionPins[3] = GPIO_NONE;
	boardConfiguration->ignitionPinMode = OM_DEFAULT;

	// harness is sequential but we have a limited board
	engineConfiguration->injectionMode = IM_BATCH;

	boardConfiguration->injectionPins[0] = GPIOB_9; // Frankenstein: low side - inj #12
	boardConfiguration->injectionPins[1] = GPIOB_8; // Frankenstein: low side - inj #11
	boardConfiguration->injectionPins[2] = GPIO_NONE;
	boardConfiguration->injectionPins[3] = GPIO_NONE;
	boardConfiguration->injectionPins[4] = GPIO_NONE;
	boardConfiguration->injectionPins[5] = GPIO_NONE;
	boardConfiguration->injectionPinMode = OM_DEFAULT;

}

