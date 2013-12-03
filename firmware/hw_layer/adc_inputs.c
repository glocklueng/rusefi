/**
 * @file	adc_inputs.c
 * @brief	Low level ADC code
 *
 * @date Jan 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "adc_inputs.h"

#include "rficonsole.h"
#include "pin_repository.h"
#include "engine_math.h"
#include "shaft_position_input.h"
#include "idle_controller.h" // that's for min/max
/* Depth of the conversion buffer, channels are sampled X times each.*/
#define ADC_GRP1_BUF_DEPTH_SLOW      1
#define ADC_GRP1_BUF_DEPTH_FAST      1

#define ADC_NUMBER_CHANNELS_FAST		1

#define PWM_FREQ_SLOW 5000   /* PWM clock frequency. I wonder what does this setting mean?  */
#define PWM_PERIOD_SLOW 500  /* PWM period (in PWM ticks).    */

#define PWM_FREQ_FAST 1500000   /* PWM clock frequency. I wonder what does this setting mean?  */
#define PWM_PERIOD_FAST 50  /* PWM period (in PWM ticks).    */

#define ADC_SLOW ADCD1

#define ADC_FAST ADCD2

#define ADC_DEBUG_KEY "adcDebug"

static char LOGGING_BUFFER[500];
static Logging logger;
static int adcCallbackCounter_slow = 0;
static int adcCallbackCounter_fast = 0;

static int adcDebugReporting = FALSE;

static int internalAdcIndex[20];

static volatile int fastValue = 0;
static volatile int fastCounter = 0;
static volatile int fastAccumulator = 0;
static volatile int fastMax = 0;
static volatile int fastMin = 9999999;

/*
 * ADC samples buffer.
 */
static adcsample_t samples_slow[EFI_ADC_SLOW_CHANNELS_COUNT * ADC_GRP1_BUF_DEPTH_SLOW];
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
		for (int i = 0; i < EFI_ADC_SLOW_CHANNELS_COUNT; i++) {
			int value = getAvgAdcValue(i, samples_slow, ADC_GRP1_BUF_DEPTH_SLOW, EFI_ADC_SLOW_CHANNELS_COUNT);
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
static ADCConversionGroup adcgrpcfg_slow = { FALSE, EFI_ADC_SLOW_CHANNELS_COUNT, adc_callback_slow, NULL,
/* HW dependent part.*/
ADC_TwoSamplingDelay_20Cycles,   // cr1
		ADC_CR2_SWSTART, // cr2

		ADC_SMPR1_SMP_AN10(MY_SAMPLING_SLOW) |
		ADC_SMPR1_SMP_AN11(MY_SAMPLING_SLOW) |
		ADC_SMPR1_SMP_AN12(MY_SAMPLING_SLOW) |
		ADC_SMPR1_SMP_AN13(MY_SAMPLING_SLOW), // sample times for channels 10...18
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

		ADC_SQR1_NUM_CH(EFI_ADC_SLOW_CHANNELS_COUNT), // Conversion group sequence 13...16 + sequence length

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

static int getAdcValueByIndex(int internalIndex) {
	return newState.adc_data[internalIndex];
}

int getInternalAdcValue(int hwIndex) {
	int internalIndex = internalAdcIndex[hwIndex];
	return getAdcValueByIndex(internalIndex);
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

static void initAdcPin(ioportid_t port, int pin, char *msg) {
	print("adc %s\r\n", msg);
	mySetPadMode("adc input", port, pin, PAL_MODE_INPUT_ANALOG);
}

static void initAdcHwChannel(int channel) {
	GPIO_TypeDef* port;
	int pin;

	switch (channel) {
	case ADC_CHANNEL_IN0:
		port = GPIOA;
		pin = 0;
		break;
	case ADC_CHANNEL_IN1:
		port = GPIOA;
		pin = 1;
		break;
	case ADC_CHANNEL_IN2:
		port = GPIOA;
		pin = 2;
		break;
	case ADC_CHANNEL_IN3:
		port = GPIOA;
		pin = 3;
		break;
	case ADC_CHANNEL_IN4:
		port = GPIOA;
		pin = 4;
		break;
	case ADC_CHANNEL_IN5:
		port = GPIOA;
		pin = 5;
		break;
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
		return;
	}
	initAdcPin(port, pin, "hw");
}

void initSlowChannel(int logicChannel, int hwChannel) {
	internalAdcIndex[hwChannel] = logicChannel;
	if (logicChannel < 6) {
		adcgrpcfg_slow.sqr3 += (hwChannel) << (5 * logicChannel);
	} else {
		adcgrpcfg_slow.sqr2 += (hwChannel) << (5 * (logicChannel - 6));
	}

	initAdcHwChannel(hwChannel);
}

static void printAdcValue(int channel) {
	int value = getAdcValue(channel);
	myfloat volts = adcToVolts(value);
	scheduleSimpleMsg(&logger, "adc voltage x100: ", (int) (100 * volts));
}

static void printFullAdcReport(void) {
	for (int i = 0; i < EFI_ADC_SLOW_CHANNELS_COUNT; i++) {
		msgInt(&logger, " ch", i);
		int value = getAdcValueByIndex(i);
		msgInt(&logger, " val= ", value);
		myfloat volts = adcToVolts(value);
		debugFloat(&logger, "v ", volts, 1);
	}
	scheduleLogging(&logger);
}

static void printStatus(void) {
	scheduleIntValue(&logger, ADC_DEBUG_KEY, adcDebugReporting);
}

static void setAdcDebugReporting(int value) {
	adcDebugReporting = value;
	printStatus();
}

void initAdcInputs() {

	initLoggingExt(&logger, "ADC", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));

	printStatus();

	addConsoleActionI(ADC_DEBUG_KEY, &setAdcDebugReporting);

#ifdef EFI_INTERNAL_ADC
	/*
	 * Initializes the ADC driver.
	 */
	adcStart(&ADC_SLOW, NULL);
	adcStart(&ADC_FAST, NULL);

	adcgrpcfg_slow.sqr2 = 0;
	adcgrpcfg_slow.sqr3 = 0;

	int index = 0;

#if EFI_USE_ADC_CHANNEL_IN0
	initSlowChannel(index++, ADC_CHANNEL_IN0); // PA0
#endif
#if EFI_USE_ADC_CHANNEL_IN1
	initSlowChannel(index++, ADC_CHANNEL_IN1); // PA1
#endif
#if EFI_USE_ADC_CHANNEL_IN2
	initSlowChannel(index++, ADC_CHANNEL_IN2); // PA2
#endif
#if EFI_USE_ADC_CHANNEL_IN3
	initSlowChannel(index++, ADC_CHANNEL_IN3); // PA3
#endif
#if EFI_USE_ADC_CHANNEL_IN4
	initSlowChannel(index++, ADC_CHANNEL_IN4); // PA4
#endif
#if EFI_USE_ADC_CHANNEL_IN5
	initSlowChannel(index++, ADC_CHANNEL_IN5); // PA5 - this is also TIM2_CH1
#endif
#if EFI_USE_ADC_CHANNEL_IN6
	initSlowChannel(index++, ADC_CHANNEL_IN6); // PA6
#endif
#if EFI_USE_ADC_CHANNEL_IN7
	initSlowChannel(index++, ADC_CHANNEL_IN7); // PA7
#endif
#if EFI_USE_ADC_CHANNEL_IN8
	initSlowChannel(index++, ADC_CHANNEL_IN8); // PB0
#endif
#if EFI_USE_ADC_CHANNEL_IN9
	initSlowChannel(index++, ADC_CHANNEL_IN9); // PB1
#endif
#if EFI_USE_ADC_CHANNEL_IN10
	initSlowChannel(index++, ADC_CHANNEL_IN10); // PC0
#endif
#if EFI_USE_ADC_CHANNEL_IN11
	initSlowChannel(index++, ADC_CHANNEL_IN11); // PC1
#endif
#if EFI_USE_ADC_CHANNEL_IN12
	initSlowChannel(index++, ADC_CHANNEL_IN12); // PC2
#endif
#if EFI_USE_ADC_CHANNEL_IN13
	initSlowChannel(index++, ADC_CHANNEL_IN13); // PC3
#endif
#if EFI_USE_ADC_CHANNEL_IN14
	initSlowChannel(index++, ADC_CHANNEL_IN14); // PC4
#endif
#if EFI_USE_ADC_CHANNEL_IN15
	initSlowChannel(index++, ADC_CHANNEL_IN15); // PC5
#endif

	if (index != EFI_ADC_SLOW_CHANNELS_COUNT)
		fatal("Invalud internal ADC config");

	/*
	 * Initializes the PWM driver.
	 */
	pwmStart(EFI_INTERNAL_SLOW_ADC_PWM, &pwmcfg_slow);
	pwmStart(EFI_INTERNAL_FAST_ADC_PWM, &pwmcfg_fast);
	addConsoleActionI("adc", printAdcValue);
	addConsoleAction("fadc", printFullAdcReport);
#else
	printSimpleMsg(&logger, "ADC disabled", 0);
#endif
}

void pokeAdcInputs() {
	if (!adcDebugReporting)
		return;
	printFullAdcReport();
}

