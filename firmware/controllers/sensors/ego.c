#include "main.h"
#include "engine_configuration.h"
#include "engine_math.h"

myfloat getAfr(void) {
	myfloat volts = getVoltage(ADC_LOGIC_AFR);

	return interpolate(0, 9, 5, 19, volts);
}
