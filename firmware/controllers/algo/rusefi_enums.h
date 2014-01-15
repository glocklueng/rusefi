/**
 * @file	rusefi_enums.h
 *
 * @date Jan 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RUSEFI_ENUMS_H_
#define RUSEFI_ENUMS_H_

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
} pin_output_mode_e;

#endif /* RUSEFI_ENUMS_H_ */
