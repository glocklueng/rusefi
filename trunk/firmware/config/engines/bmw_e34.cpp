/**
 * @file bmw_e34.cpp
 *
 * set_engine_type 25
 *
 * Coil pairs: 1-6, 2-5, 3-4
 *
 * Injector groups: 1,2,3 & 4,5,6
 *
 * @date Nov 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "global.h"
#include "bmw_e34.h"
#include "thermistors.h"
#include "engine_math.h"

EXTERN_ENGINE
;

void setBmwE34(DECLARE_ENGINE_PARAMETER_F) {
	board_configuration_s * boardConfiguration = &engineConfiguration->bc;

	// chartsize 450
	engineConfiguration->digitalChartSize = 450;

//	setOperationMode(engineConfiguration, FOUR_STROKE_CAM_SENSOR);
//	engineConfiguration->trigger.type = TT_ONE_PLUS_TOOTHED_WHEEL_60_2;
//	engineConfiguration->injectionMode = IM_SEQUENTIAL;
//	boardConfiguration->triggerInputPins[0] = GPIOC_6;
//	boardConfiguration->triggerInputPins[1] = GPIOA_5;

//Base engine setting
	engineConfiguration->specs.cylindersCount = 6;
	engineConfiguration->specs.displacement = 2.91;
	engineConfiguration->specs.firingOrder = FO_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4;
	engineConfiguration->injectionMode = IM_BATCH;
	engineConfiguration->twoWireBatch = true;
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->useOnlyFrontForTrigger = true;

	// Trigger configuration
//	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL_60_2;
	setOperationMode(engineConfiguration, FOUR_STROKE_CRANK_SENSOR);
	engineConfiguration->globalTriggerAngleOffset = 84;

	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL;
	engineConfiguration->trigger.customTotalToothCount = 30;
	engineConfiguration->trigger.customSkippedToothCount = 1;


	// Injection settings
	engineConfiguration->injector.lag = 1.15;
	engineConfiguration->injector.flow = 750;

	// General settings
	boardConfiguration->tunerStudioSerialSpeed = 57600;
	engineConfiguration->rpmHardLimit = 7000;
	setAlgorithm(LM_SPEED_DENSITY PASS_ENGINE_PARAMETER);

	// for best performance at high RPM, we need to turn off 'Engine Sniffer' and 'Sensor Sniffer'
	boardConfiguration->analogChartMode = AC_OFF;
	engineConfiguration->isDigitalChartEnabled = false;

	engineConfiguration->isCylinderCleanupEnabled = false;
	engineConfiguration->isInjectionEnabled = true;
	engineConfiguration->isIgnitionEnabled = true;

	setConstantDwell(3 PASS_ENGINE_PARAMETER); // a bit shorter dwell
	engineConfiguration->ignMathCalculateAtIndex = 14;

	engineConfiguration->mapAveragingSchedulingAtIndex = 6;

	// Cranking
	engineConfiguration->cranking.rpm = 600;
	engineConfiguration->crankingInjectionMode = IM_BATCH;
	engineConfiguration->cranking.baseFuel = 7;
	engineConfiguration->useConstantDwellDuringCranking = true;
	engineConfiguration->ignitionDwellForCrankingMs = 6;

	// Inputs configuration
	engineConfiguration->analogInputDividerCoefficient = 1.52;
	engineConfiguration->vbattDividerCoeff = 5.33;

	boardConfiguration->triggerInputPins[0] = GPIOA_5;
	boardConfiguration->triggerInputPins[1] = GPIO_UNASSIGNED;

	setWholeTimingTable(25 PASS_ENGINE_PARAMETER);

	board_configuration_s *bc = &engineConfiguration->bc;
	bc->malfunctionIndicatorPin = GPIO_UNASSIGNED;

//	bc->isFastAdcEnabled = true;

	bc->injectionPinMode = OM_INVERTED;
	bc->injectionPins[0] = GPIOB_8; // #1
	bc->injectionPins[1] = GPIOE_2; // #2
	bc->injectionPins[2] = GPIOE_3; // #3
	bc->injectionPins[3] = GPIOE_4; // #4
	bc->injectionPins[4] = GPIOE_5; // #5
	bc->injectionPins[5] = GPIOE_6; // #6

	bc->ignitionPinMode = OM_INVERTED;

	bc->ignitionPins[0] = GPIOB_5; // #1
	bc->ignitionPins[2] = GPIOB_6; // #3
	bc->ignitionPins[4] = GPIOB_7; // #5

	bc->triggerErrorPin = GPIO_UNASSIGNED;

	// clutch up
	boardConfiguration->clutchUpPin = GPIOD_3;
	boardConfiguration->clutchUpPinMode = PI_PULLUP;

	// fuel pump
	boardConfiguration->fuelPumpPin = GPIOD_4;

	// idle
	boardConfiguration->idle.solenoidPin = GPIOC_14;
	boardConfiguration->idle.solenoidPinMode = OM_INVERTED;
	boardConfiguration->idle.solenoidFrequency = 300;
	boardConfiguration->idlePosition = 50; // set_idle_pwm 50

	// disable sd_card
	boardConfiguration->sdCardCsPin = GPIO_UNASSIGNED;
	boardConfiguration->is_enabled_spi_2 = false;
	boardConfiguration->is_enabled_spi_3 = false;
	boardConfiguration->max31855spiDevice = SPI_NONE;

	// turbocharger boost control solenoid: TODO output: GPIOE_6
	// water injection #1 TODO GPIOD_7
	// water injection #2 TODO GPIOE_2

	/**
	 * emulating the 60-0 trigger takes some resources, let's keep it slow by default
	 * rpm 200
	 */
	bc->triggerSimulatorFrequency = 200;

	// Configurating sensors:

	// map
	engineConfiguration->map.sensor.type = MT_MPX4250;

	// thermistors
	engineConfiguration->hasCltSensor = true;
	engineConfiguration->hasIatSensor = true;
	setThermistorConfiguration(&engineConfiguration->clt, -10, 9300, 20, 2500, 80, 335);
	engineConfiguration->iat.bias_resistor = 2200;
	setThermistorConfiguration(&engineConfiguration->iat, -10, 9300, 20, 2500, 80, 335);
	engineConfiguration->clt.bias_resistor = 2200;

//	/**
//	 * This saves a couple of ticks in trigger emulation methods
//	 * TODO: add some smart logic to detect unneeded trigger simulation pins?
//	 * TODO: but probably not worth it
//	 */
//	bc->triggerSimulatorPins[1] = GPIO_UNASSIGNED;

	boardConfiguration->triggerSimulatorPins[0] = GPIOD_1;
	boardConfiguration->triggerSimulatorPins[1] = GPIOD_2;
	bc->triggerSimulatorPins[2] = GPIO_UNASSIGNED;
}
