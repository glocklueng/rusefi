#include "main.h"
#include "engine_configuration.h"
#include "engine_math.h"
#include "boards.h"
#include "adc_inputs.h"

myfloat getAfr(void) {
	myfloat volts = getVoltage(ADC_LOGIC_AFR);

	/**
	 * This decodes BPSX D1 Wideband Controller analog signal
	 */
	return interpolate(0, 9, 5, 19, volts);
}
