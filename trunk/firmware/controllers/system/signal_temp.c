/**
 * @file	signal_temp.c
 *
 * @date Apr 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

// https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/Flat.aspx?RootFolder=https%3a%2f%2fmy.st.com%2fpublic%2fSTe2ecommunities%2fmcu%2fLists%2fcortex_mx_stm32%2fInterrupt%20on%20CEN%20bit%20setting%20in%20TIM7&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580009C4E14902C3CDE46A77F0FFD06506F5B&currentviews=474


int globalCounter = 0;

static TIM_TypeDef *TIM = TIM5;

static void setTimer(int arr) {
	TIM->ARR = arr;
	TIM->EGR |= TIM_EGR_UG; // generate an update event to reload timer's counter value
	TIM->CR1 |= TIM_CR1_CEN; // restart timer
}

static void callback(void) {
	GPIOD->ODR ^= (1 << 13);   // Toggle D13

	globalCounter++;

	if (globalCounter < 6) {
		setTimer(499 * globalCounter);
	}
}

CH_FAST_IRQ_HANDLER(STM32_TIM5_HANDLER) {
	if (((TIM->SR & 0x0001) != 0) && ((TIM->DIER & 0x0001) != 0)) {
		callback();
	}
	TIM->SR = (int) ~STM32_TIM_SR_UIF;   // Interrupt has been handled
}


void TIM_Init(void)
{

	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;   // Enable TIM6 clock
	NVIC_EnableIRQ(TIM5_IRQn);   // Enable TIM6 IRQ
	TIM->DIER |= TIM_DIER_UIE;   // Enable interrupt on update event
	TIM->CR1 |= TIM_CR1_OPM; // one pulse mode: count down ARR and stop
	TIM->CR1 &= ~TIM_CR1_ARPE; /* ARR register is NOT buffered, allows to update timer's period on-fly. */

	TIM->PSC = 41999;   // Set prescaler to 41999

	setTimer(999);

}

