/*
 * hardware.c
 *
 *  Created on: May 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "hardware.h"
#include "pin_repository.h"
#include "output_pins.h"

#include "adc_inputs.h"

#include "crank_input.h"


void initHardware() {
	// todo: enable protection. it's disabled because it takes
	// 10 extra seconds to re-flash the chip
	//flashProtect();

	initPinRepository();

	initOutputPins();
	initAdcInputs();

	initInputCapture();
//	initFixedLeds();

	//	initBooleanInputs();

#if ADC_SNIFFER
	initAdcDriver();
#endif
}
