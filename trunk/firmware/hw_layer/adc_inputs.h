/**
 * @file	adc_inputs.h
 * @brief	Low level ADC code
 *
 * @date Jan 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADC_INPUTS_H_
#define ADC_INPUTS_H_

#include "main.h"

GPIO_TypeDef* getAdcChannelPort(int hwChannel);
int getAdcChannelPin(int hwChannel);
void initAdcInputs(void);
int getAdcHardwareIndexByInternalIndex(int index);
int getAdcValueByIndex(int internalIndex);
void pokeAdcInputs(void);
int getInternalAdcValue(int index);

/* Depth of the conversion buffer, channels are sampled X times each.*/
#define ADC_GRP1_BUF_DEPTH_SLOW      1
#define ADC_MAX_SLOW_CHANNELS_COUNT 12

// this structure contains one multi-channel ADC state snapshot
typedef struct {
	volatile adcsample_t adc_data[ADC_MAX_SLOW_CHANNELS_COUNT];
	time_t time;
} adc_state;

typedef struct {
	adcsample_t samples[ADC_MAX_SLOW_CHANNELS_COUNT * ADC_GRP1_BUF_DEPTH_SLOW];


} adc_hw_helper_s;


#define getAdcValue(hwChannel) getInternalAdcValue(hwChannel)

#define adcToVolts(adc) ((((float) 3.0) * (adc) / 4095))

#define adcToVoltsDivided(adc) (adcToVolts(adc) * engineConfiguration->analogInputDividerCoefficient)

#define getVoltage(hwChannel) (adcToVolts(getAdcValue(hwChannel)))

#define getVoltageDivided(hwChannel) (getVoltage(hwChannel) * engineConfiguration->analogInputDividerCoefficient)

#endif /* ADC_INPUTS_H_ */
