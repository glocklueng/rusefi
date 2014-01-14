/**
 * @file	engine_controller.c
 * @brief	Utility method related to the engine configuration data structure.
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "engine_configuration.h"
#include "allsensors.h"

#define ADC_CHANNEL_FAST_ADC 256

/**
 * @brief	Global default engine configuration
 * This method sets the default global engine configuration. These values are later overridden by engine-specific defaults
 * and the settings saves in flash memory.
 */
void setDefaultConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->injectorLag = 0.0;

	for (int i = 0; i < IAT_CURVE_SIZE; i++) {
		engineConfiguration->iatFuelCorrBins[i] = -40 + i * 10;
		engineConfiguration->iatFuelCorr[i] = 1; // this correction is a multiplier
	}

	for (int i = 0; i < CLT_CURVE_SIZE; i++) {
		engineConfiguration->cltFuelCorrBins[i] = -40 + i * 10;
		engineConfiguration->cltFuelCorr[i] = 1; // this correction is a multiplier
	}

	for (int i = 0; i < VBAT_INJECTOR_CURVE_SIZE; i++) {
		engineConfiguration->battInjectorLagCorrBins[i] = 12 - VBAT_INJECTOR_CURVE_SIZE / 2 + i;
		engineConfiguration->battInjectorLagCorr[i] = 0; // zero extra time by default
	}

	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			// 3ms would be the global default
			engineConfiguration->fuelTable[k][r] = 3;
		}
	}

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, 32, 9500, 75, 2100, 120, 1000);
	engineConfiguration->cltThermistorConf.bias_resistor =  1500;

	setThermistorConfiguration(&engineConfiguration->iatThermistorConf, 32, 9500, 75, 2100, 120, 1000);
// todo: this value is way off! I am pretty sure temp coeffs are off also
	engineConfiguration->iatThermistorConf.bias_resistor = 2700;

	engineConfiguration->rpmHardLimit = 7000;
	engineConfiguration->crankingSettings.crankingRpm = 400;


	engineConfiguration->crankingChargeAngle = 76;
	engineConfiguration->timingMode = TM_DYNAMIC;
	engineConfiguration->fixedModeTiming = 50;

	engineConfiguration->analogChartMode = AC_TRIGGER;

	engineConfiguration->map.channel = ADC_CHANNEL_FAST_ADC;

	engineConfiguration->pinOutputMode = OM_DEFAULT;
}

void setDefaultNonPersistentConfiguration(EngineConfiguration2 *engineConfiguration2) {
	engineConfiguration2->clt.channel = ADC_LOGIC_COOLANT;
	engineConfiguration2->iat.channel = ADC_LOGIC_AIR;
	/**
	 * 0.5 means primary position sensor is on a camshaft
	 */
	engineConfiguration2->rpmMultiplier = 0.5;

	engineConfiguration2->triggerShape.onlyOneTeeth = FALSE;
	engineConfiguration2->triggerShape.useRiseEdge = TRUE;

	trigger_shape_s *s = &engineConfiguration2->triggerShape;

	s->syncRatioFrom = 1.5;
	s->syncRatioTo = 3;

	/**
	 * 720 is the range for four stroke
	 */
	engineConfiguration2->crankAngleRange = 720;

	engineConfiguration2->can_nbc_type = CAN_BUS_NBC_BMW;
	engineConfiguration2->can_nbc_broadcast_period = 50;

	engineConfiguration2->cylindersCount = 4;

	engineConfiguration2->hasMapSensor = TRUE;
	engineConfiguration2->hasCltSensor = TRUE;
}
