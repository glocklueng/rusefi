/**
 * @file	speed_density.cpp
 *
 * See http://rusefi.com/wiki/index.php?title=Manual:Software:Fuel_Control#Speed_Density for details
 *
 * @date May 29, 2014
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#include "main.h"
#include "speed_density.h"
#include "interpolation.h"
#include "rpm_calculator.h"
#include "engine_math.h"
#include "engine_state.h"

#define K_AT_MIN_RPM_MIN_TPS 0.25
#define K_AT_MIN_RPM_MAX_TPS 0.25
#define K_AT_MAX_RPM_MIN_TPS 0.25
#define K_AT_MAX_RPM_MAX_TPS 0.9

#define rpmMin 500
#define rpmMax 8000

fuel_Map3D_t veMap("VE");
fuel_Map3D_t ve2Map("VE2");
fuel_Map3D_t afrMap("AFR");
baroCorr_Map3D_t baroCorrMap("baro");

#define tpMin 0
#define tpMax 100
//  http://rusefi.com/math/t_charge.html
float getTCharge(int rpm, float tps, float coolantTemp, float airTemp) {
	float minRpmKcurrentTPS = interpolate(tpMin, K_AT_MIN_RPM_MIN_TPS, tpMax,
	K_AT_MIN_RPM_MAX_TPS, tps);
	float maxRpmKcurrentTPS = interpolate(tpMin, K_AT_MAX_RPM_MIN_TPS, tpMax,
	K_AT_MAX_RPM_MAX_TPS, tps);

	float Tcharge_coff = interpolate(rpmMin, minRpmKcurrentTPS, rpmMax, maxRpmKcurrentTPS, rpm);

	float Tcharge = coolantTemp * (1 - Tcharge_coff) + airTemp * Tcharge_coff;

	return Tcharge;
}

/**
 * is J/g*K
 */
#define GAS_R 0.28705

float getAirMass(engine_configuration_s *engineConfiguration, float VE, float MAP, float tempK) {
	// todo: pre-calculate cylinder displacement to save one division
	float cylinderDisplacement = engineConfiguration->specs.displacement / engineConfiguration->specs.cylindersCount;
	return (cylinderDisplacement * VE * MAP) / (GAS_R * tempK);
}

/**
 * @return per cylinder injection time, in seconds
 */
float sdMath(engine_configuration_s *engineConfiguration, float airMass, float AFR) {

	/**
	 * todo: pre-calculate gramm/second injector flow to save one multiplication
	 * open question if that's needed since that's just a multiplication
	 */
	float injectorFlowRate = cc_minute_to_gramm_second(engineConfiguration->injector.flow);
	/**
	 * injection_pulse_duration = fuel_mass / injector_flow
	 * fuel_mass = air_mass / target_afr
	 *
	 * injection_pulse_duration = (air_mass / target_afr) / injector_flow
	 */
	return airMass / (AFR * injectorFlowRate);
}

EXTERN_ENGINE;

/**
 * @return per cylinder injection time, in Milliseconds
 */
float getSpeedDensityFuel(int rpm DECLARE_ENGINE_PARAMETER_S) {
	//int rpm = engine->rpmCalculator->rpm();

	/**
	 * most of the values are pre-calculated for performance reasons
	 */
	float tChargeK = ENGINE(engineState.tChargeK);
	float map = getMap();

	float adjustedMap = map + engine->engineLoadAccelEnrichment.getMapEnrichment(PASS_ENGINE_PARAMETER_F);

	engine->engineState.airMass = getAirMass(engineConfiguration, ENGINE(engineState.currentVE), adjustedMap, tChargeK);

	return sdMath(engineConfiguration, engine->engineState.airMass, ENGINE(engineState.targerAFR)) * 1000;
}

static const baro_corr_table_t default_baro_corr = {
		{1.141, 1.086, 1.039, 1},
		{1.141, 1.086, 1.039, 1},
		{1.141, 1.086, 1.039, 1},
		{1.141, 1.086, 1.039, 1}
};

void setDefaultVETable(DECLARE_ENGINE_PARAMETER_F) {
	setRpmTableBin(config->veRpmBins, FUEL_RPM_COUNT);
	veMap.setAll(80);

//	setRpmTableBin(engineConfiguration->ve2RpmBins, FUEL_RPM_COUNT);
//	setTableBin2(engineConfiguration->ve2LoadBins, FUEL_LOAD_COUNT, 10, 300, 1);
//	ve2Map.setAll(0.81);

	setRpmTableBin(config->afrRpmBins, FUEL_RPM_COUNT);
	afrMap.setAll(14.7);

	setRpmTableBin(engineConfiguration->baroCorrRpmBins, BARO_CORR_SIZE);
	setTableBin2(engineConfiguration->baroCorrPressureBins, BARO_CORR_SIZE, 75, 105, 1);
	memcpy(engineConfiguration->baroCorrTable, default_baro_corr, sizeof(default_baro_corr));
}

void initSpeedDensity(DECLARE_ENGINE_PARAMETER_F) {
	veMap.init(config->veTable, config->veLoadBins, config->veRpmBins);
//	ve2Map.init(engineConfiguration->ve2Table, engineConfiguration->ve2LoadBins, engineConfiguration->ve2RpmBins);
	afrMap.init(config->afrTable, config->afrLoadBins, config->afrRpmBins);
	baroCorrMap.init(engineConfiguration->baroCorrTable, engineConfiguration->baroCorrPressureBins, engineConfiguration->baroCorrRpmBins);
}
