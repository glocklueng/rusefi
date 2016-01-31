/**
 * @file    accel_enrichment.h
 * @brief   Acceleration enrichment calculator
 *
 * @date Apr 21, 2014
 * @author Dmitry Sidin
 * @author Andrey Belomutskiy, (c) 2012-2016
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
	/**
	 * @return Extra engine load value for fuel logic calculation
	 */
	float getEngineLoadEnrichment(DECLARE_ENGINE_PARAMETER_F);
	/**
	 * @return Extra fuel squirt duration for TPS acceleration
	 */
	floatms_t getTpsEnrichment(DECLARE_ENGINE_PARAMETER_F);
	float getMaxDelta();

	void onEngineCycle(DECLARE_ENGINE_PARAMETER_F);
	void onEngineCycleTps(DECLARE_ENGINE_PARAMETER_F);
	void reset();
	cyclic_buffer<float> cb;
	void onNewValue(float currentValue DECLARE_ENGINE_PARAMETER_S);

private:
	float previousValue;
};

class WallFuel {
public:
	WallFuel();
	/**
	 * @param target desired squirt duration
	 * @return total adjusted fuel squirt duration once wall wetting is taken into effect
	 */
	floatms_t adjust(int injectorIndex, floatms_t target DECLARE_ENGINE_PARAMETER_S);
	floatms_t getWallFuel(int injectorIndex);
	void reset();
private:
	/**
	 * Amount of fuel on the wall, in ms of injector open time, for specific injector.
	 */
	floatms_t wallFuel[INJECTION_PIN_COUNT];
};

void initAccelEnrichment(Logging *sharedLogger);

void setEngineLoadAccelLen(int len);
void setEngineLoadAccelThr(float value);
void setEngineLoadAccelMult(float value);
void updateAccelParameters();

#endif /* ACC_ENRICHMENT_H_ */

