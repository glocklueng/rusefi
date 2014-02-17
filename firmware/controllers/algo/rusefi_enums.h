/**
 * @file	rusefi_enums.h
 * @brief	Fundamental rusEfi enumerable types live here
 *
 * @note this file should probably not include any other files
 *
 * @date Jan 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RUSEFI_ENUMS_H_
#define RUSEFI_ENUMS_H_

// for now I want all enums to be 32 bit integers. At some point maybe we will make the one-byte
// this is about offsets and sizes in TunerStudio
#define ENUM_SIZE_HACK 2000000000

/**
 * This enum is used to select your desired Engine Load calculation algorithm
 */
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
	 * raw Manifold Absolute Pressure sensor value is used as engine load http://en.wikipedia.org/wiki/MAP_sensor
	 */
	LM_MAP = 2,
	/**
	 * Speed Density algorithm - Engile Load is a function of MAP and ... TODO
	 * http://articles.sae.org/8539/
	 */
	LM_SPEED_DENSITY = 3,

	Internal_ForceMyEnumIntSize_engine_load_mode = ENUM_SIZE_HACK,
} engine_load_mode_e;

typedef enum {
	DM_NONE = 0,
	DM_HD44780 = 1,
	DM_HD44780_OVER_PCF8574 = 2,

	Internal_ForceMyEnumIntSize_display_mode = ENUM_SIZE_HACK,

} display_mode_e;

typedef enum {
	LF_NATIVE = 0,
	/**
	 * http://www.efianalytics.com/MegaLogViewer/
	 * log example: http://svn.code.sf.net/p/rusefi/code/trunk/misc/ms_logs/
	 */
	LM_MLV = 1,

	Internal_ForceMyEnumIntSize_log_format = ENUM_SIZE_HACK,
} log_format_e;

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
	FO_ONE_CYLINDER = 1,
	FO_1_THEN_3_THEN_4_THEN2 = 2,
	FO_1_THEN_2_THEN_4_THEN3 = 3,
	FO_1_THEN_3_THEN_2_THEN4 = 4,
	FO_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4 = 5,
	Internal_ForceMyEnumIntSize_firing_order = ENUM_SIZE_HACK,
} firing_order_e;

/**
 * @brief Ignition Mode
 */
typedef enum {
	IM_ONE_COIL = 0,
	IM_INDIVIDUAL_COILS = 1,

	Internal_ForceMyEnumIntSize_ignition_mode = ENUM_SIZE_HACK,
} ignition_mode_e;

/**
 * @brief Ignition Mode while cranking
 */
typedef enum {
	CIM_DEFAULT = 0,
	CIM_FIXED_ANGLE = 1,

	Internal_ForceMyEnumIntSize_cranking_ignition_mode = ENUM_SIZE_HACK,
} cranking_ignition_mode_e;

#endif /* RUSEFI_ENUMS_H_ */
