/**
 * @file    voltage.c
 * @brief
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "adc_inputs.h"

extern engine_configuration_s *engineConfiguration;

myfloat getVRef(void) {
//	return getAdcValue(ADC_CHANNEL_VREF);
	return getVoltageDivided(ADC_CHANNEL_VREF);
}

myfloat getVBatt(void) {
	return getVoltage(ADC_CHANNEL_VBATT) * engineConfiguration->vbattDividerCoeff;
}
