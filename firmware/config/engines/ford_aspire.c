/**
 * @file    ford_aspire.c
 * @brief	1996 Ford Aspire default engine configuration
 *
 * @date Sep 9, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include <string.h>

#include "ford_aspire.h"

#include "allsensors.h"
#include "engines.h"
#include "engine_math.h"
#include "settings.h"
#include "rpm_calculator.h"
#include "fuel_map.h"
#include "engine_controller.h"
#include "engine_configuration.h"
#include "dist_emulator.h"
#include "main_trigger_callback.h"

#ifdef EFI_SUPPORT_FORD_ASPIRE

/**
 * Just the default RPM bin - with TunerStudio you can adjust even the bins
 */

static float default_fuel_maf_bins[FUEL_MAF_COUNT] = {/*0*/ 1.200000,
/*1*/ 1.413333,
/*2*/ 1.626667,
/*3*/ 1.840000,
/*4*/ 2.053333,
/*5*/ 2.266667,
/*6*/ 2.480000,
/*7*/ 2.693333,
/*8*/ 2.906667,
/*9*/ 3.120000,
/*10*/ 3.333333,
/*11*/ 3.546667,
/*12*/ 3.760000,
/*13*/ 3.973333,
/*14*/ 4.186667,
/*15*/ 4.400000,
};
static float default_fuel_rpm_bins[FUEL_RPM_COUNT] = {/*0*/ 800.000000,
/*1*/ 1213.333374,
/*2*/ 1626.666748,
/*3*/ 2040.000000,
/*4*/ 2453.333496,
/*5*/ 2866.666748,
/*6*/ 3280.000000,
/*7*/ 3693.333496,
/*8*/ 4106.666992,
/*9*/ 4520.000000,
/*10*/ 4933.333496,
/*11*/ 5346.666992,
/*12*/ 5760.000000,
/*13*/ 6173.333496,
/*14*/ 6586.666992,
/*15*/ 7000.000000,
};

/**
 * This is just the default map which is stored into flash memory in case flash is empty
 * The convenient way to override these default would be to tune this map using TunerStudio software
 * with which rusEfi is integrated
 */
static float default_fuel_table[FUEL_MAF_COUNT][FUEL_RPM_COUNT] = {
/* RPM			800.000000	1213.333374	1626.666748	2040.000000	2453.333496	2866.666748	3280.000000	3693.333496	4106.666992	4520.000000	4933.333496	5346.666992	5760.000000	6173.333496	6586.666992	7000.000000*/
/* Load 1.200000 */{	1.542000,	1.547600,	1.551867,	1.570000,	1.550000,	0.908666,	0.794800,	0.775200,	0.791733,	0.800000,	0.798667,	0.805733,	0.810000,	0.810000,	0.810000,	0.810000},
/* Load 1.413333 */{	1.532133,	1.565325,	1.551244,	1.552773,	1.546018,	0.802089,	0.810000,	0.788507,	0.808898,	0.744987,	0.701378,	0.711404,	0.744667,	0.810000,	0.810000,	0.810000},
/* Load 1.626667 */{	1.543600,	1.545573,	1.555956,	1.545973,	1.415333,	0.115288,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000},
/* Load 1.840000 */{	1.538800,	1.741893,	1.558426,	1.591440,	1.228773,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000},
/* Load 2.053333 */{	2.322933,	3.439928,	2.818523,	2.242266,	2.125839,	1.194041,	0.488959,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000},
/* Load 2.266667 */{	7.696667,	5.957510,	4.700978,	3.879200,	3.099600,	2.403111,	2.458666,	1.790979,	2.190533,	2.074667,	1.368887,	1.287556,	0.000000,	0.000000,	0.000000,	0.000000},
/* Load 2.480000 */{	14.330001,	8.710773,	6.558134,	5.491520,	5.117494,	4.308798,	3.185521,	3.339520,	2.883200,	2.840399,	2.643334,	2.505092,	2.296640,	0.000000,	0.000000,	0.000000},
/* Load 2.693333 */{	21.354004,	15.415981,	10.953371,	8.779520,	5.866481,	5.038577,	5.113254,	4.395565,	4.537200,	3.559386,	3.828622,	3.147404,	3.377706,	2.780000,	2.780000,	2.780000},
/* Load 2.906667 */{	20.020401,	16.311201,	17.209972,	15.600482,	10.950183,	7.773465,	6.243252,	7.400613,	6.672044,	6.133946,	5.529999,	4.769466,	4.528134,	4.010000,	4.010000,	4.010000},
/* Load 3.120000 */{	18.264000,	15.464134,	15.595227,	15.395760,	12.987042,	13.339199,	8.897678,	8.927333,	8.032880,	6.769040,	5.823335,	6.413146,	6.089281,	5.730000,	5.730000,	5.730000},
/* Load 3.333333 */{	17.414667,	15.366401,	15.187378,	15.338401,	15.306623,	15.386889,	14.470800,	11.941733,	10.985557,	9.956400,	9.019111,	8.441555,	7.515199,	6.900000,	6.900000,	6.900000},
/* Load 3.546667 */{	17.005333,	15.372302,	15.188160,	15.278268,	15.325876,	15.561645,	15.638906,	15.415441,	13.630393,	10.918774,	11.508314,	10.660010,	9.551816,	9.230000,	9.230000,	9.230000},
/* Load 3.760000 */{	16.978800,	15.360346,	15.170587,	15.301680,	15.331520,	15.684401,	15.810480,	15.702454,	15.828107,	15.114964,	14.666001,	11.908847,	12.046723,	9.230000,	9.230000,	9.230000},
/* Load 3.973333 */{	16.975599,	15.343084,	15.305715,	15.287172,	15.288801,	15.484089,	15.928854,	15.780366,	15.669041,	15.836693,	16.123335,	15.054674,	14.972587,	14.610000,	14.610000,	14.610000},
/* Load 4.186667 */{	16.961868,	15.368391,	15.210348,	15.290641,	15.263707,	15.485778,	15.827333,	15.802435,	15.677885,	15.827120,	15.997155,	16.027468,	15.478480,	15.190000,	15.190000,	15.190000},
/* Load 4.400000 */{	17.010000,	15.250000,	15.680000,	15.440000,	15.270000,	15.470000,	15.800000,	15.730000,	15.600000,	15.790000,	16.120001,	16.110001,	15.630000,	15.150000,	15.150000,	15.150000}
};

static void confgiureFordAspireTriggerShape(trigger_shape_s * s) {
	triggerShapeInit(s);

	triggerAddEvent(s, 53.747, T_SECONDARY, 1);
	triggerAddEvent(s, 121.90, T_SECONDARY, 0);
	triggerAddEvent(s, 232.76, T_SECONDARY, 1);
	triggerAddEvent(s, 300.54, T_SECONDARY, 0);
	triggerAddEvent(s, 360, T_PRIMARY, 1);

	triggerAddEvent(s, 409.8412, T_SECONDARY, 1);
	triggerAddEvent(s, 478.6505, T_SECONDARY, 0);
	triggerAddEvent(s, 588.045, T_SECONDARY, 1);
	triggerAddEvent(s, 657.03, T_SECONDARY, 0);
	triggerAddEvent(s, 720, T_PRIMARY, 0);
}

static void configureAspireEngineEventHandler(EventHandlerConfiguration *config) {
	float x = 51;

	resetEventList(&config->crankingInjectionEvents);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), x);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), x);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_3_OUTPUT), x);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_4_OUTPUT), x);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), x + 180);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), x + 180);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_3_OUTPUT), x + 180);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_4_OUTPUT), x + 180);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), x + 360);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), x + 360);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_3_OUTPUT), x + 360);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_4_OUTPUT), x + 360);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), x + 540);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), x + 540);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_3_OUTPUT), x + 540);
	registerActuatorEvent(&config->crankingInjectionEvents, 0, addOutputSignal(INJECTOR_4_OUTPUT), x + 540);

	resetEventList(&config->injectionEvents);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_4_OUTPUT), x);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), x + 180);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), x + 360);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_3_OUTPUT), x + 540);

	resetEventList(&config->ignitionEvents);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 180);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 360);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 540);
}

static void setDefaultFuelMap(EngineConfiguration *engineConfiguration) {
	for (int i = 0; i < FUEL_MAF_COUNT; i++)
		engineConfiguration->fuelKeyBins[i] = default_fuel_maf_bins[i];
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		engineConfiguration->fuelRpmBins[i] = default_fuel_rpm_bins[i];
	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = default_fuel_table[k][r];
		}
	}
}

void setFordAspireEngineConfiguration(EngineConfiguration *engineConfiguration) {
engineConfiguration->tpsMin = 1;
	engineConfiguration->tpsMax = 1000;

	engineConfiguration->ignitonOffset = 35;
	engineConfiguration->rpmHardLimit = 7000;

	engineConfiguration->crankingSettings.coolantTempMin = 15;
	engineConfiguration->crankingSettings.coolantTempMax = 65;
	engineConfiguration->crankingSettings.minTempPW = 16;
	engineConfiguration->crankingSettings.maxTempPW = 8;

	setDefaultFuelMap(engineConfiguration);
}

void setFordAspireEngineConfiguration2(EngineConfiguration2 *engineConfiguration2) {
	engineConfiguration2->triggerShape.onlyOneTeeth = TRUE;
	configureAspireEngineEventHandler(&engineConfiguration2->engineEventConfiguration);
	engineConfiguration2->triggerShape.shaftPositionEventCount = 10;
	confgiureFordAspireTriggerShape(&engineConfiguration2->triggerShape);
}

#endif /* EFI_SUPPORT_FORD_ASPIRE */
