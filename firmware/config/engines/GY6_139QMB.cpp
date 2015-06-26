/**
 * @file	GY6_139QMB.cpp
 * @brief	139qmb default engine configuration
 *
 * @date Feb 13, 2014
 * @author rus084, (c) 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "GY6_139QMB.h"
#include "engine_math.h"
#include "engine_configuration.h"
#include "allsensors.h"
#include "advance_map.h"

EXTERN_ENGINE
;

static const fuel_table_t default_139qmb_fuel_table = {

{ 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000 }, { 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000 }, { 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000 }, { 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000 }, { 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
		6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000 },
		{ 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000 }, { 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000 }, { 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000 }, { 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000 }, { 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000 }, { 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000 }, { 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000 }, { 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000 }, { 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000 }, { 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000 }, { 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
				6.000000 }

};

static void setDefault139qmbMaps(DECLARE_ENGINE_PARAMETER_F) {

	setFuelLoadBin(1.2, 4.4 PASS_ENGINE_PARAMETER);
	setFuelRpmBin(1000, 11000 PASS_ENGINE_PARAMETER);
	setTimingLoadBin(1.2, 4.4 PASS_ENGINE_PARAMETER);
	setTimingRpmBin(1000, 11000 PASS_ENGINE_PARAMETER);

	copyFuelTable(default_139qmb_fuel_table, config->fuelTable);
	//copyTimingTable(default_139qmb_timing_table, config->ignitionTable);
}

void setGy6139qmbDefaultEngineConfiguration(DECLARE_ENGINE_PARAMETER_F) {
	setDefault139qmbMaps(PASS_ENGINE_PARAMETER_F);
//        engineConfiguration->map.sensor.type = MT_3V_SENSOR;
	setEgoSensor(ES_NarrowBand PASS_ENGINE_PARAMETER);

	engineConfiguration->rpmHardLimit = 9000;
	engineConfiguration->cranking.rpm = 1100;
	engineConfiguration->targetIdleRpm = 2000;
	engineConfiguration->analogInputDividerCoefficient = 1;
	engineConfiguration->algorithm = LM_MAP;
	engineConfiguration->globalTriggerAngleOffset = 45;
	engineConfiguration->bc.sensorChartMode = SC_MAP;
	engineConfiguration->specs.displacement = 0.072; // 72cc
	engineConfiguration->specs.cylindersCount = 1;
	setOperationMode(engineConfiguration, FOUR_STROKE_CRANK_SENSOR);

	engineConfiguration->specs.firingOrder = FO_ONE_CYLINDER;

	/**
	 * We treat the trigger as 8-1 toothed wheel
	 */
	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL;
	engineConfiguration->trigger.customTotalToothCount = 8;
	engineConfiguration->trigger.customSkippedToothCount = 1;

	boardConfiguration->injectionPins[0] = GPIOC_9;
	boardConfiguration->ignitionPins[0] = GPIOC_8;

}
