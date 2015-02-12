/**
 * @file    maf.h
 * @brief
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
void setBosch0280218037(engine_configuration_s *engineConfiguration);

#endif
