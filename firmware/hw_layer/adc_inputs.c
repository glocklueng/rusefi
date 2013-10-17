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
#include "engine_math.h"
#include "crank_input.h"
#include "idle_controller.h" // that's for min/max
/* Depth of the conversion buffer, channels are sampled X times each.*/
#define ADC_GRP1_BUF_DEPTH_SLOW      1
#define ADC_GRP1_BUF_DEPTH_FAST      1

#define ADC_NUMBER_CHANNELS_FAST		1

#define PWM_FREQ_SLOW 5000   /* PWM clock frequency. I wonder what does this setting mean?  */
#define PWM_PERIOD_SLOW 500  /* PWM period (in PWM ticks).    */

#define PWM_FREQ_FAST 1500000   /* PWM clock frequency. I wonder what does this setting mean?  */
#define PWM_PERIOD_FAST 50  /* PWM period (in PWM ticks).    */

#define ADC_PWM_SLOW	&PWMD5
#define ADC_SLOW ADCD1

#define ADC_PWM_FAST	&PWMD4
#define ADC_FAST ADCD2

#define ADC_DEBUG_KEY "adcDebug"

static char LOGGING_BUFFER[500];
static Logging log;
static int adcCallbackCounter_slow = 0;
static int adcCallbackCounter_fast = 0;

static int adcPokeCounter = 0;

static int adcDebugReporting = TRUE;

static volatile int fastValue = 0;
static volatile int fastCounter = 0;
static volatile int fastAccumulator = 0;
static volatile int fastMax = 0;
static volatile int fastMin = 9999999;

/*
 * ADC samples buffer.
 */
static adcsample_t samples_slow[ADC_NUMBER_CHANNELS_SLOW * ADC_GRP1_BUF_DEPTH_SLOW];
static adcsample_t samples_fast[ADC_NUMBER_CHANNELS_FAST * ADC_GRP1_BUF_DEPTH_FAST];

static adcsample_t getAvgAdcValue(int index, adcsample_t *samples, int bufDepth, int numChannels) {
	adcsample_t result = 0;
	int i;
	for (i = 0; i < bufDepth; i++) {
		result += samples[index];
		index += numChannels;
	}
	return result / bufDepth;
}

static adc_state newState;

static void adc_callback_slow(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void) buffer;
	(void) n;
	/* Note, only in the ADC_COMPLETE state because the ADC driver fires an
	 intermediate callback when the buffer is half full.*/
	if (adcp->state == ADC_COMPLETE) {
		/* Calculates the average values from the ADC samples.*/

		adcCallbackCounter_slow++;

		newState.time = chTimeNow();
		for (int i = 0; i < ADC_NUMBER_CHANNELS_SLOW; i++) {
			int value = getAvgAdcValue(i, samples_slow, ADC_GRP1_BUF_DEPTH_SLOW, ADC_NUMBER_CHANNELS_SLOW);
			newState.adc_data[i] = value;
		}
	}
}

static void adc_callback_fast(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void) buffer;
	(void) n;
//	/* Note, only in the ADC_COMPLETE state because the ADC driver fires an
//	 intermediate callback when the buffer is half full.*/
	if (adcp->state == ADC_COMPLETE) {
		/* Calculates the average values from the ADC samples.*/
//
		adcCallbackCounter_fast++;
//
//

		chSysLockFromIsr()
		;
//		newState.time = chTimeNow();
//		for (int i = 0; i < ADC_NUMBER_CHANNELS_SLOW; i++) {
		fastValue = getAvgAdcValue(0, samples_fast, ADC_GRP1_BUF_DEPTH_FAST, ADC_NUMBER_CHANNELS_FAST);

		fastAccumulator += fastValue;
		fastMax = max(fastMax, fastValue);
		fastMin = min(fastMin, fastValue);
		fastCounter++;
		chSysUnlockFromIsr()
		;

//			newState.adc_data[i] = value;
//		}
	}
}

#define MY_SAMPLING_SLOW ADC_SAMPLE_480
#define MY_SAMPLING_FAST ADC_SAMPLE_28

/*
 * ADC conversion group.
 */
static ADCConversionGroup adcgrpcfg_slow = { FALSE, ADC_NUMBER_CHANNELS_SLOW, adc_callback_slow, NULL,
/* HW dependent part.*/
ADC_TwoSamplingDelay_20Cycles,   // cr1
		ADC_CR2_SWSTART, // cr2

		ADC_SMPR1_SMP_AN10(MY_SAMPLING_SLOW) |
		ADC_SMPR1_SMP_AN11(MY_SAMPLING_SLOW) |
		ADC_SMPR1_SMP_AN12(MY_SAMPLING_SLOW) |
		ADC_SMPR1_SMP_AN13(MY_SAMPLING_SLOW) , // sample times for channels 10...18
		ADC_SMPR2_SMP_AN0(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN1(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN3(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN4(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN5(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN6(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN7(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN8(MY_SAMPLING_SLOW) |
		ADC_SMPR2_SMP_AN9(MY_SAMPLING_SLOW)

		, // In this field must be specified the sample times for channels 0...9

		ADC_SQR1_NUM_CH(ADC_NUMBER_CHANNELS_SLOW), // Conversion group sequence 13...16 + sequence length

		0
//		| ADC_SQR2_SQ7_N(ADC_CHANNEL_IN12) /* PC2 - green */
//				| ADC_SQR2_SQ8_N(ADC_CHANNEL_IN13) /* PC3 - yellow maf? */

		,// Conversion group sequence 7...12
		0
//		| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN6) /* PA6 - white */
//		| ADC_SQR3_SQ2_N(ADC_CHANNEL_IN7) /* PA7 - blue */
//				| ADC_SQR3_SQ3_N(ADC_CHANNEL_IN14) /* PC4 - green */
//				| ADC_SQR3_SQ4_N(ADC_CHANNEL_IN15) /* PC5 - yellow */
//				| ADC_SQR3_SQ5_N(ADC_CHANNEL_IN8) /* PB0 - blue */
//				| ADC_SQR3_SQ6_N(ADC_CHANNEL_IN9) /* PB1 - white */
// Conversion group sequence 1...6
		};

static const ADCConversionGroup adcgrpcfg_fast = { FALSE, ADC_NUMBER_CHANNELS_FAST, adc_callback_fast, NULL,
/* HW dependent part.*/
ADC_TwoSamplingDelay_5Cycles,   // cr1
		ADC_CR2_SWSTART, // cr2

		0, // sample times for channels 10...18
		ADC_SMPR2_SMP_AN0(MY_SAMPLING_FAST), // In this field must be specified the sample times for channels 0...9

		ADC_SQR1_NUM_CH(ADC_NUMBER_CHANNELS_FAST), // Conversion group sequence 13...16 + sequence length

		0, // Conversion group sequence 7...12
		0 | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN3) /* PA3 */
// maf		| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN13) /* PC3 */

		// Conversion group sequence 1...6
		};

static void pwmpcb_slow(PWMDriver *pwmp) {
#ifdef EFI_INTERNAL_ADC
	(void) pwmp;

	/* Starts an asynchronous ADC conversion operation, the conversion
	 will be executed in parallel to the current PWM cycle and will
	 terminate before the next PWM cycle.*/chSysLockFromIsr()
	;
	adcStartConversionI(&ADC_SLOW, &adcgrpcfg_slow, samples_slow, ADC_GRP1_BUF_DEPTH_SLOW);
	chSysUnlockFromIsr()
	;
#endif
}

static void pwmpcb_fast(PWMDriver *pwmp) {
#ifdef EFI_INTERNAL_ADC
	(void) pwmp;

	/* Starts an asynchronous ADC conversion operation, the conversion
	 will be executed in parallel to the current PWM cycle and will
	 terminate before the next PWM cycle.*/chSysLockFromIsr()
	;
	adcStartConversionI(&ADC_FAST, &adcgrpcfg_fast, samples_fast, ADC_GRP1_BUF_DEPTH_FAST);
	chSysUnlockFromIsr()
	;
#endif
}

int getInternalAdcValue(int index) {
	if (index >= ADC_NUMBER_CHANNELS_SLOW)
		return -1;
	return newState.adc_data[index];
}

static PWMConfig pwmcfg_slow = { PWM_FREQ_SLOW, PWM_PERIOD_SLOW, pwmpcb_slow, { {
PWM_OUTPUT_DISABLED, NULL }, { PWM_OUTPUT_DISABLED, NULL }, {
PWM_OUTPUT_DISABLED, NULL }, { PWM_OUTPUT_DISABLED, NULL } },
/* HW dependent part.*/
0 };

static PWMConfig pwmcfg_fast = { PWM_FREQ_FAST, PWM_PERIOD_FAST, pwmpcb_fast, { {
PWM_OUTPUT_DISABLED, NULL }, { PWM_OUTPUT_DISABLED, NULL }, {
PWM_OUTPUT_DISABLED, NULL }, { PWM_OUTPUT_DISABLED, NULL } },
/* HW dependent part.*/
0 };

static void initAdcPin(GPIO_TypeDef* port, int pin, char *msg) {
	print("adc %s\r\n", msg);
	mySetPadMode("adc input", port, pin, PAL_MODE_INPUT_ANALOG);
}

static void initAdcHwChannel(int channel) {
	GPIO_TypeDef* port;
	int pin;

	switch (channel) {
	case ADC_CHANNEL_IN6:
		port = GPIOA;
		pin = 6;
		break;
	case ADC_CHANNEL_IN7:
		port = GPIOA;
		pin = 7;
		break;
	case ADC_CHANNEL_IN8:
		port = GPIOB;
		pin = 0;
		break;
	case ADC_CHANNEL_IN9:
		port = GPIOB;
		pin = 1;
		break;
	case ADC_CHANNEL_IN10:
		port = GPIOC;
		pin = 0;
		break;
	case ADC_CHANNEL_IN11:
		port = GPIOC;
		pin = 1;
		break;
	case ADC_CHANNEL_IN12:
		port = GPIOC;
		pin = 2;
		break;
	case ADC_CHANNEL_IN13:
		port = GPIOC;
		pin = 3;
		break;
	case ADC_CHANNEL_IN14:
		port = GPIOC;
		pin = 4;
		break;
	case ADC_CHANNEL_IN15:
		port = GPIOC;
		pin = 5;
		break;
	default:
		fatal("Unknown hw channel");
	}
	initAdcPin(port, pin, "hw");
}

void initSlowChannel(int logicChannel, int hwChannel) {
	if (logicChannel < 6) {
		adcgrpcfg_slow.sqr3 += (hwChannel) << (5 * logicChannel);
	} else {
		adcgrpcfg_slow.sqr2 += (hwChannel) << (5 * (logicChannel - 6));
	}

	initAdcHwChannel(hwChannel);
}

void printAdcValue(int channel) {
	int value = getAdcValue(channel);
	myfloat volts = adcToVolts(value);
	scheduleSimpleMsg(&log, "adc voltage x100: ", (int) (100 * volts));
}

void printFullAdcReport() {
	for (int i = 0; i < ADC_NUMBER_CHANNELS_SLOW; i++) {
		msgInt(&log, " ch", i);
		int value = getAdcValue(i);
		msgInt(&log, " val= ", value);
		myfloat volts = adcToVolts(value);
		debugFloat(&log, "v ", volts, 1);
	}
	scheduleLogging(&log);
}

static void printStatus() {
	scheduleIntValue(&log, ADC_DEBUG_KEY, adcDebugReporting);
}

static void setAdcDebugReporting(int value) {
	adcDebugReporting = value;
	printStatus();
}

void initAdcInputs() {

	initLogging(&log, "ADC", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));

	printStatus();

	addConsoleAction1(ADC_DEBUG_KEY, &setAdcDebugReporting);

#ifdef EFI_INTERNAL_ADC
	/*
	 * Initializes the ADC driver.
	 */
	adcStart(&ADC_SLOW, NULL);
	adcStart(&ADC_FAST, NULL);

	adcgrpcfg_slow.sqr2 = 0;
	adcgrpcfg_slow.sqr3 = 0;

	initSlowChannel(ADC_LOGIC_0, ADC_CHANNEL_IN6); // PA6 right white
	initSlowChannel(ADC_LOGIC_1, ADC_CHANNEL_IN7); // PA7 right blue
	initSlowChannel(ADC_LOGIC_2, ADC_CHANNEL_IN14); // PC4 right green
	initSlowChannel(ADC_LOGIC_3, ADC_CHANNEL_IN15); // PC5 right yellow

	initSlowChannel(ADC_LOGIC_4, ADC_CHANNEL_IN8); // PB0 left blue
	initSlowChannel(ADC_LOGIC_5, ADC_CHANNEL_IN9); // PB1 left white
	initSlowChannel(ADC_LOGIC_6, ADC_CHANNEL_IN12); // PC2 left green. extra board ch 4
	initSlowChannel(ADC_LOGIC_7, ADC_CHANNEL_IN13); // PC3 left yellow, extra board ch 1

	initSlowChannel(ADC_LOGIC_8, ADC_CHANNEL_IN10); // extra board ch 3
	initSlowChannel(ADC_LOGIC_9, ADC_CHANNEL_IN11); // extra board ch 2

	/*
	 * Initializes the PWM driver.
	 */
	pwmStart(ADC_PWM_SLOW, &pwmcfg_slow);
	pwmStart(ADC_PWM_FAST, &pwmcfg_fast);
	addConsoleAction1("adc", printAdcValue);
	addConsoleAction("fadc", printFullAdcReport);
#else
	printSimpleMsg(&log, "ADC disabled", 0);
#endif
}

static int prevCkpEventCounter = -1;

void pokeAdcInputs() {
	if (!adcDebugReporting)
		return;

	int currentCkpEventCounter = getCrankEventCounter();
	if (prevCkpEventCounter == currentCkpEventCounter)
		return;
	prevCkpEventCounter = currentCkpEventCounter;

//	if (adcPokeCounter++ % 40 != 0)
//		return;

//	myfloat sec = ((myfloat) GetSysclockCounter() / TICKS_IN_MS) / 1000;
//	debugFloat(&log, "time", sec, 3);
//	scheduleIntValue(&log, "adc10", newState.adc_data[10]);

	chSysLock()
	;
	int lFastValue = fastValue;
	int lFastCounter = fastCounter;
	int lFastAccumulator = fastAccumulator;
	int lFastMax = fastMax;
	int lFastMin = fastMin;
	fastCounter = fastAccumulator = fastMax = 0;
	fastMin = 9999999;
	chSysUnlock()
	;

	if (lFastCounter > 0) {
//		scheduleIntValue(&log, "adcfast", lFastValue);
//		scheduleIntValue(&log, "adcfastavg", lFastAccumulator / lFastCounter);
//		scheduleIntValue(&log, "adcfast_co", lFastCounter);
//		scheduleIntValue(&log, "adcfast_min", lFastMin);
//		scheduleIntValue(&log, "adcfast_max", lFastMax);
	}

	//scheduleIntValue(&log, "adcfastavg", lFastAccumulator);

//	print("adc slow %4d    adc fast %d\r\n", newState.adc_data[10], fastValue);

//	for (int i = 0; i< ADC_NUMBER_CHANNELS_SLOW; i++) {
//		print("adc%d:%d\r\n", i, newState.adc_data[i]);
//	}
}

