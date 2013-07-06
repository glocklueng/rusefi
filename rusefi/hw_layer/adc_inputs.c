/*
 * adc_inputs.c
 *
 *  Created on: Jan 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "adc_inputs.h"

#include "rficonsole.h"
#include "datalogging.h"
#include "pin_repository.h"

/* Depth of the conversion buffer, channels are sampled X times each.*/
#define ADC_GRP1_BUF_DEPTH      1

#define ADC_NUMBER_CHANNELS		12

/* PWM clock frequency. I wonder what does this setting mean?  */
#define PWM_FREQ 50000
/* PWM period (in PWM ticks).    */
#define PWM_PERIOD 5000

#define ADC_PWM	&PWMD5

static Logging log;

/*
 * ADC samples buffer.
 */
static adcsample_t samples[ADC_NUMBER_CHANNELS * ADC_GRP1_BUF_DEPTH];

static void adc_callback(ADCDriver *adcp, adcsample_t *buffer, size_t n);

#define MY_SAMPLING ADC_SAMPLE_480

/*
 * ADC conversion group.
 */
static const ADCConversionGroup adcgrpcfg =
		{ FALSE, ADC_NUMBER_CHANNELS, adc_callback, NULL,
		/* HW dependent part.*/
				ADC_TwoSamplingDelay_20Cycles,   // cr1
				ADC_CR2_SWSTART, // cr2

				ADC_SMPR1_SMP_AN10(ADC_SAMPLE_480) |
				ADC_SMPR1_SMP_AN11(ADC_SAMPLE_480) |
				ADC_SMPR1_SMP_AN12(ADC_SAMPLE_480) , // sample times for channels 10...18
						ADC_SMPR2_SMP_AN0(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN1(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN3(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN4(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN5(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN6(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN7(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN8(ADC_SAMPLE_480) |
						ADC_SMPR2_SMP_AN9(ADC_SAMPLE_480)

						, // In this field must be specified the sample times for channels 0...9

				ADC_SQR1_NUM_CH(ADC_NUMBER_CHANNELS), // Conversion group sequence 13...16 + sequence length

				0
				| ADC_SQR2_SQ7_N(ADC_CHANNEL_IN12) /* PC2 - green */
				| ADC_SQR2_SQ8_N(ADC_CHANNEL_IN13) /* PC3 - yellow */
				| ADC_SQR2_SQ9_N(ADC_CHANNEL_IN0)  /* PA0 green */
				| ADC_SQR2_SQ10_N(ADC_CHANNEL_IN1)  /* PA1 */
				| ADC_SQR2_SQ11_N(ADC_CHANNEL_IN2) /* PA2 */
				| ADC_SQR2_SQ12_N(ADC_CHANNEL_IN3) /* PA3 */

				, // Conversion group sequence 7...12
				0
//				| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10) /* PC0 */ // careful - power switch on board
//				| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11) /* PC1 grey */
//				| ADC_SQR3_SQ2_N(ADC_CHANNEL_IN12) /* PC2 */
//				| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN13) /* PC3 */
				| ADC_SQR3_SQ3_N(ADC_CHANNEL_IN14) /* PC4 - green */
				| ADC_SQR3_SQ4_N(ADC_CHANNEL_IN15) /* PC5 - yellow */


				//				| ADC_SQR3_SQ5_N(ADC_CHANNEL_IN4)  /* PA4 orange */
//				| ADC_SQR3_SQ2_N(ADC_CHANNEL_IN5) /* PA5 */
				| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN6) /* PA6 - white */
				| ADC_SQR3_SQ2_N(ADC_CHANNEL_IN7) /* PA7 - blue */
				| ADC_SQR3_SQ5_N(ADC_CHANNEL_IN8) /* PB0 - blue */
				| ADC_SQR3_SQ6_N(ADC_CHANNEL_IN9) /* PB1 - white */
		// Conversion group sequence 1...6
		};

static void pwmpcb(PWMDriver *pwmp) {
#ifdef EFI_ADC
	(void) pwmp;

	/* Starts an asynchronous ADC conversion operation, the conversion
	 will be executed in parallel to the current PWM cycle and will
	 terminate before the next PWM cycle.*/chSysLockFromIsr()
	;
	adcStartConversionI(&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
	chSysUnlockFromIsr();
#endif
}

static adcsample_t getAvgAdcValue(int index, adcsample_t *samples) {
	adcsample_t result = 0;
	int i;
	for (i = 0; i < ADC_GRP1_BUF_DEPTH; i++) {
		result += samples[index];
		index += ADC_NUMBER_CHANNELS;
	}
	return result / ADC_GRP1_BUF_DEPTH;
}

// this structure contains one multi-channel ADC state snapshot
typedef struct {
	volatile adcsample_t adc_data[ADC_NUMBER_CHANNELS];
	time_t time;
} adc_state;

static adc_state newState;

int getAdcValue(int index) {
	if (index >= ADC_NUMBER_CHANNELS)
		return -1;
	return newState.adc_data[index];
}

static void adc_callback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void) buffer;
	(void) n;
	/* Note, only in the ADC_COMPLETE state because the ADC driver fires an
	 intermediate callback when the buffer is half full.*/
	if (adcp->state == ADC_COMPLETE) {
		/* Calculates the average values from the ADC samples.*/

		newState.time = chTimeNow();
		for (int i = 0; i < ADC_NUMBER_CHANNELS; i++) {
			int value = getAvgAdcValue(i, samples);
			newState.adc_data[i] = value;
		}
	}
}

static PWMConfig pwmcfg = { PWM_FREQ, PWM_PERIOD, pwmpcb, { {
		PWM_OUTPUT_DISABLED, NULL }, { PWM_OUTPUT_DISABLED, NULL }, {
		PWM_OUTPUT_DISABLED, NULL }, { PWM_OUTPUT_DISABLED, NULL } },
/* HW dependent part.*/
0 };

static void initAdcPin(GPIO_TypeDef* port, int pin, char *msg) {
	print("adc %s\r\n", msg);
	mySetPadMode("adc input", port, pin, PAL_MODE_INPUT_ANALOG);
}

void printAdcValue(int channel) {
	int value = getAdcValue(channel);
	myfloat volts = adcToVolts2(value);
	scheduleSimpleMsg(&log, "adc voltage x100: ", (int)(100 * volts));
}


void initAdcInputs() {
	initLogging(&log, "ADC", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));
#ifdef EFI_ADC
	/*
	 * Initializes the ADC driver 1.
	 */
	adcStart(&ADCD1, NULL );

	// PA0: ADC 0 (2nd pin on 1 amp board)
	initAdcPin(GPIOA, 0, "a0");
	initAdcPin(GPIOA, 1, "a1");
	initAdcPin(GPIOA, 2, "MAF");
	// PA3: ADC 3 (upper pin on x1 amp board)
	initAdcPin(GPIOA, 3, "Vref");

	// PC0, PC1, PC2 & PC3
	initAdcPin(GPIOA, 6, "coolant temp");
	initAdcPin(GPIOA, 7, "MAF");
	initAdcPin(GPIOC, 4, "air");
	initAdcPin(GPIOC, 5, "tp");

	initAdcPin(GPIOB, 0, "5air");
	initAdcPin(GPIOB, 1, "6tp");
	initAdcPin(GPIOC, 2, "7air");
	initAdcPin(GPIOC, 3, "8tp");

	/*
	 * Initializes the PWM driver.
	 */
	pwmStart(ADC_PWM, &pwmcfg);
	addConsoleAction1("adc", printAdcValue);
#else
	printSimpleMsg(&log, "ADC disabled", 0);
#endif
}

void pokeAdcInputs() {
	for (int i = 0; i< ADC_NUMBER_CHANNELS; i++) {
		print("adc%d:%d\r\n", i, newState.adc_data[i]);
	}
}

myfloat adcToVolts(int adc) {
	return ((myfloat)3.0) * adc / 4095;
}

myfloat adcToVolts2(int adc) {
	return adcToVolts(adc) * 2;
}

