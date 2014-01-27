/**
 * @file	engine_configuration.h
 * @brief	Main engine configuration data structure.
 *
 * @date Oct 30, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_CONFIGURATION_H_
#define ENGINE_CONFIGURATION_H_

#include "features.h"
#include "fuel_map.h"
#include "sensor_types.h"
#include "engine_math.h"
#include "can_header.h"
#include "trigger_structure.h"
#include "event_registry.h"
#include "rusefi_enums.h"

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
	/**
	 * This is the default mode in which ECU controls timing dynamically
	 */
	TM_DYNAMIC = 0,
	/**
	 * Fixed timing is useful while you are playing with a timing gun - you need to have fixed
	 * timing if you want to install your distributor at some specific angle
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

	cranking_parameters_s crankingSettings;

	map_s map;

	ThermistorConf cltThermistorConf; // size 40 (10*4), offset 336
	ThermistorConf iatThermistorConf; // size 40, offset 376

	float ignitionDwellBins[DWELL_COUNT]; // offset 580
	float ignitionDwell[DWELL_COUNT];

	float ignitionTable[IGN_LOAD_COUNT][IGN_RPM_COUNT];
	float ignitionLoadBins[IGN_LOAD_COUNT]; // offset 3450
	float ignitionRpmBins[IGN_RPM_COUNT]; // offset 3542

	/**
	 * this value could be used to offset the whole ignition timing table by a constant
	 */
	float ignitonOffset;

	/**
	 * While cranking (which causes battery voltage to drop) we can calculate dwell time in shaft
	 * degrees, not in absolute time as in running mode.
	 */
	float crankingChargeAngle;

	timing_mode_e timingMode;
	/**
	 * This value is used in 'fixed timing' mode, i.e. constant timing
	 * This mode is useful for instance while adjusting distributor location
	 */
	float fixedModeTiming;

	// WARNING: by default, our small enums are ONE BYTE. but if the are surrounded by non-enums - alignments do the trick
	engine_type_e engineType;


	float fuelTable[FUEL_LOAD_COUNT][FUEL_RPM_COUNT]; // size 1024, offset 1816
	float fuelLoadBins[FUEL_LOAD_COUNT]; // offset 2840
	// RPM is float and not integer in order to use unified methods for interpolation
	float fuelRpmBins[FUEL_RPM_COUNT]; // offset 3542

	// WARNING: by default, our small enums are ONE BYTE. this one is made 4-byte with the 'ENUM_SIZE_HACK' hack
	pin_output_mode_e injectionPinMode;
	pin_output_mode_e ignitionPinMode;
	pin_output_mode_e idlePinMode;
	pin_output_mode_e fuelPumpPinMode;
	pin_output_mode_e malfunctionIndicatorPinMode;

	/**
	 * This is the angle between Top Dead Center (TDC) and the first trigger event.
	 * Knows this angle allows us to control timing and other angles in reference to TDC.
	 */
	float globalTriggerOffsetAngle;
	/**
	 * We have 3.3V ADC and most of the analog input signals are 5V, this forces us to use
	 * voltage dividers on the input circuits. This parameter holds the coefficient of these dividers.
	 */
	float analogInputDividerCoefficient;

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

	cranking_ignition_mode_e crankingIgnitionMode;

	EventHandlerConfiguration engineEventConfiguration;
} EngineConfiguration2;

char* getConfigurationName(EngineConfiguration *engineConfiguration);
void setDefaultConfiguration(EngineConfiguration *engineConfiguration);
void setDefaultNonPersistentConfiguration(EngineConfiguration2 *engineConfiguration2);
void printConfiguration(EngineConfiguration *engineConfiguration, EngineConfiguration2 *engineConfiguration2);
void printFloatArray(char *prefix, float array[], int size);

#endif /* ENGINE_CONFIGURATION_H_ */
