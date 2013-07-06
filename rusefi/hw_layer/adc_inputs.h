/*
 * adc_inputs.h
 *
 *  Created on: Jan 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADC_INPUTS_H_
#define ADC_INPUTS_H_

#include "global.h"

//#define ADC_CHANNEL_MAF 7 // x2 board
#define ADC_CHANNEL_MAF 9 // x1 board
// channel 11: PA3
#define ADC_CHANNEL_VREF 11

void initAdcInputs(void);
void pokeAdcInputs(void);
int getAdcValue(int index);
myfloat adcToVolts(int adc);
// this method should be used to display real voltage if we have divided it by two to fit it under +3v
myfloat adcToVolts2(int adc);

#endif /* ADC_INPUTS_H_ */
