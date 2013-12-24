/**
 * @file	signal_executor_single_timer.c
 * @brief Single timer based implementation of signal executor.
 *
 * All active outputs are stored in "output_list".
 * Closest in time output event is loaded in timer TIM7.
 * In TIM7 timer's interrupt next closest in time output event is found and so on.
 * This algorithm should reduce jitter in output signal.
 *
 * @todo Add test code.
 *
 * @date Nov 27, 2013
 * @author Dobrin Georgiev
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <stdint.h>
#include <stm32_tim.h>
#include "hal.h"
#include "utlist.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "signal_executor_single_timer_algo.h"

#if EFI_WAVE_ANALYZER
#include "wave_chart.h"
/**
 * Signal executors feed digital events right into WaveChart used by Sniffer tab of Dev Console
 */
extern WaveChart waveChart;
#endif /* EFI_WAVE_ANALYZER */

#if EFI_SIGNAL_EXECUTOR_SINGLE_TIMER

/**
 * @brief Output list
 *
 * List of all active output signals
 * This is actually the head of the list.
 * When the list is empty (initial state) the head of the list should be NULL.
 * This is by design.
 */
static OutputSignal *output_list = NULL;

/**
 * @brief Schedule output
 *
 * Set new parametrs to output event.
 * When to become active and how long to stay active.
 *
 * @param [in, out] signal Signal related to an output.
 * @param [in] delay the number of ticks before the output signal immediate output if delay is zero.
 * @param [in] dwell the number of ticks of output duration.
 */
void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
	chDbgCheck(signal->initialized, "Signal not initialized");
	chDbgCheck(dwell >= 0, "dwell cannot be negative");

	signal->duration = dwell;
	signal->offset = delay;

	/* generate an update event to reload timer's counter value, according to new set of output timings */
	TIM7->EGR |= TIM_EGR_UG;
}

/**
 * @brief Initialization of output scheduler.
 *
 * TIM7 timer initil settings.
 */
void initOutputScheduler(void)
{
	/**
	 * @brief TIM7 initialization. Timer should run at 42MHz and before any output event registered should generate ISR event each milisecond.
	 */
	/**
	 * @todo Find general macros for CPU ticks to milliseconds or add such a macro!
	 */
	uint32_t initial_interval = STM32_PCLK1/1000; /// clock ticks per 1msec
#if 0
#pragma message VAR_NAME_VALUE(STM32_PCLK1)" <= "VAR_NAME_VALUE(STM32_PCLK1_MAX)
#pragma message VAR_NAME_VALUE(STM32_PPRE1)
#endif
	nvicEnableVector(TIM7_IRQn, CORTEX_PRIORITY_MASK(2));
	TIM7->ARR = initial_interval;		/* Timer's period */
	TIM7->PSC = 0;				/* No prescaler */
	TIM7->CR1 &= ~STM32_TIM_CR1_ARPE;	/* ARR register is NOT buffered, allows to update timer's period on-fly. */
	TIM7->DIER |= STM32_TIM_DIER_UIE;	/* Interrupt enable */
	TIM7->CR1 |= STM32_TIM_CR1_CEN;		/* Counter enable */
}

/**
 * @brief Timer7 IRQ handler
 *
 * This is the core of "Single Timer" signal executor.
 * Each time closest in time output event is found and TIM7 is loaded to generate IRQ at exact moment.
 * FAST IRQ handler is used to minimaze the jitter in output signal, caused by RTOS switching threads and by busy threads.
 * Timer7 is used as output scheduler (to drive all outputs - spark plugs and fuel injectors).
 */
CH_FAST_IRQ_HANDLER(STM32_TIM7_HANDLER)
{
#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define PRESCALLER ((STM32_HCLK) / (STM32_PCLK1))
/* Convert chSys tick to CPU tick */
#define ST2CT(st) ((st) * (STM32_SYSCLK) / (CH_FREQUENCY))
//#pragma message VAR_NAME_VALUE(STM32_SYSCLK)
#define GET_DURATION(o) ((o)->status ? (o)->duration : (o)->offset)
	OutputSignal *out;
	time_t next;	/* Time to next output event */
	time_t now;

	now = chTimeNow();
	next = S2ST(1); /* one second in system ticks */
	LL_FOREACH(output_list, out) {
		time_t n = toggleSignalIfNeeded(out, now);
		/* Find closest output event in time */
		next = MIN(next, n);
	}
	if (next) {
		TIM7->ARR = ST2CT(next) / PRESCALLER;	/* Update scheduler timing */
	}
	TIM7->SR &= ~STM32_TIM_SR_UIF;	/* Reset interrupt flag */
}

/**
 * @brief Initialize output signal.
 *
 * @param [in] name Signal name.
 * @param [in, out] signal Output signal.
 * @param [in] led LED
 * @param [in] xor Option to invert output signal.
 */
void initOutputSignal(char *name, OutputSignal *signal, int led, int xor) {
	initLogging(&signal->logging, name);

	signal->ledIndex = led;
	signal->xor = xor;
	signal->name = name;
	signal->duration = 0;
	setOutputPinValue(led, xor); // initial state
	registerSignal(signal);
	signal->initialized = TRUE;
}
#endif /* EFI_SIGNAL_EXECUTOR_SINGLE_TIMER */
