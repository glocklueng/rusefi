
#include "main.h"
#include "boards.h"
#include "engine_configuration.h"

extern EngineConfiguration2 engineConfiguration2;

int getTpsValue(myfloat volts) {
	if (volts <= engineConfiguration2.tps_idle)
		return 0;
	if (volts >= engineConfiguration2.tps_wot)
		return 100;
	// todo: replace with 'interpolate' function invocation
	return (int) (100 * (volts - engineConfiguration2.tps_idle) / (engineConfiguration2.tps_wot - engineConfiguration2.tps_idle));
}

myfloat getTPS(void) {
	// blue, 1st board
	/* PA7 - blue TP */
	int tpsValue = getTpsValue(getVoltage(ADC_LOGIC_TPS));
	return tpsValue;
}
