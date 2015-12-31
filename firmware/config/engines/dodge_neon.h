/**
 * @file	dodge_neon.h
 * @brief	1995 Dodge Neon default engine configuration
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef DODGE_NEON_H_
#define DODGE_NEON_H_

#if EFI_SUPPORT_DODGE_NEON

#include "engine.h"

void setDodgeNeon1995EngineConfiguration(DECLARE_ENGINE_PARAMETER_F);

void setDodgeNeonNGCEngineConfiguration(DECLARE_ENGINE_PARAMETER_F);

#endif /* EFI_SUPPORT_DODGE_NEON */

#endif /* DODGE_NEON_H_ */
