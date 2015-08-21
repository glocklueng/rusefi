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

/**
 * this object is used for MAP rate-of-change and TPS rate-of-change corrections
 */
class AccelEnrichmemnt {
public:
	AccelEnrichmemnt();
	float getMapEnrichment(DECLARE_ENGINE_PARAMETER_F);
	floatms_t getTpsEnrichment(DECLARE_ENGINE_PARAMETER_F);
	float getDelta();

	void onEngineCycle(DECLARE_ENGINE_PARAMETER_F);
	void onEngineCycleTps(DECLARE_ENGINE_PARAMETER_F);
	void reset();
	float delta;
	cyclic_buffer<float> cb;

private:
	float currentValue;
	void onNewValue(float currentValue DECLARE_ENGINE_PARAMETER_S);
};

class WallFuel {
	WallFuel();
	floatms_t adjust(floatms_t target DECLARE_ENGINE_PARAMETER_S);

private:
	/**
	 * Amount of fuel on the wall, in injector open time scale
	 */
	floatms_t wallFuel;
};

void initAccelEnrichment(Logging *sharedLogger);
float getAccelEnrichment(void);

#endif /* ACC_ENRICHMENT_H_ */

