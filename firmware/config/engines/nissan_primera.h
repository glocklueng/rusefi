/**
 * @file	nissan_primera.h
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "features.h"
#include "pwm_generator.h"

#ifndef DENISVAK_H_
#define DENISVAK_H_

#if EFI_SUPPORT_NISSAN_PRIMERA

void setNissanPrimeraEngineConfiguration(EngineConfiguration *engineConfiguration);
void setNissanPrimeraEngineConfiguration2(EngineConfiguration2 *engineConfiguration2);

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */

#endif /* DENISVAK_H_ */
