/**
 * @file	microsecond_timer.c
 *
 * Here we have a 1MHz timer dedicated to event scheduling. We are using one of the 32-bit timers here,
 * so this timer can schedule events up to 4B/100M ~ 4000 seconds ~ 1 hour from current time.
 *
 * @date Apr 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "signal_executor.h"
#include "microsecond_timer.h"

// https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/Flat.aspx?RootFolder=https%3a%2f%2fmy.st.com%2fpublic%2fSTe2ecommunities%2fmcu%2fLists%2fcortex_mx_stm32%2fInterrupt%20on%20CEN%20bit%20setting%20in%20TIM7&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580009C4E14902C3CDE46A77F0FFD06506F5B&currentviews=474

#if EFI_PROD_CODE

#define TIM TIM5
#define HW_TIMER_PRIORITY 12
#define HW_TIMER_IRQ TIM5_IRQn

static volatile int64_t lastSetTimerTime;
static volatile bool_t isTimerPending = FALSE;

static volatile int timerCallbackCounter = 0;
static volatile int timerRestartCounter = 0;

schfunc_t globalTimerCallback;

/**
 * sets the alarm to the specified number of microseconds from now.
 * This function should be invoked under kernel lock which would disable interrupts.
 */
void setHardwareUsTimer(int timeUs) {
	TIM->ARR = timeUs - 1;
	TIM->EGR |= TIM_EGR_UG; // generate an update event to reload timer's counter value
	TIM->CR1 |= TIM_CR1_CEN; // restart timer

	lastSetTimerTime = getTimeNowUs();
	isTimerPending = TRUE;
	timerRestartCounter++;
}

static void callback(void) {
	timerCallbackCounter++;
	if (globalTimerCallback == NULL) {
		firmwareError("NULL globalTimerCallback");
		return;
	}
	isTimerPending = FALSE;
	globalTimerCallback(NULL);
}

// if you decide to move this to .cpp do not forget to make that an extern "C" method
CH_IRQ_HANDLER(STM32_TIM5_HANDLER) {
	CH_IRQ_PROLOGUE();
	if (((TIM->SR & TIM_SR_UIF) != 0) && ((TIM->DIER & TIM_DIER_UIE) != 0))
		callback();
	TIM->SR = (int) ~STM32_TIM_SR_UIF;   // Interrupt has been handled
	CH_IRQ_EPILOGUE();
}

static WORKING_AREA(mwThreadStack, UTILITY_THREAD_STACK_SIZE);

static msg_t mwThread(int param) {
	chRegSetThreadName("timer watchdog");

	while (TRUE) {
		chThdSleepMilliseconds(1000); // once a second is enough

		const char * msg = isTimerPending ? "No callback for too long" : "Timer not reset for awhile";
		// 2 seconds of inactivity would not look right
		efiAssert(getTimeNowUs() < lastSetTimerTime + 2 * US_PER_SECOND, msg);
	}
	return -1;
}

void initMicrosecondTimer(void) {
	RCC ->APB1ENR |= RCC_APB1ENR_TIM5EN;   // Enable TIM5 clock
	nvicEnableVector(HW_TIMER_IRQ, CORTEX_PRIORITY_MASK(HW_TIMER_PRIORITY));
	TIM->DIER |= TIM_DIER_UIE;   // Enable interrupt on update event
	TIM->CR1 |= TIM_CR1_OPM; // one pulse mode: count down ARR and stop
	TIM->CR1 &= ~TIM_CR1_ARPE; /* ARR register is NOT buffered, allows to update timer's period on-fly. */

	TIM->PSC = 84 - 1;   // 168MHz / 2 / 84 = 1MHz, each tick is a microsecond

	lastSetTimerTime = getTimeNowUs();
	chThdCreateStatic(mwThreadStack, sizeof(mwThreadStack), NORMALPRIO, (tfunc_t)mwThread, NULL);
}

#endif /* EFI_PROD_CODE */
