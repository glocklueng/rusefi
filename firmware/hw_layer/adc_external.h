/*
 * @file    adc_external.h
 *
 *
 *  Created on: Aug 18, 2013
 *      Author: pc
 */

#ifndef ADC_EXTERNAL_H_
#define ADC_EXTERNAL_H_

#include "mcp3208.h"

#define getAdcValue(channel) getMcp3208adc(channel)
#define adcToVolts(adc) ((((float) 5.0) * adc / 4095))
#define getVoltage(channel) adcToVolts(getAdcValue(channel))

#endif /* ADC_EXTERNAL_H_ */
