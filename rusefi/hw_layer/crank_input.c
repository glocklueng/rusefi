/*
 * chibi_input_capture.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "crank_input.h"

#include "rficonsole.h"

#include "wave_math.h"
#include "data_buffer.h"
#include "ckp_events.h"
#include "pin_repository.h"

/**
 * ChibiOS uses only one channel 1
 *
 * TIM4_CH1
 *  PB6
 * 	PD12
 */

IntListenerArray ckpListeneres;

static volatile systime_t crankWidthTime;
static volatile systime_t crankPeriodTime;

#if RE_CRANK_INPUT
// 'width' happens before the 'period' event
static void crank_icuwidthcb(ICUDriver *icup) {
	crankWidthTime = chTimeNow();
//	icucnt_t last_width = icuGetWidth(icup);

	invokeCallbacks(&ckpListeneres, CKP_PRIMARY_FALL);
}

static void crank_icuperiodcb(ICUDriver *icup) {
	crankPeriodTime = chTimeNow();
//	icucnt_t last_period = icuGetPeriod(icup);

	invokeCallbacks(&ckpListeneres, CKP_PRIMARY_RISE);
}
#endif
systime_t getCrankWidthTime() {
	return crankWidthTime;
}

systime_t getCrankPeriodTime() {
	return crankPeriodTime;
}

#if RE_CRANK_INPUT
static ICUConfig crank_icucfg = { ICU_INPUT_ACTIVE_LOW, 100000, /* 100kHz ICU clock frequency.   */
crank_icuwidthcb, crank_icuperiodcb };
#endif

void registerCkpListener(IntListener handler, char *msg) {
	print("registerCkpListener: %s\r\n", msg);
	registerCallback(&ckpListeneres, handler);
}

void initInputCapture() {

#if RE_CRANK_INPUT

	icuStart(&CRANK_DRIVER, &crank_icucfg);
	icuEnable(&CRANK_DRIVER);
	mySetPadMode("crank input", CRANK_INPUT_PORT, CRANK_INPUT_PIN,
			PAL_MODE_ALTERNATE(CRANK_AF));
#else
	print("crank input disabled\r\n");
#endif
}
