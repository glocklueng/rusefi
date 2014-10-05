/**
 * @file le_functions.cpp
 *
 * @date Oct 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "le_functions.h"
#include "allsensors.h"

extern LENameOrdinalPair * LE_FIRST;

static LENameOrdinalPair leRpm(LE_METHOD_RPM, "rpm");
static LENameOrdinalPair leFan(LE_METHOD_FAN, "fan");
static LENameOrdinalPair leCoolant(LE_METHOD_COOLANT, "coolant");
static LENameOrdinalPair leFanOnSetting(LE_METHOD_FAN_ON_SETTING, "fan_on_setting");
static LENameOrdinalPair leFanOffSetting(LE_METHOD_FAN_OFF_SETTING, "fan_off_setting");


#if EFI_PROD_CODE || EFI_SIMULATOR
float getLEValue(Engine *engine, le_action_e action) {
	switch(action) {
//	case LE_METHOD_FAN:
	//	return ;
	case LE_METHOD_COOLANT:
		return getCoolantTemperature(engine->engineConfiguration2);
	default:
		firmwareError("No value for %d", action);
		return NAN;
	}
}
#endif
