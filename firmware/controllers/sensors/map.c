#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "engine_math.h"

myfloat getMap(void) {
	int adc0 = getAdcValue(ADC_LOGIC_MAP);
	float volts = adcToVolts(adc0);

	return getMAPValueHonda_Denso183(volts);
}
