/**
 * @file	dodge_neon.h
 * @brief	1995 Dodge Neon default engine configuration
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef DODGE_NEON_H_
#define DODGE_NEON_H_

#if EFI_ENGINE_DODGE_NEON

void setDodgeNeonEngineConfiguration(EngineConfiguration *engineConfiguration);
void setDodgeNeonEngineConfiguration2(EngineConfiguration2 *engineConfiguration2);

#endif /* EFI_ENGINE_DODGE_NEON */

#endif /* DODGE_NEON_H_ */
