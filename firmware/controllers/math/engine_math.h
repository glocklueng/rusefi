/**
 * @file	engine_math.h
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

#include "engine_configuration.h"

#ifdef __cplusplus

#include "ec2.h"
#include "trigger_structure.h"
#include "table_helper.h"
#include "engine.h"

#define INJECTOR_PIN_BY_INDEX(index) (io_pin_e) ((int) INJECTOR_1_OUTPUT + (index))

void findTriggerPosition(trigger_shape_s * s,
		event_trigger_position_s *position, float angleOffset DECLARE_ENGINE_PARAMETER_S);

int isInjectionEnabled(engine_configuration_s *engineConfiguration);

#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

float fixAngle(float angle DECLARE_ENGINE_PARAMETER_S);

/**
 * So that's how 'inline' syntax for both GCC and IAR
 * It is interesting to mention that GCC compiler chooses not to inline this function.
 *
 * @return time needed to rotate crankshaft by one degree, in milliseconds.
 * @deprecated use at least Us, maybe event Nt
 */
inline float getOneDegreeTimeMs(int rpm) {
	return 1000.0f * 60 / 360 / rpm;
}

/**
 * @return time needed to rotate crankshaft by one degree, in microseconds.
 */
#define getOneDegreeTimeUs(rpm) (1000000.0f * 60 / 360 / (rpm))

#define getOneDegreeTimeNt(rpm) (US2NT(1000000.0f) * 60 / 360 / (rpm))

float getCrankshaftRevolutionTimeMs(int rpm);

#define isCrankingR(rpm) ((rpm) > 0 && (rpm) < engineConfiguration->crankingSettings.crankingRpm)

float getEngineLoadT(Engine *engine);
#define getEngineLoad() getEngineLoadT(engine)

float getSparkDwellMsT(int rpm DECLARE_ENGINE_PARAMETER_S);

int getCylinderId(firing_order_e firingOrder, int index);

void setFuelRpmBin(engine_configuration_s *engineConfiguration, float l, float r);
void setFuelLoadBin(engine_configuration_s *engineConfiguration, float l, float r);
void setTimingRpmBin(engine_configuration_s *engineConfiguration, float l, float r);
void setTimingLoadBin(engine_configuration_s *engineConfiguration, float l, float r);

void setSingleCoilDwell(engine_configuration_s *engineConfiguration);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ENGINE_MATH_H_ */
