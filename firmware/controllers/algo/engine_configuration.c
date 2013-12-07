/**
 * @file	engine_controller.c
 * @brief	Utility method related to the engine configuration data structure.
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "engine_configuration.h"
#include "main.h"

extern EngineConfiguration2 engineConfiguration2;

/**
 * @brief	Global default engine configuration
 * This method sets the default global engine configuration. These values are later overridden by engine-specific defaults
 * and the settings saves in flash memory.
 */
void setDefaultConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->injectorLag = 0.0;

	for (int i = 0; i < IAT_CURVE_SIZE; i++) {
		engineConfiguration->iatFuelCorrBins[i] = -40 + i * 10;
		engineConfiguration->iatFuelCorr[i] = 1;
	}

	for (int i = 0; i < CLT_CURVE_SIZE; i++) {
		engineConfiguration->cltFuelCorrBins[i] = -40 + i * 10;
		engineConfiguration->cltFuelCorr[i] = 1;
	}

	for (int i = 0; i < VBAT_INJECTOR_CURVE_SIZE; i++) {
		engineConfiguration->battInjectorLagCorrBins[i] = 12 - VBAT_INJECTOR_CURVE_SIZE / 2 + i;
		engineConfiguration->battInjectorLagCorr[i] = 1;
	}

	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			// 3ms would be the global default
			engineConfiguration->fuelTable[k][r] = 3;
		}
	}

	engineConfiguration2.clt.channel = ADC_LOGIC_COOLANT;
	engineConfiguration->cltThermistorConf.s_h_a = -0.0015925922146267837;
	engineConfiguration->cltThermistorConf.s_h_b = 0.0008205491888240184;
	engineConfiguration->cltThermistorConf.s_h_c =-0.0000029438499727564513;
	engineConfiguration->cltThermistorConf.bias_resistor =  1500;

	engineConfiguration2.iat.channel = ADC_LOGIC_AIR;
	engineConfiguration->iatThermistorConf.s_h_a = -0.0015925922146267837;
	engineConfiguration->iatThermistorConf.s_h_b = 0.0008205491888240184;
	engineConfiguration->iatThermistorConf.s_h_c =-0.0000029438499727564513;

// todo: this value is way off! I am pretty sure temp coeffs are off also
	engineConfiguration->iatThermistorConf.bias_resistor = 2700;



	engineConfiguration->rpmHardLimit = 7000;
	engineConfiguration->crankingRpm = 400;
}

static void printIntArray(int array[], int size) {
	for (int j = 0; j < size; j++)
		print("%d ", array[j]);
	print("\r\n");
}

void printFloatArray(char *prefix, float array[], int size) {
	print(prefix);
	for (int j = 0; j < size; j++)
		print("%f ", array[j]);
	print("\r\n");
}

/**
 * @brief	Prints current engine configuration to human-readable console.
 */
void printConfiguration(EngineConfiguration *engineConfiguration) {
	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		print("line %d (%f): ", k, engineConfiguration->fuelKeyBins[k]);
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			print("%f ", engineConfiguration->fuelTable[k][r]);
		}
		print("\r\n");
	}

	printFloatArray("RPM bin: ", engineConfiguration->fuelRpmBins, FUEL_RPM_COUNT);

	printFloatArray("Y bin: ", engineConfiguration->fuelKeyBins, FUEL_MAF_COUNT);

	printFloatArray("CLT: ", engineConfiguration->cltFuelCorr, CLT_CURVE_SIZE);
	printFloatArray("CLT bins: ", engineConfiguration->cltFuelCorrBins, CLT_CURVE_SIZE);

	printFloatArray("IAT: ", engineConfiguration->iatFuelCorr, IAT_CURVE_SIZE);
	printFloatArray("IAT bins: ", engineConfiguration->iatFuelCorrBins, IAT_CURVE_SIZE);

	printFloatArray("vBatt: ", engineConfiguration->battInjectorLagCorr, VBAT_INJECTOR_CURVE_SIZE);
	printFloatArray("vBatt bins: ", engineConfiguration->battInjectorLagCorrBins, VBAT_INJECTOR_CURVE_SIZE);

	print("rpmHardLimit: %d\r\n", engineConfiguration->rpmHardLimit);

	print("tpsMin: %d\r\n", engineConfiguration->tpsMin);
	print("tpsMax: %d\r\n", engineConfiguration->tpsMax);

	print("crankingRpm: %d\r\n", engineConfiguration->crankingRpm);
}
