/*
 * adc_internal_dual_amp.h
 *
 *  Created on: Aug 18, 2013
 *      Author: user
 */

#ifndef ADC_INTERNAL_DUAL_AMP_H_
#define ADC_INTERNAL_DUAL_AMP_H_

#include "adc_inputs.h"
#include "adc_internal_common.h"

#define ADC_LOGIC_MAP ADC_LOGIC_0
#define ADC_LOGIC_TPS ADC_LOGIC_1
#define ADC_LOGIC_AFR ADC_LOGIC_7


// x2: yellow PC5. SQ4 is channel 3
 #define ADC_CHANNEL_VREF ADC_LOGIC_3
// x2 board
 #define ADC_LOGIC_MAF ADC_LOGIC_5
 #define ADC_LOGIC_COOLANT ADC_LOGIC_2
 #define ADC_LOGIC_AIR ADC_LOGIC_3

#endif /* ADC_INTERNAL_DUAL_AMP_H_ */
