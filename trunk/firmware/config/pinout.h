/*
 * pinout.h
 *
 *  Created on: Aug 29, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef PINOUT_H_
#define PINOUT_H_

#if EFI_SHAFT_POSITION_INPUT
/**
 * currently ChibiOS uses only first channel of each timer for input capture
 *
 * So, our options are:
 *
 * TIM2_CH1
 *  PA5
 *
 * TIM4_CH1
 *  PB6
 * 	PD12
 *
 * TIM9_CH1
 *  PE5
 */

#endif

#endif /* PINOUT_H_ */
