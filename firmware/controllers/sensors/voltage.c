/**
 * @file    voltage.c
 * @brief
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "adc_inputs.h"

extern EngineConfiguration *engineConfiguration;

myfloat getVRef(void) {
//	return getAdcValue(ADC_CHANNEL_VREF);
	return getVoltageDivided(ADC_CHANNEL_VREF);
}

myfloat getVBatt(void) {
	return 12; // todo: take it from ADC
}
