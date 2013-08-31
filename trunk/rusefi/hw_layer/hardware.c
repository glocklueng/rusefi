/*
 * hardware.c
 *
 *  Created on: May 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    hardware.c
 * @brief   Hardware package entry point
 */

#include "hardware.h"
#include "pin_repository.h"
#include "output_pins.h"

#include "adc_inputs.h"

#include "crank_input.h"
#include "mcp3208.h"


McpAdcState adcState;

void initHardware() {
	// todo: enable protection. it's disabled because it takes
	// 10 extra seconds to re-flash the chip
	//flashProtect();

	initPinRepository();

	initOutputPins();
	initAdcInputs();

	init_adc_mcp3208(&adcState, &SPID2);
	requestAdcValue(&adcState, 0);

	initInputCapture();
//	initFixedLeds();

	//	initBooleanInputs();

#if ADC_SNIFFER
	initAdcDriver();
#endif
}
