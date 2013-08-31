/*
 * adc_external.h
 *
 *  Created on: Aug 18, 2013
 *      Author: pc
 */

#ifndef ADC_EXTERNAL_H_
#define ADC_EXTERNAL_H_

#include "mcp3208.h"

#define ADC_CHANNEL_VREF ADC_LOGIC_0
#define ADC_LOGIC_COOLANT ADC_LOGIC_0
#define ADC_LOGIC_AIR ADC_LOGIC_1

#define ADC_LOGIC_AFR ADC_LOGIC_1
#define ADC_LOGIC_MAF ADC_LOGIC_2
#define ADC_LOGIC_MAP ADC_LOGIC_2
#define ADC_LOGIC_TPS ADC_LOGIC_2

#define getAdcValue(channel) getMcp3208adc(channel)
#define adcToVolts(adc) ((((float) 5.0) * adc / 4095))
#define getVoltage(channel) adcToVolts(getAdcValue(channel))

#endif /* ADC_EXTERNAL_H_ */
