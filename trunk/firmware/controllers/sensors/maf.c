#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "adc_inputs.h"

extern engine_configuration_s *engineConfiguration;

myfloat getMaf(void) {
	return getVoltageDivided(ADC_LOGIC_MAF);
}
