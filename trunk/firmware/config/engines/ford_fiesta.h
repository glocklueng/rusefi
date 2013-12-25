/**
 * @file	ford_fiesta.h
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FORD_FIESTA_H_
#define FORD_FIESTA_H_
#if EFI_SUPPORT_FORD_FIESTA

#include "engine_configuration.h"

void setFordFiestaDefaultEngineConfiguration(EngineConfiguration *engineConfiguration);
void setFordFiestaEngineConfiguration2(EngineConfiguration2 *engineConfiguration2);

#endif /* EFI_SUPPORT_FORD_FIESTA */
#endif /* FORD_FIESTA_H_ */
