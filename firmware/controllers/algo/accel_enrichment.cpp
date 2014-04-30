/**
 * @file    accel_enrichment.cpp
 * @brief   Acceleration enrichment calculator
 *
 * @date Apr 21, 2014
 * @author Dmitry Sidin
 * @author Andrey Belomutskiy (c) 2012-2014
 */

#include "main.h"
#include "trigger_central.h"
#include "accel_enrichment.h"
#include "engine_state.h"
#include "engine_math.h"
#include "signal_executor.h"

extern engine_configuration_s *engineConfiguration;
static AccelEnrichmemnt instance;

void AccelEnrichmemnt::updateDiffEnrichment(engine_configuration_s *engineConfiguration, float engineLoad) {
	for (int i = 1; i < 4; i++) {
		engineLoadD[i] = engineLoadD[i - 1];
	}
	engineLoadD[0] = engineLoad;
	float Dcurr = engineLoadD[0] - engineLoadD[1];
	float Dold = engineLoadD[2] - engineLoadD[3];
	diffEnrichment = ((3 * Dcurr + Dold) / 4) * (engineConfiguration->diffLoadEnrichmentCoef);
}

float AccelEnrichmemnt::getDiffEnrichment() {
	return diffEnrichment;
}

float getAccelEnrichment(void) {
	return instance.getDiffEnrichment();
}

#if EFI_PROD_CODE
static WORKING_AREA(aeThreadStack, UTILITY_THREAD_STACK_SIZE);

static msg_t DiffEnrichmentThread(int param) {
	chRegSetThreadName("Diff Enrichment");
	while (TRUE) {
		instance.updateDiffEnrichment(engineConfiguration, getEngineLoad());
		chThdSleepMilliseconds(100);
	}
#if defined __GNUC__
	return -1;
#endif
}

void initDiffEnrichment(void) {
	chThdCreateStatic(aeThreadStack, sizeof(aeThreadStack), LOWPRIO, (tfunc_t) DiffEnrichmentThread, NULL);
}

#endif
