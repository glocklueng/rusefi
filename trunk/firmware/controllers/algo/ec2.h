/*
 * ec2.h
 *
 *  Created on: Apr 26, 2014
 *      Author: Andrey
 */

#ifndef EC2_H_
#define EC2_H_

#include "engine_configuration.h"
#include "trigger_structure.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
typedef struct {
	int hasMapSensor;
	int hasCltSensor;

	Thermistor iat;
	Thermistor clt;

	int crankAngleRange;

	trigger_shape_s triggerShape;

	cranking_ignition_mode_e crankingIgnitionMode;

	EventHandlerConfiguration engineEventConfiguration;

	int isInjectionEnabledFlag;
} engine_configuration2_s;

void prepareOutputSignals(engine_configuration_s *engineConfiguration,
		engine_configuration2_s *engineConfiguration2);

void initializeIgnitionActions(float baseAngle, engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2);
void addFuelEvents(engine_configuration_s const *e,  engine_configuration2_s *engineConfiguration2, ActuatorEventList *list, injection_mode_e mode);

void resetConfigurationExt(engine_type_e engineType,
		engine_configuration_s *engineConfiguration,
		engine_configuration2_s *engineConfiguration2,
		board_configuration_s *boardConfiguration);
void applyNonPersistentConfiguration(engine_configuration_s *engineConfiguration,
		engine_configuration2_s *engineConfiguration2, engine_type_e engineType);


void setDefaultNonPersistentConfiguration(engine_configuration2_s *engineConfiguration2);
void printConfiguration(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EC2_H_ */
