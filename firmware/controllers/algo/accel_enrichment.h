/**
 * @file    accel_enrichment.h
 * @brief   Acceleration enrichment calculator
 *
 * @date Apr 21, 2014
 * @author Dmitry Sidin
 * @author Andrey Belomutskiy (c) 2012-2014
 */

#ifndef ACC_ENRICHMENT_H_
#define ACC_ENRICHMENT_H_

#include "engine_configuration.h"

class AccelEnrichmemnt {
public:
	AccelEnrichmemnt();
	void updateDiffEnrichment(engine_configuration_s *engineConfiguration,
			float engineLoad);
	float getEnrichment(DECLARE_ENGINE_PARAMETER_F);
//	float getDiffEnrichment(void);

	void onEngineCycle(DECLARE_ENGINE_PARAMETER_F);
	void reset();
	float currentEngineLoad;
	float maxDelta;
	float minDelta;
	float delta;

private:
	float engineLoadD[4];
	float diffEnrichment;
};

void initDiffEnrichment(void);
float getAccelEnrichment(void);


#endif /* ACC_ENRICHMENT_H_ */

