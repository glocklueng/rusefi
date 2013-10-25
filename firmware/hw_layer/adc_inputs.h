/*
 * adc_inputs.h
 *
 *  Created on: Jan 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADC_INPUTS_H_
#define ADC_INPUTS_H_

#include "global.h"
#include <time.h>

#define ADC_LOGIC_0 0
#define ADC_LOGIC_1 1
#define ADC_LOGIC_2 2
#define ADC_LOGIC_3 3
#define ADC_LOGIC_4 4
#define ADC_LOGIC_5 5
#define ADC_LOGIC_6 6
#define ADC_LOGIC_7 7
#define ADC_LOGIC_8 8
#define ADC_LOGIC_9 9

//#include "adc_internal_nice_board.h"
#include "adc_internal_dual_amp.h"
//#include "adc_external.h"

// extra board

// channel 11: PA3
//#define ADC_CHANNEL_VREF 11

void initAdcInputs(void);
void pokeAdcInputs(void);
int getInternalAdcValue(int index);

#define ADC_NUMBER_CHANNELS_SLOW		10

// this structure contains one multi-channel ADC state snapshot
typedef struct {
	volatile adcsample_t adc_data[ADC_NUMBER_CHANNELS_SLOW];
	time_t time;
} adc_state;


#endif /* ADC_INPUTS_H_ */
