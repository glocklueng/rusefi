#include "main.h"
#include "boards.h"
#include "engine_configuration.h"

myfloat getMaf(void) {
	return getVoltage(ADC_LOGIC_MAF);
}
