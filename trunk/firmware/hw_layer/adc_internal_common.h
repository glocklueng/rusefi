/*
 * adc_internal_common.h
 *
 *  Created on: Aug 29, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADC_INTERNAL_COMMON_H_
#define ADC_INTERNAL_COMMON_H_

#define getAdcValue(channel) getInternalAdcValue(channel)

#define adcToVolts(adc) ((((float) 3.0) * adc / 4095) * 2)

#define getVoltage(channel) adcToVolts(getAdcValue(channel))


#endif /* ADC_INTERNAL_COMMON_H_ */
