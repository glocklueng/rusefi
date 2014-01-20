/**
 * @file	advance_map.c
 *
 * @date Mar 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "advance_map.h"
#include "interpolation.h"
// that's for 'max' function
#include "idle_controller.h"

#include "engine_controller.h"

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

static float *timing_ptrs[AD_LOAD_COUNT];
static int initialized = FALSE;

float getBaseAdvance(int rpm, float key) {
	chDbgAssert(initialized, "fuel map initialized", NULL);
	return interpolate3d(key, engineConfiguration->ignitionLoadBins, AD_LOAD_COUNT, rpm,
			engineConfiguration->ignitionRpmBins,
			AD_RPM_COUNT, timing_ptrs);
}

float getAdvance(int rpm, float key) {
	if (isCrankingR(rpm))
		return engineConfiguration->crankingChargeAngle;

	return getBaseAdvance(rpm, key) + engineConfiguration->ignitonOffset;
}

void prepareTimingMap(void) {
	for (int k = 0; k < FUEL_LOAD_COUNT; k++)
		timing_ptrs[k] = engineConfiguration->fuelTable[k];
	initialized = TRUE;
}
