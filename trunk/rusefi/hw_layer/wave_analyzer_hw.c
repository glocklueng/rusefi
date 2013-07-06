/*
 * wave_analyzer_hw.c
 *
 *  Created on: Jun 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "wave_analyzer_hw.h"
#include "rficonsole.h"
#include "pin_repository.h"

#if 1

static void icuWidthCallback(ICUDriver *driver);
static void icuPeriordCallBack(ICUDriver *driver);

/*
 * 30ms seems like width maximum, at 16bit precision that means
 * CORE_CLOCK / 33.33333 = TICKS * 65536
 * 168000000 / 33.333333 / 65536 = 76.90
 */
static ICUConfig wave_icucfg = { ICU_INPUT_ACTIVE_LOW, CORE_CLOCK / 100,
		icuWidthCallback, icuPeriordCallBack };

static int registeredIcuCount = 0;
static WaveReaderHw* registeredIcus[8];

static WaveReaderHw * findWaveReaderHw(ICUDriver *driver) {
	for (int i = 0; i < registeredIcuCount; i++)
		if (registeredIcus[i]->driver == driver)
			return registeredIcus[i];
	fatal("reader not found\r\n");
	return NULL;
}

static void icuWidthCallback(ICUDriver *driver) {
	int rowWidth = icuGetWidth(driver);

	WaveReaderHw * hw = findWaveReaderHw(driver);
	invokeArgCallbacks(&hw->widthListeners, rowWidth);
}

static void icuPeriordCallBack(ICUDriver *driver) {
	int period = icuGetPeriod(driver);

	WaveReaderHw * hw = findWaveReaderHw(driver);
	invokeArgCallbacks(&hw->periodListeners, period);
}

static int getAlt(ICUDriver *driver) {
#if STM32_ICU_USE_TIM1
	if (driver == &ICUD1)
		return GPIO_AF_TIM1;
#endif
#if STM32_ICU_USE_TIM2
	if (driver == &ICUD2)
		return GPIO_AF_TIM2;
#endif
#if STM32_ICU_USE_TIM3
	if (driver == &ICUD3)
		return GPIO_AF_TIM3;
#endif
#if STM32_ICU_USE_TIM4
	if (driver == &ICUD4)
	return GPIO_AF_TIM4;
#endif
#if STM32_ICU_USE_TIM9
	if (driver == &ICUD9)
	return GPIO_AF_TIM9;
#endif
	fatal("No such driver");
	return -1;
}

void initWaveAnalyzerDriver(WaveReaderHw *hw, ICUDriver *driver,
		ioportid_t *port, int pin) {
	hw->driver = driver;
	hw->port = port;
	hw->pin = pin;
	mySetPadMode("wave input", port, pin, PAL_MODE_ALTERNATE(getAlt(driver)));

//	hw->widthListeners.currentListenersCount = 0;

	registeredIcus[registeredIcuCount++] = hw;
}

void setWaveReaderMode(WaveReaderHw *hw, int mode) {
	hw->activeMode = mode;
	if (hw->activeMode) {
		wave_icucfg.mode = ICU_INPUT_ACTIVE_HIGH;
	} else {
		wave_icucfg.mode = ICU_INPUT_ACTIVE_LOW;
	}
	ICUDriver *driver = hw->driver;

	if (hw->started) {
		icuDisable(driver);
		icuStop(driver);
	}
	icuStart(driver, &wave_icucfg);
	icuEnable(driver);
	hw->started = TRUE;
#endif
}
