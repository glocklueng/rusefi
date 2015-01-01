/**
 * @file settings.h
 * @brief This file is about configuring engine via the human-readable protocol
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef INJECTOR_CONTROL_H_
#define INJECTOR_CONTROL_H_

#include "engine.h"

void initSettings(engine_configuration_s *engineConfiguration);
void printSpiState(Logging *logger, board_configuration_s *boardConfiguration);
void printConfiguration(engine_configuration_s *engineConfiguration);

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void setEngineType(int value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INJECTOR_CONTROL_H_ */
