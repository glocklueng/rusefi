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

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

static float *timing_ptrs[AD_LOAD_COUNT];
static int initialized = FALSE;

float getBaseAdvance(int rpm, float engineLoad) {
	chDbgAssert(initialized, "fuel map initialized", NULL);
	return interpolate3d(engineLoad, engineConfiguration->ignitionLoadBins, AD_LOAD_COUNT, rpm,
			engineConfiguration->ignitionRpmBins,
			AD_RPM_COUNT, timing_ptrs);
}

float getAdvance(int rpm, float engineLoad) {
	if (isCrankingR(rpm))
		return engineConfiguration->crankingChargeAngle;

	return getBaseAdvance(rpm, engineLoad) + engineConfiguration->ignitonOffset;
}

void prepareTimingMap(void) {
	for (int k = 0; k < FUEL_LOAD_COUNT; k++)
		timing_ptrs[k] = engineConfiguration->fuelTable[k];
	initialized = TRUE;
}
