/**
 * @file    maf.h
 * @brief
 *
 * by the way 2.081989116 kg/h = 1 ft�/m
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef MAF_H_
#define MAF_H_

#include "main.h"

#define getMafT(ec) (getVoltageDivided(ec->mafAdcChannel))
float getMaf(void);
float getRealMaf(DECLARE_ENGINE_PARAMETER_F);

void setBosch0280218037(engine_configuration_s *engineConfiguration);
void setBosch0280218004(engine_configuration_s *engineConfiguration);

#endif
