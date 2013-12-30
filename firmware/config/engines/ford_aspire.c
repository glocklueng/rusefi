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
#include "main_loop.h"

#ifdef EFI_SUPPORT_FORD_ASPIRE

/**
 * Just the default RPM bin - with TunerStudio you can adjust even the bins
 */
static float default_fuel_rpm_bins[FUEL_RPM_COUNT] = {/*0*/400.0, /*1*/650.0, /*2*/900.0, /*3*/1150.0, /*4*/1400.0, /*5*/1650.0, /*6*/1900.0, /*7*/
2150.0, /*8*/2400.0, /*9*/2650.0, /*10*/2900.0, /*11*/3150.0, /*12*/3400.0, /*13*/3650.0, /*14*/3900.0, /*15*/
4150.0, /*16*/4400.0, /*17*/4650.0, /*18*/4900.0, /*19*/5150.0, /*20*/5400.0, /*21*/5650.0, /*22*/5900.0 };

static float default_fuel_maf_bins[FUEL_MAF_COUNT] = {/*0*/1.2000000476837158, /*1*/1.300000047683716, /*2*/1.400000047683716, /*3*/
1.500000047683716, /*4*/1.6000000476837162, /*5*/1.7000000476837163, /*6*/1.8000000476837164, /*7*/
1.9000000476837164, /*8*/2.0000000476837165, /*9*/2.1000000476837166, /*10*/2.2000000476837167, /*11*/
2.300000047683717, /*12*/2.400000047683717, /*13*/2.500000047683717, /*14*/2.600000047683717, /*15*/
2.700000047683717, /*16*/2.8000000476837172, /*17*/2.9000000476837173, /*18*/3.0000000476837174, /*19*/
3.1000000476837175, /*20*/3.2000000476837176, /*21*/3.3000000476837177, /*22*/3.4000000476837178, /*23*/
3.500000047683718, /*24*/3.600000047683718, /*25*/3.700000047683718, /*26*/3.800000047683718, /*27*/
3.900000047683718, /*28*/4.000000047683718, /*29*/4.100000047683718, /*30*/4.200000047683718, /*31*/
4.300000047683717, /*32*/4.400000047683717 };

/**
 * This is just the default map which is stored into flash memory in case flash is empty
 * The convenient way to override these default would be to tune this map using TunerStudio software
 * with which rusEfi is integrated
 */
static float default_fuel_table[FUEL_RPM_COUNT][FUEL_MAF_COUNT] = {
	/*	Load		1.2		1.3		1.4		1.5		1.6		1.7		1.8		1.9		2.0		2.1		2.2		2.3		2.4		2.5		2.6		2.7		2.8		2.9		3.0		3.1		3.2		3.3		3.4		3.5		3.6		3.7		3.8		3.9		4.0		4.1		4.2		4.3		4.4	*/
	/* RPM__400 */ {1.55,	1.55,	1.52,	1.54,	1.58,	1.52,	1.53,	4.03,	6.55,	8.13,	13.69,	16.14,	16.35,	25.07,	25.11,	25.13,	25.12,	25.09,	25.09,	25.13,	25.1,	25.12,	25.12,	25.12,	25.14,	25.12,	25.1,	25.12,	25.11,	24.39,	24.06,	23.21,	22.55	},
	/* RPM__650 */ {1.53,	1.55,	1.54,	1.52,	1.52,	1.52,	1.52,	1.54,	1.53,	1.54,	6.01,	10.64,	11.93,	18.35,	17.72,	22.67,	21.79,	21.12,	20.25,	19.4,	18.7,	18.29,	17.68,	17.14,	16.98,	16.98,	16.97,	16.92,	17.01,	16.97,	16.92,	16.97,	17.01	},
	/* RPM__900 */ {1.55,	1.57,	1.53,	1.52,	1.57,	1.53,	1.55,	1.54,	2.72,	2.96,	3.17,	8.56,	8.77,	13.44,	14.77,	21.12,	20.03,	19.38,	18.57,	17.67,	17.32,	16.97,	16.96,	16.97,	16.96,	17.03,	16.95,	17.02,	16.95,	17.02,	16.98,	17.01,	16.97	},
	/* RPM_1150 */ {1.54,	1.58,	1.57,	1.54,	1.54,	1.54,	1.55,	2.05,	3.18,	4.01,	5.17,	6.92,	8.35,	10.01,	13.76,	17.3,	16.48,	15.84,	15.27,	15.26,	15.28,	15.26,	15.26,	15.27,	15.25,	15.27,	15.25,	15.23,	15.22,	15.28,	15.26,	15.22,	15.25	},
	/* RPM_1400 */ {1.57,	1.54,	1.57,	1.52,	1.57,	1.54,	1.55,	1.97,	2.88,	2.92,	2.92,	5.8,	5.86,	5.86,	11.1,	10.52,	18.84,	17.88,	16.86,	16.14,	15.71,	15.68,	15.68,	15.72,	15.68,	15.65,	15.67,	15.72,	15.69,	15.68,	15.68,	15.69,	15.68	},
	/* RPM_1650 */ {1.55,	1.55,	1.55,	1.55,	1.55,	1.57,	1.55,	1.53,	2.33,	3.23,	3.88,	5.09,	6.63,	6.63,	6.57,	11.31,	10.93,	17.22,	16.14,	15.63,	15.22,	15.11,	15.19,	15.14,	15.13,	15.15,	15.1,	15.5,	15.18,	15.11,	15.17,	15.19,	15.17	},
	/* RPM_1900 */ {1.57,	1.53,	1.57,	1.55,	1.54,	1.54,	1.55,	1.69,	2.13,	2.68,	3.44,	4.46,	5.34,	5.36,	5.34,	9.63,	9.4,	17.94,	16.8,	15.9,	15.35,	15.52,	15.44,	15.38,	15.43,	15.42,	15.43,	15.43,	15.39,	15.39,	15.43,	15.44,	15.44	},
	/* RPM_2150 */ {1.57,	1.54,	1.54,	1.55,	1.54,	1.58,	1.54,	1.64,	2.1,	2.1,	3.07,	4.0,	5.23,	5.69,	6.88,	8.44,	10.4,	13.64,	16.37,	15.06,	15.19,	15.21,	15.23,	15.18,	15.18,	15.18,	15.22,	15.22,	15.19,	15.22,	15.18,	15.22,	15.22	},
	/* RPM_2400 */ {1.55,	1.55,	1.57,	1.58,	1.57,	1.55,	1.57,	1.55,	1.85,	2.42,	2.79,	3.6,	4.34,	5.69,	5.71,	5.65,	9.22,	11.52,	12.56,	12.05,	12.14,	15.25,	15.23,	15.3,	15.25,	15.27,	15.3,	15.27,	15.22,	15.25,	15.19,	15.31,	15.27	},
	/* RPM_2650 */ {1.55,	1.57,	1.55,	0.82,	0.87,	0.85,	0.0,	0.0,	1.75,	2.26,	2.23,	2.26,	4.01,	4.0,	3.99,	6.84,	8.43,	8.39,	11.44,	16.5,	15.88,	15.56,	15.5,	15.47,	15.55,	15.48,	15.5,	15.42,	15.52,	15.48,	15.51,	15.53,	15.47	},
	/* RPM_2900 */ {0.81,	0.8,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.0,	2.42,	2.43,	2.42,	4.84,	4.8,	4.79,	7.63,	7.65,	7.61,	13.02,	12.28,	15.27,	15.55,	15.5,	15.65,	15.72,	15.71,	15.38,	15.52,	15.63,	15.46,	15.59,	15.59	},
	/* RPM_3150 */ {0.8,	0.79,	0.81,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	1.91,	1.89,	2.86,	3.43,	4.05,	4.07,	5.84,	7.03,	7.73,	7.69,	7.71,	7.71,	16.63,	15.55,	15.47,	15.8,	15.81,	15.79,	15.77,	15.85,	15.81,	15.81,	15.86,	15.8	},
	/* RPM_3400 */ {0.79,	0.81,	0.81,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.2,	2.48,	2.47,	2.51,	4.57,	4.55,	4.55,	4.61,	8.56,	9.51,	11.93,	12.81,	12.81,	15.76,	15.53,	15.84,	15.81,	15.97,	16.04,	15.8,	15.85,	15.68,	16.12	},
	/* RPM_3650 */ {0.77,	0.8,	0.78,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.54,	3.0,	3.57,	4.28,	4.32,	6.13,	7.44,	8.17,	8.97,	8.93,	12.06,	11.96,	15.31,	15.79,	15.71,	15.75,	15.77,	15.85,	15.82,	15.84,	15.76,	15.73	},
	/* RPM_3900 */ {0.8,	0.79,	0.81,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	1.99,	2.39,	2.8,	2.78,	4.05,	4.82,	4.73,	6.94,	7.55,	8.39,	10.25,	11.09,	12.43,	14.85,	14.85,	15.6,	15.52,	15.55,	15.55,	15.61,	15.64,	15.6,	15.6	},
	/* RPM_4150 */ {0.79,	0.8,	0.81,	0.8,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	1.91,	2.31,	2.92,	2.9,	4.19,	4.51,	4.57,	6.61,	6.57,	7.88,	7.88,	10.5,	11.61,	11.76,	15.22,	16.0,	15.81,	15.65,	15.71,	15.73,	15.68,	15.69,	15.81	},
	/* RPM_4400 */ {0.8,	0.79,	0.79,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	1.86,	2.23,	2.21,	3.04,	3.65,	3.64,	5.19,	6.34,	6.23,	6.21,	6.13,	10.07,	11.03,	12.26,	12.22,	12.27,	15.93,	15.57,	16.0,	15.86,	15.89,	15.93,	15.79	},
	/* RPM_4650 */ {0.8,	0.8,	0.8,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	1.8,	2.16,	2.5,	2.88,	3.49,	3.47,	3.47,	5.92,	5.9,	7.09,	8.6,	9.5,	9.46,	9.43,	9.55,	15.86,	15.79,	15.85,	15.76,	15.72,	15.77,	16.0,	15.97	},
	/* RPM_4900 */ {0.8,	0.8,	0.79,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.06,	2.07,	2.76,	2.74,	3.97,	4.76,	5.67,	5.67,	5.61,	5.59,	9.06,	8.98,	10.97,	12.25,	14.48,	14.77,	16.1,	16.11,	16.11,	15.98,	16.13,	16.12	},
	/* RPM_5150 */ {0.79,	0.8,	0.81,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.01,	2.31,	2.9,	3.48,	3.44,	4.51,	4.53,	5.88,	7.09,	7.82,	8.65,	9.48,	10.56,	11.77,	13.94,	15.28,	16.22,	16.23,	16.23,	15.96,	16.27,	16.11	},
	/* RPM_5400 */ {0.81,	0.81,	0.79,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	1.91,	1.95,	2.55,	3.03,	3.07,	3.0,	4.75,	5.65,	6.21,	6.11,	8.31,	8.31,	10.1,	11.03,	11.14,	11.14,	11.18,	16.03,	16.01,	16.04,	15.86,	15.97	},
	/* RPM_5650 */ {0.81,	0.8,	0.8,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.14,	2.69,	2.69,	3.49,	4.15,	4.94,	4.9,	5.94,	7.21,	8.01,	7.96,	7.96,	11.85,	12.06,	13.11,	12.86,	15.65,	15.72,	15.75,	15.65,	15.63	},
	/* RPM_5900 */ {0.81,	0.8,	0.81,	0.81,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	2.42,	2.78,	3.34,	4.03,	4.01,	3.97,	5.73,	6.86,	6.9,	6.92,	9.23,	9.31,	9.23,	12.56,	14.61,	15.22,	15.19,	15.13,	15.17,	15.15	}
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
			// todo: this is BAD, this needs to be fixed - TS table indexes are different from default indexes
			engineConfiguration->fuelTable[k][r] = default_fuel_table[r][k];
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
