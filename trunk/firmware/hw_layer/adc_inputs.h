/*
 * adc_inputs.h
 *
 *  Created on: Jan 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADC_INPUTS_H_
#define ADC_INPUTS_H_

#include "main.h"

#include "adc_internal_common.h"

void initAdcInputs(void);
void pokeAdcInputs(void);
int getInternalAdcValue(int index);

// this structure contains one multi-channel ADC state snapshot
typedef struct {
	volatile adcsample_t adc_data[EFI_ADC_SLOW_CHANNELS_COUNT];
	time_t time;
} adc_state;

#endif /* ADC_INPUTS_H_ */
