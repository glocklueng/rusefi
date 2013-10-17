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
#include "wave_analyzer_hw.h"
#include "pinout.h"

/**
 * ChibiOS uses only one channel 1
 *
 * TIM4_CH1
 *  PB6
 * 	PD12
 */

IntListenerArray ckpListeneres;

static volatile int crpEventCounter;

static WaveReaderHw primaryCrankInput;
static WaveReaderHw secondaryCrankInput;

int getCrankEventCounter() {
	return crpEventCounter;
}

#if EFI_CRANK_INPUT
// 'width' happens before the 'period' event
static void crank_icuwidthcb(ICUDriver *icup) {
	// this is not atomic, but it's fine here
	crpEventCounter++;
//	icucnt_t last_width = icuGetWidth(icup);
	if (icup == &PRIMARY_CRANK_DRIVER) {
		invokeCallbacks(&ckpListeneres, CKP_PRIMARY_UP);
	} else {
		invokeCallbacks(&ckpListeneres, CKP_SECONDARY_UP);
	}
}

static void crank_icuperiodcb(ICUDriver *icup) {
	// this is not atomic, but it's fine here
	crpEventCounter++;
//	icucnt_t last_period = icuGetPeriod(icup);

	if (icup == &PRIMARY_CRANK_DRIVER) {
		invokeCallbacks(&ckpListeneres, CKP_PRIMARY_DOWN);
	} else {
		invokeCallbacks(&ckpListeneres, CKP_SECONDARY_DOWN);
	}
}

static ICUConfig crank_icucfg = { ICU_INPUT_ACTIVE_LOW, 100000, /* 100kHz ICU clock frequency.   */
crank_icuwidthcb, crank_icuperiodcb };
#endif

void registerCkpListener(IntListener handler, char *msg) {
	print("registerCkpListener: %s\r\n", msg);
	registerCallback(&ckpListeneres, handler, NULL);
}

void initInputCapture() {

#if EFI_CRANK_INPUT

	initWaveAnalyzerDriver(&primaryCrankInput, &PRIMARY_CRANK_DRIVER, PRIMARY_CRANK_INPUT_PORT,
	PRIMARY_CRANK_INPUT_PIN);
	icuStart(&PRIMARY_CRANK_DRIVER, &crank_icucfg);
	icuEnable(&PRIMARY_CRANK_DRIVER);

	initWaveAnalyzerDriver(&secondaryCrankInput, &SECONDARY_CRANK_DRIVER, SECONDARY_CRANK_INPUT_PORT,
	SECONDARY_CRANK_INPUT_PIN);
	icuStart(&SECONDARY_CRANK_DRIVER, &crank_icucfg);
	icuEnable(&SECONDARY_CRANK_DRIVER);

#else
	print("crank input disabled\r\n");
#endif
}
