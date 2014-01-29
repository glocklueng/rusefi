/**
 * @file	rusefi_enums.h
 *
 * @date Jan 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RUSEFI_ENUMS_H_
#define RUSEFI_ENUMS_H_

// for now I want all enums to be 32 bit integers. At some point maybe we will make the one-byte
// this is about offsets and sizes in TunerStudio
#define ENUM_SIZE_HACK 2000000000

typedef enum {
	/**
	 * raw Mass Air Flow sensor value algorithm. http://en.wikipedia.org/wiki/Mass_flow_sensor
	 */
	LM_MAF = 0,
	/**
	 * Throttle Position Sensor value is used as engine load. http://en.wikipedia.org/wiki/Throttle_position_sensor
	 * That's know as Alpha N
	 */
	LM_TPS = 1,
	/**
	 * Manifold Absolute Pressure sensor value is used as engine load http://en.wikipedia.org/wiki/MAP_sensor
	 * For now this is just
	 * TODO: speed density - maybe separate algorith? Maybe
	 */
	LM_MAP = 2,

	Internal_ForceMyEnumIntSize_engine_load_mode = ENUM_SIZE_HACK,
} engine_load_mode_e;

typedef enum {
	/**
	 * GND for logical OFF, VCC for logical ON
	 */
	OM_DEFAULT = 0,
	/**
	 * GND for logical ON, VCC for logical OFF
	 */
	OM_INVERTED = 1,
	OM_OPENDRAIN = 2,
	OM_OPENDRAIN_INVERTED = 3,

	Internal_ForceMyEnumIntSize_pin_output_mode = ENUM_SIZE_HACK,
} pin_output_mode_e;


typedef enum {
	CIM_DEFAULT = 0,
	CIM_FIXED_ANGLE = 1,

	Internal_ForceMyEnumIntSize_cranking_ignition_mode = ENUM_SIZE_HACK,
} cranking_ignition_mode_e;

#endif /* RUSEFI_ENUMS_H_ */
