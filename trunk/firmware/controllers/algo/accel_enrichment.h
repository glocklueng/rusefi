/**
 * @file    accel_enrichment.h
 * @brief   Acceleration enrichment calculator
 *
 * @date Apr 21, 2014
 * @author Dmitry Sidin
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef ACC_ENRICHMENT_H_
#define ACC_ENRICHMENT_H_

#include "engine_configuration.h"
#include "cyclic_buffer.h"

//#define MAX_ACCEL_ARRAY_SIZE 64

class AccelEnrichmemnt {
public:
	AccelEnrichmemnt();
	void updateDiffEnrichment(engine_configuration_s *engineConfiguration,
			float engineLoad);
	float getMapEnrichment(DECLARE_ENGINE_PARAMETER_F);
	float getTpsEnrichment(DECLARE_ENGINE_PARAMETER_F);
//	float getDiffEnrichment(void);

	void onEngineCycle(DECLARE_ENGINE_PARAMETER_F);
	void onEngineCycleTps(DECLARE_ENGINE_PARAMETER_F);
	void reset();
	float currentEngineLoad;
	float maxDelta;
	float minDelta;
	float delta;
	cyclic_buffer<float> cb;

private:
//	float array[MAX_ACCEL_ARRAY_SIZE];
	float diffEnrichment;
};

void initAccelEnrichment(Logging *sharedLogger);
float getAccelEnrichment(void);

#endif /* ACC_ENRICHMENT_H_ */

