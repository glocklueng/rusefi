/**
 * @file    ford_aspire.c
 * @brief	1996 Ford Aspire default engine configuration
 *
 * @date Sep 9, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"

#include "ford_aspire.h"

#include "allsensors.h"
#include "engines.h"
#include "engine_math.h"
#include "advance_map.h"
#include "engine_configuration.h"

#if EFI_SUPPORT_FORD_ASPIRE || defined(__DOXYGEN__)

/**
 * Just the default RPM bin - with TunerStudio you can adjust even the bins
 */

static float default_fuel_maf_bins[FUEL_LOAD_COUNT] = {/*0*/ 1.200000,
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
static float default_fuel_table[FUEL_LOAD_COUNT][FUEL_RPM_COUNT] = {
/* RPM					800.000000	1213.333374	1626.666748	2040.000000	2453.333496	2866.666748	3280.000000	3693.333496	4106.666992	4520.000000	4933.333496	5346.666992	5760.000000	6173.333496	6586.666992	7000.000000*/
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

static float default_timing_maf_table[AD_LOAD_COUNT] = {/*0*/ 1.200000,
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
static float default_timing_rpm_table[AD_RPM_COUNT] = {/*0*/ 800.000000,
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

static float default_timing_table[AD_LOAD_COUNT][AD_RPM_COUNT] = {
/* RPM					800.000000	1213.333374	1626.666748	2040.000000	2453.333496	2866.666748	3280.000000	3693.333496	4106.666992	4520.000000	4933.333496	5346.666992	5760.000000	6173.333496	6586.666992	7000.000000*/
/* Load 1.200000 */{	0.662000,	-7.730000,	-16.722000,	-23.139999,	-29.398001,	-31.268000,	-32.108002,	-30.436001,	-30.896000,	-26.656000,	-24.704000,	-25.108000,	-25.132000,	-25.459999,	-25.459999,	-25.459999},
/* Load 1.413333 */{	0.546000,	-7.662000,	-16.882000,	-23.482000,	-29.520000,	-31.323999,	-32.108002,	-30.656000,	-30.468000,	-26.879999,	-24.746000,	-24.742001,	-29.032000,	-25.562000,	-25.562000,	-25.562000},
/* Load 1.626667 */{	0.584000,	-7.870000,	-16.714001,	-23.025999,	-29.542000,	-31.166000,	-32.175999,	-30.540001,	-30.268000,	-26.416000,	-24.134001,	-25.007999,	-24.698000,	-26.167999,	-26.167999,	-26.167999},
/* Load 1.840000 */{	0.584000,	-7.658000,	-16.714001,	-23.254000,	-29.351999,	-30.978001,	-32.141998,	-30.874001,	-30.896000,	-26.507999,	-24.558001,	-24.389999,	-25.761999,	-35.492001,	-35.492001,	-35.492001},
/* Load 2.053333 */{	0.584000,	-7.862000,	-16.538000,	-23.254000,	-29.232000,	-31.296000,	-32.520000,	-30.142000,	-30.388000,	-25.903999,	-24.370001,	-24.082001,	-24.792000,	-24.351999,	-24.351999,	-24.351999},
/* Load 2.266667 */{	-1.364000,	-7.726000,	-16.806000,	-23.254000,	-29.639999,	-31.006001,	-32.298000,	-30.912001,	-29.882000,	-26.392000,	-24.664000,	-27.233999,	-25.374001,	-25.417999,	-25.417999,	-25.417999},
/* Load 2.480000 */{	1.364000,	-10.490000,	-16.705999,	-22.441999,	-28.101999,	-30.238001,	-32.363998,	-30.719999,	-30.896000,	-26.608000,	-24.664000,	-24.431999,	-24.500000,	-25.510000,	-25.510000,	-25.510000},
/* Load 2.693333 */{	9.864000,	-10.416000,	-11.680000,	-19.150000,	-25.754000,	-27.936001,	-32.554001,	-30.656000,	-30.153999,	-27.184000,	-25.252001,	-22.812000,	-24.452000,	-25.219999,	-25.219999,	-25.219999},
/* Load 2.906667 */{	9.866000,	5.452000,	2.854000,	-17.212000,	-17.552000,	-20.688000,	-25.660000,	-27.809999,	-27.691999,	-27.224001,	-25.882000,	-25.360001,	-26.100000,	-27.992001,	-27.992001,	-27.992001},
/* Load 3.120000 */{	9.864000,	5.452000,	2.854000,	-0.342000,	-12.526000,	-16.218000,	-21.364000,	-27.590000,	-25.780001,	-24.170000,	-24.664000,	-25.584000,	-26.490000,	-31.968000,	-31.968000,	-31.968000},
/* Load 3.333333 */{	9.864000,	5.516000,	2.854000,	-0.226000,	-2.738000,	-3.816000,	-11.924000,	-18.808001,	-21.038000,	-21.538000,	-21.209999,	-22.228001,	-25.046000,	-25.156000,	-25.156000,	-25.156000},
/* Load 3.546667 */{	9.866000,	5.518000,	2.854000,	0.000000,	-3.022000,	-3.816000,	-6.428000,	-7.788000,	-19.426001,	-20.860001,	-19.966000,	-21.030001,	-21.396000,	-21.570000,	-21.570000,	-21.570000},
/* Load 3.760000 */{	9.864000,	5.516000,	2.772000,	-0.226000,	-2.732000,	-3.500000,	-6.798000,	-8.102000,	-8.660000,	-9.500000,	-11.788000,	-20.132000,	-20.072001,	-20.510000,	-20.510000,	-20.510000},
/* Load 3.973333 */{	9.864000,	5.518000,	2.854000,	0.000000,	-2.880000,	-3.816000,	-6.420000,	-8.320000,	-8.426000,	-8.532000,	-11.470000,	-11.442000,	-13.610000,	-12.022000,	-12.022000,	-12.022000},
/* Load 4.186667 */{	9.750000,	5.518000,	2.604000,	0.000000,	-2.880000,	-3.654000,	-6.050000,	-6.888000,	-8.372000,	-9.364000,	-11.764000,	-11.732000,	-11.864000,	-12.376000,	-12.376000,	-12.376000},
/* Load 4.400000 */{	0.350000,	5.590000,	0.502000,	0.910000,	0.864000,	0.954000,	1.324000,	-7.436000,	1.170000,	1.054000,	2.058000,	2.098000,	2.636000,	-12.352000,	-12.352000,	-12.352000}
};

static void configureAspireEngineEventHandler(engine_configuration_s *e,
		engine_configuration2_s *engineConfiguration2, trigger_shape_s * s, EventHandlerConfiguration *config) {

	resetEventList(&config->crankingInjectionEvents);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_1_OUTPUT), x);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_2_OUTPUT), x);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_3_OUTPUT), x);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_4_OUTPUT), x);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_1_OUTPUT), x + 180);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_2_OUTPUT), x + 180);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_3_OUTPUT), x + 180);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_4_OUTPUT), x + 180);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_1_OUTPUT), x + 360);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_2_OUTPUT), x + 360);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_3_OUTPUT), x + 360);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_4_OUTPUT), x + 360);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_1_OUTPUT), x + 540);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_2_OUTPUT), x + 540);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_3_OUTPUT), x + 540);
//	registerActuatorEventExt(e, s, &config->crankingInjectionEvents, addOutputSignal(INJECTOR_4_OUTPUT), x + 540);

	registerActuatorEvent(&config->crankingInjectionEvents, 1, addOutputSignal(INJECTOR_1_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 1, addOutputSignal(INJECTOR_2_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 1, addOutputSignal(INJECTOR_3_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 1, addOutputSignal(INJECTOR_4_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 3, addOutputSignal(INJECTOR_1_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 3, addOutputSignal(INJECTOR_2_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 3, addOutputSignal(INJECTOR_3_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 3, addOutputSignal(INJECTOR_4_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 6, addOutputSignal(INJECTOR_1_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 6, addOutputSignal(INJECTOR_2_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 6, addOutputSignal(INJECTOR_3_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 6, addOutputSignal(INJECTOR_4_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 8, addOutputSignal(INJECTOR_1_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 8, addOutputSignal(INJECTOR_2_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 8, addOutputSignal(INJECTOR_3_OUTPUT), 0);
	registerActuatorEvent(&config->crankingInjectionEvents, 8, addOutputSignal(INJECTOR_4_OUTPUT), 0);

	addFuelEvents(e, s, config);


//	i = 1;
//	registerActuatorEventExt(e, s, &config->injectionEvents, addOutputSignal(INJECTOR_1_OUTPUT + getCylinderId(e->firingOrder,i ) - 1), x + i * 720 / 4);
//	registerActuatorEventExt(e, s, &config->injectionEvents, addOutputSignal(INJECTOR_4_OUTPUT), x + 360);
//	registerActuatorEventExt(e, s, &config->injectionEvents, addOutputSignal(INJECTOR_2_OUTPUT), x + 540);
//	registerActuatorEvent(&config->injectionEvents, 1, addOutputSignal(INJECTOR_4_OUTPUT), 0);
//	registerActuatorEvent(&config->injectionEvents, 3, addOutputSignal(INJECTOR_2_OUTPUT), 0);
//	registerActuatorEvent(&config->injectionEvents, 6, addOutputSignal(INJECTOR_1_OUTPUT), 0);
//	registerActuatorEvent(&config->injectionEvents, 8, addOutputSignal(INJECTOR_3_OUTPUT), 0);

	float y = -106 + 360;

//	resetEventList(&config->ignitionEvents);
//	registerActuatorEventExt(e, s, &config->ignitionEvents, addOutputSignal(SPARKOUT_1_OUTPUT), 0);
//	registerActuatorEventExt(e, s, &config->ignitionEvents, addOutputSignal(SPARKOUT_1_OUTPUT), 180);
//	registerActuatorEventExt(e, s, &config->ignitionEvents, addOutputSignal(SPARKOUT_1_OUTPUT), 360);
//	registerActuatorEventExt(e, s, &config->ignitionEvents, addOutputSignal(SPARKOUT_1_OUTPUT), 540);

	initializeIgnitionActions(e, engineConfiguration2);
}

static void setDefaultMaps(engine_configuration_s *engineConfiguration) {
	for (int i = 0; i < FUEL_LOAD_COUNT; i++)
		engineConfiguration->fuelLoadBins[i] = default_fuel_maf_bins[i];
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		engineConfiguration->fuelRpmBins[i] = default_fuel_rpm_bins[i];
	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = default_fuel_table[k][r];
		}
	}

	for (int i = 0; i < AD_LOAD_COUNT; i++)
		engineConfiguration->ignitionLoadBins[i] = default_timing_maf_table[i];
	for (int i = 0; i < AD_RPM_COUNT; i++)
		engineConfiguration->ignitionRpmBins[i] = default_timing_rpm_table[i];

	for (int k = 0; k < AD_LOAD_COUNT; k++) {
		for (int r = 0; r < AD_RPM_COUNT; r++) {
			engineConfiguration->ignitionTable[k][r] = default_timing_table[k][r];
		}
	}
}

void setFordAspireEngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->tpsMin = 1;
	engineConfiguration->tpsMax = 1000;

	engineConfiguration->rpmHardLimit = 7000;

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, -20, 18000, 23.8889, 2100, 48.8889, 1000);
	engineConfiguration->cltThermistorConf.bias_resistor = 3300; // that's my custom resistor value!

	engineConfiguration->crankingSettings.coolantTempMaxC = 65; // 8ms at 65C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 8;

	engineConfiguration->crankingSettings.coolantTempMinC = 0; // 20ms at 0C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 20;

//	engineConfiguration->ignitionPinMode = OM_INVERTED;

	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;
	engineConfiguration->globalTriggerAngleOffset = 175;
	engineConfiguration->ignitionOffset = 269;
	engineConfiguration->injectionOffset = 254 - 20;
	engineConfiguration->triggerShapeSynchPointIndex = 4;

	setDefaultMaps(engineConfiguration);
	engineConfiguration->crankingSettings.crankingRpm = 550;
	engineConfiguration->crankingChargeAngle = 65;
	engineConfiguration->crankingTimingAngle = -149;

	for (int i = 0; i < DWELL_CURVE_SIZE; i++) {
		engineConfiguration->sparkDwellBins[i] = 0;
		engineConfiguration->sparkDwell[i] = -1;
	}

	engineConfiguration->sparkDwellBins[5] = 1;
	engineConfiguration->sparkDwell[5] = 4;

	engineConfiguration->sparkDwellBins[6] = 4500;
	engineConfiguration->sparkDwell[6] = 4;

	engineConfiguration->sparkDwellBins[7] = 12500;
	engineConfiguration->sparkDwell[7] = 0;

	engineConfiguration->triggerConfig.triggerType = TT_FORD_ASPIRE;
	engineConfiguration->triggerConfig.isSynchronizationNeeded = FALSE;

	engineConfiguration->HD44780width = 20;
	engineConfiguration->HD44780height = 4;

	engineConfiguration->tpsAdcChannel = 3; // 15 is the old value
	engineConfiguration->vBattAdcChannel = 0; // 1 is the old value
//	engineConfiguration->map.channel = 1;
	engineConfiguration->mafAdcChannel = 1;
	engineConfiguration->cltAdcChannel = 11;
//	engineConfiguration->iatAdcChannel =

	engineConfiguration->map.config.mapType = MT_DENSO183;
}

void setFordAspireengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {


	configureAspireEngineEventHandler(engineConfiguration,
			engineConfiguration2,

			&engineConfiguration2->triggerShape,

			&engineConfiguration2->engineEventConfiguration);
}

#endif /* EFI_SUPPORT_FORD_ASPIRE */
