/**
 * @file	map_averaging.h
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef ADC_AVERAGING_H_
#define ADC_AVERAGING_H_

#include "engine.h"

#if EFI_MAP_AVERAGING || defined(__DOXYGEN__)

#if EFI_PROD_CODE || defined(__DOXYGEN__)
void mapAveragingCallback(adcsample_t newValue);
#endif

void initMapAveraging(Logging *sharedLogger, Engine *engine);

#endif /* EFI_MAP_AVERAGING */

#endif /* ADC_AVERAGING_H_ */
