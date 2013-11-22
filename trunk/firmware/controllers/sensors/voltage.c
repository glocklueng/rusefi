#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "adc_inputs.h"

myfloat getVRef(void) {
//	return getAdcValue(ADC_CHANNEL_VREF);
	return getVoltage(ADC_CHANNEL_VREF);
}

myfloat getVBatt(void) {
	return 12; // todo: take it from ADC
}
