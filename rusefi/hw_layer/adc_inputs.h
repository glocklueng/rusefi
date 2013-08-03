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


// x2: yellow PC5. SQ4 is channel 3
//#define ADC_CHANNEL_VREF 3
// x2 board
//#define ADC_LOGIC_MAF 5
#define ADC_LOGIC_COOLANT ADC_LOGIC_6

//#define ADC_LOGIC_AIR ADC_LOGIC_3

// extra board
#define ADC_LOGIC_COOLANT ADC_LOGIC_6
// ch 1
#define ADC_LOGIC_MAF ADC_LOGIC_7
// ch 3
#define ADC_CHANNEL_VREF ADC_LOGIC_8
#define ADC_LOGIC_AIR ADC_LOGIC_9

// dual quad board:

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

#define ADC_LOGIC_MAP 0
#define ADC_LOGIC_TPS 1




#define ADC_LOGIC_AFR 7



// channel 11: PA3
//#define ADC_CHANNEL_VREF 11

void initAdcInputs(void);
void pokeAdcInputs(void);
int getAdcValue(int index);

#define ADC_NUMBER_CHANNELS_SLOW		10

// this structure contains one multi-channel ADC state snapshot
typedef struct {
	volatile adcsample_t adc_data[ADC_NUMBER_CHANNELS_SLOW];
	time_t time;
} adc_state;


#endif /* ADC_INPUTS_H_ */
