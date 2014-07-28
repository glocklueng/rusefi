/*
 * @file	wave_analyzer_hw.c
 * @brief	Helper methods related to Input Capture Unit (ICU)
 *
 * @date Jun 23, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "wave_analyzer_hw.h"
#include "eficonsole.h"
#include "pin_repository.h"

static void icuWidthCallback(ICUDriver *driver);
static void icuPeriordCallBack(ICUDriver *driver);

/*
 * 30ms seems like width maximum, at 16bit precision that means
 * CORE_CLOCK / 33.33333 = TICKS * 65536
 * 168000000 / 33.333333 / 65536 = 76.90
 */
static ICUConfig wave_icucfg = { ICU_INPUT_ACTIVE_LOW, CORE_CLOCK / 100, icuWidthCallback, icuPeriordCallBack, 0, ICU_CHANNEL_1, 0 };

static int registeredIcuCount = 0;
static WaveReaderHw* registeredIcus[8];

static WaveReaderHw * findWaveReaderHw(ICUDriver *driver) {
  for (int i = 0; i < registeredIcuCount; i++) {
          if (registeredIcus[i]->driver == driver) {
			return registeredIcus[i];
          }
  }
	firmwareError("reader not found");
	return (WaveReaderHw *)NULL;
}

static void icuWidthCallback(ICUDriver *driver) {
	/*
	 * see comment in icuPeriordCallBack
	 int rowWidth = icuGetWidth(driver);
	 */
	WaveReaderHw * hw = findWaveReaderHw(driver);
	invokeJustArgCallbacks(&hw->widthListeners);
}

static void icuPeriordCallBack(ICUDriver *driver) {
	/*
	 * 	we do not use timer period at all - we just need the event. For all time characteristics,
	 * 	we use system time
	 * 	int period = icuGetPeriod(driver);
	 */

	WaveReaderHw * hw = findWaveReaderHw(driver);
	invokeJustArgCallbacks(&hw->periodListeners);
}

static uint32_t getAlternateFunctions(ICUDriver *driver) {
	if (driver == NULL) {
		firmwareError("getAlternateFunctions(NULL)");
		return 0xffffffff;
	}
#if STM32_ICU_USE_TIM1
	if (driver == &ICUD1) {
		return GPIO_AF_TIM1;
        }
#endif
#if STM32_ICU_USE_TIM2
	if (driver == &ICUD2) {
		return GPIO_AF_TIM2;
        }
#endif
#if STM32_ICU_USE_TIM3
	if (driver == &ICUD3) {
		return GPIO_AF_TIM3;
        }
#endif
#if STM32_ICU_USE_TIM4
	if (driver == &ICUD4) {
	return GPIO_AF_TIM4;
        }
#endif
#if STM32_ICU_USE_TIM9
	if (driver == &ICUD9) {
		return GPIO_AF_TIM9;
        }
#endif
	firmwareError("No such driver");
	return 0xffffffff;
}

ICUDriver * getInputCaptureDriver(brain_pin_e hwPin) {
#if STM32_ICU_USE_TIM1
  if (hwPin == GPIOA_8) {
		return &ICUD1;
  }
#endif
#if STM32_ICU_USE_TIM2
	if (hwPin == GPIOA_5) {
		return &ICUD2;
        }
#endif
#if STM32_ICU_USE_TIM3
	if (hwPin == GPIOC_6) {
		return &ICUD3;
        }
#endif
#if STM32_ICU_USE_TIM9
	if (hwPin == GPIOE_7) {
		return &ICUD9;
        }
#endif
	return (ICUDriver *)NULL;
}

void initWaveAnalyzerDriver(WaveReaderHw *hw, ICUDriver *driver, ioportid_t port, ioportmask_t pin) {
	hw->driver = driver;
	hw->port = port;
	hw->pin = pin;
        iomode_t mode = (iomode_t)PAL_MODE_ALTERNATE(getAlternateFunctions(driver));
	mySetPadMode("wave input", port, pin, mode);

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
}
