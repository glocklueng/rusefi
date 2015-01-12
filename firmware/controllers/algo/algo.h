/*
 * @file	algo.h
 *
 * @date Mar 2, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef ALGO_H_
#define ALGO_H_

#include "engine_configuration.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void initDataStructures(DECLARE_ENGINE_PARAMETER_F);
void initAlgo(engine_configuration_s *engineConfiguration);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ALGO_H_ */
