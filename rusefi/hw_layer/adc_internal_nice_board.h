/*
 * adc_internal_nice_board.h
 *
 *  Created on: Aug 18, 2013
 *      Author: user
 */

#ifndef ADC_INTERNAL_NICE_BOARD_H_
#define ADC_INTERNAL_NICE_BOARD_H_

#include "adc_internal_common.h"

// nice board is mounted right at the top left side


// ch 1 - 1st pin from top
#define ADC_LOGIC_MAF ADC_LOGIC_7
// ch 3 - 3rd pin, PC0
#define ADC_CHANNEL_VREF ADC_LOGIC_8
// ch 4 - 4th pin, PC2
#define ADC_LOGIC_COOLANT ADC_LOGIC_6

#define ADC_LOGIC_AIR ADC_LOGIC_9

#define ADC_LOGIC_TPS ADC_LOGIC_0
#define ADC_LOGIC_MAP ADC_LOGIC_0
#define ADC_LOGIC_AFR ADC_LOGIC_0



#endif /* ADC_INTERNAL_NICE_BOARD_H_ */
