#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "engine_math.h"

myfloat getMap(void) {
	float volts = getVoltage(ADC_LOGIC_MAP);

	return getMAPValueHonda_Denso183(volts);
}
