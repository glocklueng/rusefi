/**
 * @file	nissan_primera.h
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "features.h"

#ifndef NISSAN_PRIMERA_H_
#define NISSAN_PRIMERA_H_

#if EFI_SUPPORT_NISSAN_PRIMERA

void setNissanPrimeraEngineConfiguration(EngineConfiguration *engineConfiguration);
void setNissanPrimeraEngineConfiguration2(EngineConfiguration2 *engineConfiguration2);

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */

#endif /* NISSAN_PRIMERA_H_ */
