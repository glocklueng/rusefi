/**
 * @file	citroenBerlingoTU3JP.cpp
 *
 * CITROEN_TU3JP: engine_type 15
 * Board pin out for Frankenstein
 *
 * This config overrides some values of the default configuration which is set by setDefaultConfiguration() method
 *
 *
 * @date Apr 15, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "engine_math.h"
#include "thermistors.h"
#include "citroenBerlingoTU3JP.h"

static const fuel_table_t tps_fuel_table = {
{/*0  engineLoad=0.00*/   /*0 800.0*/4.00,  /*1 1213.0*/4.00,  /*2 1626.0*/4.00,  /*3 2040.0*/4.00,  /*4 2453.0*/4.00,  /*5 2866.0*/4.00,  /*6 3280.0*/4.00,  /*7 3693.0*/4.00,  /*8 4106.0*/4.00,  /*9 4520.0*/4.00,  /*10 4933.0*/4.00,  /*11 5346.0*/4.00,  /*12 5760.0*/4.00,  /*13 6173.0*/4.00,  /*14 6586.0*/4.00,  /*15 7000.0*/4.00},
{/*1  engineLoad=6.66*/   /*0 800.0*/5.07,  /*1 1213.0*/5.07,  /*2 1626.0*/5.07,  /*3 2040.0*/5.07,  /*4 2453.0*/5.07,  /*5 2866.0*/5.07,  /*6 3280.0*/5.07,  /*7 3693.0*/5.07,  /*8 4106.0*/5.07,  /*9 4520.0*/5.07,  /*10 4933.0*/5.07,  /*11 5346.0*/5.07,  /*12 5760.0*/5.07,  /*13 6173.0*/5.07,  /*14 6586.0*/5.07,  /*15 7000.0*/5.07},
{/*2  engineLoad=13.33*/  /*0 800.0*/6.13,  /*1 1213.0*/6.13,  /*2 1626.0*/6.13,  /*3 2040.0*/6.13,  /*4 2453.0*/6.13,  /*5 2866.0*/6.13,  /*6 3280.0*/6.13,  /*7 3693.0*/6.13,  /*8 4106.0*/6.13,  /*9 4520.0*/6.13,  /*10 4933.0*/6.13,  /*11 5346.0*/6.13,  /*12 5760.0*/6.13,  /*13 6173.0*/6.13,  /*14 6586.0*/6.13,  /*15 7000.0*/6.13},
{/*3  engineLoad=20.00*/  /*0 800.0*/7.20,  /*1 1213.0*/7.20,  /*2 1626.0*/7.20,  /*3 2040.0*/7.20,  /*4 2453.0*/7.20,  /*5 2866.0*/7.20,  /*6 3280.0*/7.20,  /*7 3693.0*/7.20,  /*8 4106.0*/7.20,  /*9 4520.0*/7.20,  /*10 4933.0*/7.20,  /*11 5346.0*/7.20,  /*12 5760.0*/7.20,  /*13 6173.0*/7.20,  /*14 6586.0*/7.20,  /*15 7000.0*/7.20},
{/*4  engineLoad=26.66*/  /*0 800.0*/8.27,  /*1 1213.0*/8.27,  /*2 1626.0*/8.27,  /*3 2040.0*/8.27,  /*4 2453.0*/8.27,  /*5 2866.0*/8.27,  /*6 3280.0*/8.27,  /*7 3693.0*/8.27,  /*8 4106.0*/8.27,  /*9 4520.0*/8.27,  /*10 4933.0*/8.27,  /*11 5346.0*/8.27,  /*12 5760.0*/8.27,  /*13 6173.0*/8.27,  /*14 6586.0*/8.27,  /*15 7000.0*/8.27},
{/*5  engineLoad=33.33*/  /*0 800.0*/9.33,  /*1 1213.0*/9.33,  /*2 1626.0*/9.33,  /*3 2040.0*/9.33,  /*4 2453.0*/9.33,  /*5 2866.0*/9.33,  /*6 3280.0*/9.33,  /*7 3693.0*/9.33,  /*8 4106.0*/9.33,  /*9 4520.0*/9.33,  /*10 4933.0*/9.33,  /*11 5346.0*/9.33,  /*12 5760.0*/9.33,  /*13 6173.0*/9.33,  /*14 6586.0*/9.33,  /*15 7000.0*/9.33},
{/*6  engineLoad=40.00*/  /*0 800.0*/10.40, /*1 1213.0*/10.40, /*2 1626.0*/10.40, /*3 2040.0*/10.40, /*4 2453.0*/10.40, /*5 2866.0*/10.40, /*6 3280.0*/10.40, /*7 3693.0*/10.40, /*8 4106.0*/10.40, /*9 4520.0*/10.40, /*10 4933.0*/10.40, /*11 5346.0*/10.40, /*12 5760.0*/10.40, /*13 6173.0*/10.40, /*14 6586.0*/10.40, /*15 7000.0*/10.40},
{/*7  engineLoad=46.66*/  /*0 800.0*/11.47, /*1 1213.0*/11.47, /*2 1626.0*/11.47, /*3 2040.0*/11.47, /*4 2453.0*/11.47, /*5 2866.0*/11.47, /*6 3280.0*/11.47, /*7 3693.0*/11.47, /*8 4106.0*/11.47, /*9 4520.0*/11.47, /*10 4933.0*/11.47, /*11 5346.0*/11.47, /*12 5760.0*/11.47, /*13 6173.0*/11.47, /*14 6586.0*/11.47, /*15 7000.0*/11.47},
{/*8  engineLoad=53.33*/  /*0 800.0*/12.53, /*1 1213.0*/12.53, /*2 1626.0*/12.53, /*3 2040.0*/12.53, /*4 2453.0*/12.53, /*5 2866.0*/12.53, /*6 3280.0*/12.53, /*7 3693.0*/12.53, /*8 4106.0*/12.53, /*9 4520.0*/12.53, /*10 4933.0*/12.53, /*11 5346.0*/12.53, /*12 5760.0*/12.53, /*13 6173.0*/12.53, /*14 6586.0*/12.53, /*15 7000.0*/12.53},
{/*9  engineLoad=60.00*/  /*0 800.0*/12.60, /*1 1213.0*/13.60, /*2 1626.0*/13.60, /*3 2040.0*/13.60, /*4 2453.0*/13.60, /*5 2866.0*/13.60, /*6 3280.0*/13.60, /*7 3693.0*/13.60, /*8 4106.0*/13.60, /*9 4520.0*/13.60, /*10 4933.0*/13.60, /*11 5346.0*/13.60, /*12 5760.0*/13.60, /*13 6173.0*/13.60, /*14 6586.0*/13.60, /*15 7000.0*/13.60},
{/*10 engineLoad=66.66*/  /*0 800.0*/14.67, /*1 1213.0*/14.67, /*2 1626.0*/14.67, /*3 2040.0*/14.67, /*4 2453.0*/14.67, /*5 2866.0*/14.67, /*6 3280.0*/14.67, /*7 3693.0*/14.67, /*8 4106.0*/14.67, /*9 4520.0*/14.67, /*10 4933.0*/14.67, /*11 5346.0*/14.67, /*12 5760.0*/14.67, /*13 6173.0*/14.67, /*14 6586.0*/14.67, /*15 7000.0*/14.67},
{/*11 engineLoad=73.33*/  /*0 800.0*/15.73, /*1 1213.0*/15.73, /*2 1626.0*/15.73, /*3 2040.0*/15.73, /*4 2453.0*/15.73, /*5 2866.0*/15.73, /*6 3280.0*/15.73, /*7 3693.0*/15.73, /*8 4106.0*/15.73, /*9 4520.0*/15.73, /*10 4933.0*/15.73, /*11 5346.0*/15.73, /*12 5760.0*/15.73, /*13 6173.0*/15.73, /*14 6586.0*/15.73, /*15 7000.0*/15.73},
{/*12 engineLoad=80.00*/  /*0 800.0*/16.80, /*1 1213.0*/16.80, /*2 1626.0*/16.80, /*3 2040.0*/16.80, /*4 2453.0*/16.80, /*5 2866.0*/16.80, /*6 3280.0*/16.80, /*7 3693.0*/16.80, /*8 4106.0*/16.80, /*9 4520.0*/16.80, /*10 4933.0*/16.80, /*11 5346.0*/16.80, /*12 5760.0*/16.80, /*13 6173.0*/16.80, /*14 6586.0*/16.80, /*15 7000.0*/16.80},
{/*13 engineLoad=86.66*/  /*0 800.0*/17.87, /*1 1213.0*/17.87, /*2 1626.0*/17.87, /*3 2040.0*/17.87, /*4 2453.0*/17.87, /*5 2866.0*/17.87, /*6 3280.0*/17.87, /*7 3693.0*/17.87, /*8 4106.0*/17.87, /*9 4520.0*/17.87, /*10 4933.0*/17.87, /*11 5346.0*/17.87, /*12 5760.0*/17.87, /*13 6173.0*/17.87, /*14 6586.0*/17.87, /*15 7000.0*/17.87},
{/*14 engineLoad=93.33*/  /*0 800.0*/18.93, /*1 1213.0*/18.93, /*2 1626.0*/18.93, /*3 2040.0*/18.93, /*4 2453.0*/18.93, /*5 2866.0*/18.93, /*6 3280.0*/18.93, /*7 3693.0*/18.93, /*8 4106.0*/18.93, /*9 4520.0*/18.93, /*10 4933.0*/18.93, /*11 5346.0*/18.93, /*12 5760.0*/18.93, /*13 6173.0*/18.93, /*14 6586.0*/18.93, /*15 7000.0*/18.93},
{/*15 engineLoad=100.00*/ /*0 800.0*/20.00, /*1 1213.0*/20.00, /*2 1626.0*/20.00, /*3 2040.0*/20.00, /*4 2453.0*/20.00, /*5 2866.0*/20.00, /*6 3280.0*/20.00, /*7 3693.0*/20.00, /*8 4106.0*/20.00, /*9 4520.0*/20.00, /*10 4933.0*/20.00, /*11 5346.0*/20.00, /*12 5760.0*/20.00, /*13 6173.0*/20.00, /*14 6586.0*/20.00, /*15 7000.0*/20.00}
};

static const ignition_table_t tps_advance_table = {
{/*0  engineLoad=0.00*/   /*0 800.0*/+15.00, /*1 1213.0*/+16.33, /*2 1626.0*/+17.67, /*3 2040.0*/+19.00, /*4 2453.0*/+20.33, /*5 2866.0*/+21.67, /*6 3280.0*/+23.00, /*7 3693.0*/+24.33, /*8 4106.0*/+25.67, /*9 4520.0*/+27.00, /*10 4933.0*/+28.33, /*11 5346.0*/+29.67, /*12 5760.0*/+31.00, /*13 6173.0*/+32.33, /*14 6586.0*/+33.67, /*15 7000.0*/+35.00},
{/*1  engineLoad=6.66*/	  /*0 800.0*/+14.80, /*1 1213.0*/+16.12, /*2 1626.0*/+17.45, /*3 2040.0*/+18.77, /*4 2453.0*/+20.10, /*5 2866.0*/+21.42, /*6 3280.0*/+22.75, /*7 3693.0*/+24.07, /*8 4106.0*/+25.40, /*9 4520.0*/+26.72, /*10 4933.0*/+28.04, /*11 5346.0*/+29.37, /*12 5760.0*/+30.69, /*13 6173.0*/+32.02, /*14 6586.0*/+33.34, /*15 7000.0*/+34.67},
{/*2  engineLoad=13.33*/  /*0 800.0*/+14.60, /*1 1213.0*/+15.92, /*2 1626.0*/+17.23, /*3 2040.0*/+18.55, /*4 2453.0*/+19.86, /*5 2866.0*/+21.18, /*6 3280.0*/+22.49, /*7 3693.0*/+23.81, /*8 4106.0*/+25.12, /*9 4520.0*/+26.44, /*10 4933.0*/+27.76, /*11 5346.0*/+29.07, /*12 5760.0*/+30.39, /*13 6173.0*/+31.70, /*14 6586.0*/+33.02, /*15 7000.0*/+34.33},
{/*3  engineLoad=20.00*/  /*0 800.0*/+14.40, /*1 1213.0*/+15.71, /*2 1626.0*/+17.01, /*3 2040.0*/+18.32, /*4 2453.0*/+19.63, /*5 2866.0*/+20.93, /*6 3280.0*/+22.24, /*7 3693.0*/+23.55, /*8 4106.0*/+24.85, /*9 4520.0*/+26.16, /*10 4933.0*/+27.47, /*11 5346.0*/+28.77, /*12 5760.0*/+30.08, /*13 6173.0*/+31.39, /*14 6586.0*/+32.69, /*15 7000.0*/+34.00},
{/*4  engineLoad=26.66*/  /*0 800.0*/+14.20, /*1 1213.0*/+15.50, /*2 1626.0*/+16.80, /*3 2040.0*/+18.09, /*4 2453.0*/+19.39, /*5 2866.0*/+20.69, /*6 3280.0*/+21.99, /*7 3693.0*/+23.28, /*8 4106.0*/+24.58, /*9 4520.0*/+25.88, /*10 4933.0*/+27.18, /*11 5346.0*/+28.48, /*12 5760.0*/+29.77, /*13 6173.0*/+31.07, /*14 6586.0*/+32.37, /*15 7000.0*/+33.67},
{/*5  engineLoad=33.33*/  /*0 800.0*/+14.00, /*1 1213.0*/+15.29, /*2 1626.0*/+16.58, /*3 2040.0*/+17.87, /*4 2453.0*/+19.16, /*5 2866.0*/+20.44, /*6 3280.0*/+21.73, /*7 3693.0*/+23.02, /*8 4106.0*/+24.31, /*9 4520.0*/+25.60, /*10 4933.0*/+26.89, /*11 5346.0*/+28.18, /*12 5760.0*/+29.47, /*13 6173.0*/+30.76, /*14 6586.0*/+32.04, /*15 7000.0*/+33.33},
{/*6  engineLoad=40.00*/  /*0 800.0*/+13.80, /*1 1213.0*/+15.08, /*2 1626.0*/+16.36, /*3 2040.0*/+17.64, /*4 2453.0*/+18.92, /*5 2866.0*/+20.20, /*6 3280.0*/+21.48, /*7 3693.0*/+22.76, /*8 4106.0*/+24.04, /*9 4520.0*/+25.32, /*10 4933.0*/+26.60, /*11 5346.0*/+27.88, /*12 5760.0*/+29.16, /*13 6173.0*/+30.44, /*14 6586.0*/+31.72, /*15 7000.0*/+33.00},
{/*7  engineLoad=46.66*/  /*0 800.0*/+13.60, /*1 1213.0*/+14.87, /*2 1626.0*/+16.14, /*3 2040.0*/+17.41, /*4 2453.0*/+18.68, /*5 2866.0*/+19.96, /*6 3280.0*/+21.23, /*7 3693.0*/+22.50, /*8 4106.0*/+23.77, /*9 4520.0*/+25.04, /*10 4933.0*/+26.31, /*11 5346.0*/+27.58, /*12 5760.0*/+28.85, /*13 6173.0*/+30.12, /*14 6586.0*/+31.40, /*15 7000.0*/+32.67},
{/*8  engineLoad=53.33*/  /*0 800.0*/+13.40, /*1 1213.0*/+14.66, /*2 1626.0*/+15.92, /*3 2040.0*/+17.19, /*4 2453.0*/+18.45, /*5 2866.0*/+19.71, /*6 3280.0*/+20.97, /*7 3693.0*/+22.24, /*8 4106.0*/+23.50, /*9 4520.0*/+24.76, /*10 4933.0*/+26.02, /*11 5346.0*/+27.28, /*12 5760.0*/+28.55, /*13 6173.0*/+29.81, /*14 6586.0*/+31.07, /*15 7000.0*/+32.33},
{/*9  engineLoad=60.00*/  /*0 800.0*/+13.20, /*1 1213.0*/+14.45, /*2 1626.0*/+15.71, /*3 2040.0*/+16.96, /*4 2453.0*/+18.21, /*5 2866.0*/+19.47, /*6 3280.0*/+20.72, /*7 3693.0*/+21.97, /*8 4106.0*/+23.23, /*9 4520.0*/+24.48, /*10 4933.0*/+25.73, /*11 5346.0*/+26.99, /*12 5760.0*/+28.24, /*13 6173.0*/+29.49, /*14 6586.0*/+30.75, /*15 7000.0*/+32.00},
{/*10 engineLoad=66.66*/  /*0 800.0*/+13.00, /*1 1213.0*/+14.24, /*2 1626.0*/+15.49, /*3 2040.0*/+16.73, /*4 2453.0*/+17.98, /*5 2866.0*/+19.22, /*6 3280.0*/+20.47, /*7 3693.0*/+21.71, /*8 4106.0*/+22.96, /*9 4520.0*/+24.20, /*10 4933.0*/+25.44, /*11 5346.0*/+26.69, /*12 5760.0*/+27.93, /*13 6173.0*/+29.18, /*14 6586.0*/+30.42, /*15 7000.0*/+31.67},
{/*11 engineLoad=73.33*/  /*0 800.0*/+12.80, /*1 1213.0*/+14.04, /*2 1626.0*/+15.27, /*3 2040.0*/+16.51, /*4 2453.0*/+17.74, /*5 2866.0*/+18.98, /*6 3280.0*/+20.21, /*7 3693.0*/+21.45, /*8 4106.0*/+22.68, /*9 4520.0*/+23.92, /*10 4933.0*/+25.16, /*11 5346.0*/+26.39, /*12 5760.0*/+27.63, /*13 6173.0*/+28.86, /*14 6586.0*/+30.10, /*15 7000.0*/+31.33},
{/*12 engineLoad=80.00*/  /*0 800.0*/+12.60, /*1 1213.0*/+13.83, /*2 1626.0*/+15.05, /*3 2040.0*/+16.28, /*4 2453.0*/+17.51, /*5 2866.0*/+18.73, /*6 3280.0*/+19.96, /*7 3693.0*/+21.19, /*8 4106.0*/+22.41, /*9 4520.0*/+23.64, /*10 4933.0*/+24.87, /*11 5346.0*/+26.09, /*12 5760.0*/+27.32, /*13 6173.0*/+28.55, /*14 6586.0*/+29.77, /*15 7000.0*/+31.00},
{/*13 engineLoad=86.66*/  /*0 800.0*/+12.40, /*1 1213.0*/+13.62, /*2 1626.0*/+14.84, /*3 2040.0*/+16.05, /*4 2453.0*/+17.27, /*5 2866.0*/+18.49, /*6 3280.0*/+19.71, /*7 3693.0*/+20.92, /*8 4106.0*/+22.14, /*9 4520.0*/+23.36, /*10 4933.0*/+24.58, /*11 5346.0*/+25.80, /*12 5760.0*/+27.01, /*13 6173.0*/+28.23, /*14 6586.0*/+29.45, /*15 7000.0*/+30.67},
{/*14 engineLoad=93.33*/  /*0 800.0*/+12.20, /*1 1213.0*/+13.41, /*2 1626.0*/+14.62, /*3 2040.0*/+15.83, /*4 2453.0*/+17.04, /*5 2866.0*/+18.24, /*6 3280.0*/+19.45, /*7 3693.0*/+20.66, /*8 4106.0*/+21.87, /*9 4520.0*/+23.08, /*10 4933.0*/+24.29, /*11 5346.0*/+25.50, /*12 5760.0*/+26.71, /*13 6173.0*/+27.92, /*14 6586.0*/+29.12, /*15 7000.0*/+30.33},
{/*15 engineLoad=100.00*/ /*0 800.0*/+12.00, /*1 1213.0*/+13.20, /*2 1626.0*/+14.40, /*3 2040.0*/+15.60, /*4 2453.0*/+16.80, /*5 2866.0*/+18.00, /*6 3280.0*/+19.20, /*7 3693.0*/+20.40, /*8 4106.0*/+21.60, /*9 4520.0*/+22.80, /*10 4933.0*/+24.00, /*11 5346.0*/+25.20, /*12 5760.0*/+26.40, /*13 6173.0*/+27.60, /*14 6586.0*/+28.80, /*15 7000.0*/+30.00}
};


void setCitroenBerlingoTU3JPConfiguration(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->engineType = CITROEN_TU3JP;

	/**
	 * Base engine setting
	 */
	setOperationMode(engineConfiguration, FOUR_STROKE_CRANK_SENSOR);
	engineConfiguration->triggerConfig.triggerType = TT_TOOTHED_WHEEL_60_2;
	engineConfiguration->globalTriggerAngleOffset = 114;
	engineConfiguration->cylindersCount = 4;
	engineConfiguration->displacement = 1.360;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->injectionMode = IM_BATCH;
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->rpmHardLimit = 5000;
	engineConfiguration->cranking.rpm = 600;

	/**
	* Cranking fuel setting
	* TODO: they recomend using something like -40C for low point and +80C for high point
	*/
	engineConfiguration->cranking.baseFuel = 15;

	/**
	 * Algorithm Alpha-N setting
	 */
	engineConfiguration->algorithm = LM_ALPHA_N;
	setFuelLoadBin(engineConfiguration, 0, 100);
	setFuelRpmBin(engineConfiguration, 800, 7000);
	setTimingLoadBin(engineConfiguration, 0, 100);
	setTimingRpmBin(engineConfiguration, 800, 7000);

	/**
	 * Outputs
	 */

	// Frankenstein lo-side output #1: PC14 Igniter 1-4
	// Frankenstein lo-side output #2: PC15 Igniter 2-3
	// Frankenstein lo-side output #3: PE6  Injector 1-4
	// Frankenstein lo-side output #4: PC13 Injector 2-3
	// Frankenstein lo-side output #5: PE4
	// Frankenstein lo-side output #6: PE5
	// Frankenstein lo-side output #7: PE2
	// Frankenstein lo-side output #8: PE3
	// Frankenstein lo-side output #9: PE0
	// Frankenstein lo-side output #10: PE1
	// Frankenstein lo-side output #11: PB8
	// Frankenstein lo-side output #12: PB9 Fuel pump

	engineConfiguration->injectorFlow = 137; //SIEMENS DEKA VAZ20734
	boardConfiguration->injectionPins[0] = GPIOE_6;
	boardConfiguration->injectionPins[1] = GPIOC_13;
	boardConfiguration->injectionPins[2] = GPIO_UNASSIGNED;
	boardConfiguration->injectionPins[3] = GPIO_UNASSIGNED;

	boardConfiguration->ignitionPins[0] = GPIOC_14;
	boardConfiguration->ignitionPins[1] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[2] = GPIOC_15;
	boardConfiguration->ignitionPins[3] = GPIO_UNASSIGNED;

	boardConfiguration->fuelPumpPin = GPIOB_9;
	boardConfiguration->fuelPumpPinMode = OM_DEFAULT;

	boardConfiguration->fanPin = GPIO_UNASSIGNED;
//	boardConfiguration->fanPinMode = OM_DEFAULT;

//	boardConfiguration->o2heaterPin = GPIOC_13;
//	boardConfiguration->logicAnalyzerPins[1] = GPIO_UNASSIGNED;

	/**
	 * Inputs
	 */

	// See https://docs.google.com/spreadsheet/ccc?key=0Arl1FeMZcfisdEdGdUlHdWh6cVBoSzFIbkxqa1QtZ3c
	// Frankenstein analog input #1: PA1 adc1	MAP
	// Frankenstein analog input #2: PA3 adc3	TPS
	// Frankenstein analog input #3: PC3 adc13	IAT
	// Frankenstein analog input #4: PC1 adc11	CLT
	// Frankenstein analog input #5: PA0 adc0	vBatt
	// Frankenstein analog input #6: PC2 adc12	WBO
	// Frankenstein analog input #7: PA4 adc4
	// Frankenstein analog input #8: PA2 adc2
	// Frankenstein analog input #9: PA6 adc6
	// Frankenstein analog input #10: PA7 adc7
	// Frankenstein analog input #11: PC4 adc14
	// Frankenstein analog input #12: PC5 adc15

	/**
	 * MAP <BOSCH 0 261 230 057>
	 */
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_1;
	engineConfiguration->map.sensor.type = MT_CUSTOM;
	engineConfiguration->map.sensor.valueAt0 = 10;
	engineConfiguration->map.sensor.valueAt5 = 110;
	/**
	 * TPS <MAGNETI MARELLI>
	 */
	engineConfiguration->tpsAdcChannel = EFI_ADC_3;
	engineConfiguration->tpsMin = 108; // convert 12to10 bit (ADC/4)
	engineConfiguration->tpsMax = 812; // convert 12to10 bit (ADC/4)
	/**
	 * IAT <OEM ECU>
	 */
	engineConfiguration->iatAdcChannel = EFI_ADC_13;
	setThermistorConfiguration(&engineConfiguration->iat, -20.0, 15600.0, 23.0, 2250.0, 92.0, 240.0);
	engineConfiguration->iat.bias_resistor = 2660;
	/**
	* CLT <LADA Samara>
	*/
	engineConfiguration->cltAdcChannel = EFI_ADC_11;
	setThermistorConfiguration(&engineConfiguration->clt, -20.0, 28680.0, 25.0, 2796.0, 100.0, 177.0);
	engineConfiguration->clt.bias_resistor = 2660;
	/**
	 * vBatt
	 */
	engineConfiguration->vbattAdcChannel = EFI_ADC_0;
	engineConfiguration->vbattDividerCoeff = ((float) (2.6 + 11)) / 2.6 * 2;
	/**
	* WBO Innovate LC-1
	*/
	engineConfiguration->afrSensor.afrAdcChannel = EFI_ADC_12;
	/**
	* Other
	*/
//	engineConfiguration->mafAdcChannel = GPIO_UNASSIGNED;

	copyFuelTable(tps_fuel_table, engineConfiguration->fuelTable);
	copyTimingTable(tps_advance_table, engineConfiguration->ignitionTable);

}
