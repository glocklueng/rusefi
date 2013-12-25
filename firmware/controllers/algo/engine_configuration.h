/**
 * @file	engine_configuration.h
 * @brief	Main engine configuration data structure.
 *
 * @date Oct 30, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_CONFIGURATION_H_
#define ENGINE_CONFIGURATION_H_

#include "fuel_map.h"
#include "allsensors.h"
#include "engine_math.h"
#include "can_header.h"
#include "trigger_structure.h"
#include "event_registry.h"

typedef enum {
	AUDI_AAN = 1,
	DODGE_NEON_1995 = 2,
	/**
	 * 1996 1.3 Ford Aspire
	 * http://rusefi.com/forum/viewtopic.php?t=375
	 */
	FORD_ASPIRE_1996 = 3,
	FORD_FIESTA = 4,
	NISSAN_PRIMERA = 5,
} engine_type_e;

/**
 * @brief Here we store information about which injector or spark should be fired when.
 */
typedef struct {
	ActuatorEventList crankingInjectionEvents;
	ActuatorEventList injectionEvents;
	ActuatorEventList ignitionEvents;
} EventHandlerConfiguration;


#define CLT_CURVE_SIZE 16
#define IAT_CURVE_SIZE 16
#define VBAT_INJECTOR_CURVE_SIZE 8

#define IGN_LOAD_COUNT 16
#define IGN_RPM_COUNT 16

typedef enum {
	AC_OFF = 0,
	AC_TRIGGER = 1,
	AC_MAP = 2,
} analog_chart_e;

typedef enum {
	TM_DYNAMIC = 0,
	/**
	 * Fixed timing is useful while you are playing with a timing gun
	 */
	TM_FIXED = 1,
} timing_mode_e;


#define DWELL_COUNT 8
/**
 * @brief	Engine configuration.
 * 		Values in this data structure are adjustable and persisted in on-board flash RAM.
 */
typedef struct {
	float injectorLag;	// size 4, offset 0
	float injectorFlow; // size 4, offset 4
	float battInjectorLagCorrBins[VBAT_INJECTOR_CURVE_SIZE]; // size 32, offset 8
	float battInjectorLagCorr[VBAT_INJECTOR_CURVE_SIZE]; // size 32, offset 40

	float cltFuelCorrBins[CLT_CURVE_SIZE]; // size 64, offset 72
	float cltFuelCorr[CLT_CURVE_SIZE]; // size 64, offset 136

	float iatFuelCorrBins[IAT_CURVE_SIZE]; // size 64, offset 200
	float iatFuelCorr[IAT_CURVE_SIZE]; // size 64, offset 264

	short int rpmHardLimit; // size 2, offset 328

	// todo: extract these two fields into a structure
	// todo: we need two sets of TPS parameters - modern ETBs have to sensors
	short int tpsMin; // size 2, offset 330
	short int tpsMax; // size 2, offset 332
	short int analogChartMode;

	CrankingMode crankingSettings;

	map_s map;

	ThermistorConf cltThermistorConf; // size 40 (10*4), offset 336
	ThermistorConf iatThermistorConf; // size 40, offset 376

	float ignitionDwellBins[DWELL_COUNT];
	float ignitionDwell[DWELL_COUNT];

	float ignitionTable[IGN_LOAD_COUNT][IGN_RPM_COUNT];
	float ignitionKeyBins[IGN_LOAD_COUNT]; // offset 3450
	float ignitionRpmBins[IGN_RPM_COUNT]; // offset 3542

	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT]; // size 3036, offset 414
	float fuelKeyBins[FUEL_MAF_COUNT]; // offset 3450
	// RPM is float and not integer in order to use unified methods for interpolation
	float fuelRpmBins[FUEL_RPM_COUNT]; // offset 3542

	/**
	 * this value could be used to offset the whole ignition timing table by a constant
	 */
	float ignitonOffset;

	/**
	 * While cranking which causes battery voltage we can calculate dwell time in shaft
	 * degrees, not in absolute time as in running mode.
	 */
	int crankingChargeAngle;

	timing_mode_e timingMode;
	/**
	 * This value is used in 'fixed timing' mode, i.e. constant timing
	 * This mode is useful for instance while adjusting distributor location
	 */
	float fixedModeTiming;

	engine_type_e engineType;

} EngineConfiguration;

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
typedef struct {
	int hasMapSensor;
	int hasCltSensor;

	int cylindersCount;

	Thermistor iat;
	Thermistor clt;

	/**
	 * This magic constant is about four-stroke engines with camshaft position sensors.
	 * On any four stroke engine, each revolution of the camshaft is two revolutions
	 * of the crankshaft. If camshaft position is our primary sensor, we use this multiplier
	 * to convert from camshaft angles to crankshaft angles. All angels across the system
	 * should be crankshaft angles.
	 */

	float rpmMultiplier;

	int crankAngleRange;

	can_nbc_e can_nbc_type;
	int can_nbc_broadcast_period;

	trigger_shape_s triggerShape;

	EventHandlerConfiguration engineEventConfiguration;
} EngineConfiguration2;

char* getConfigurationName(EngineConfiguration *engineConfiguration);
void setDefaultConfiguration(EngineConfiguration *engineConfiguration);
void printConfiguration(EngineConfiguration *engineConfiguration, EngineConfiguration2 *engineConfiguration2);
void printFloatArray(char *prefix, float array[], int size);

#endif /* ENGINE_CONFIGURATION_H_ */
