/**
 * @file	joystick.cpp
 *
 * @date Jan 2, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "engine_configuration.h"
#include "joystick.h"
#include "engine.h"
#include "pin_repository.h"

#if HAL_USE_EXT || defined(__DOXYGEN__)

EXTERN_ENGINE
;

static int joyTotal = 0;
static int joyCenter;
static int joyA = 0;
static int joyB = 0;
static int joyC = 0;
static int joyD = 0;

#define NT_EVENT_GAP US2NT(1000)

static Logging *sharedLogger;
static efitick_t lastEventTime = 0;

static void extCallback(EXTDriver *extp, expchannel_t channel) {
	efitick_t now = getTimeNowNt();
	if (now - lastEventTime < NT_EVENT_GAP)
		return; // two consecutive events are probably just jitter
	lastEventTime = now;
	joyTotal++;
	joystick_button_e button;
	// todo: I guess it's time to reduce code duplication and start working with an array
	if (channel == getHwPin(boardConfiguration->joystickCenterPin)) {
		joyCenter++;
		button = JB_CENTER;
	} else if (channel == getHwPin(boardConfiguration->joystickAPin)) {
		joyA++;
		button = JB_BUTTON_A;
	} else if (channel == getHwPin(boardConfiguration->joystickBPin)) {
		joyB++;
		button = JB_BUTTON_C;
	} else if (channel == getHwPin(boardConfiguration->joystickCPin)) {
		joyC++;
		button = JB_BUTTON_B;
	} else if (channel == getHwPin(boardConfiguration->joystickDPin)) {
		joyD++;
		button = JB_BUTTON_D;
	} else {
		// unexpected channel
		return;
	}
#if EFI_HD44780_LCD || defined(__DOXYGEN__)
	onJoystick(button);
#endif
}

static void joystickInfo(void) {
	scheduleMsg(sharedLogger, "total %d center=%d@%s", joyTotal, joyCenter,
			hwPortname(boardConfiguration->joystickCenterPin));
	scheduleMsg(sharedLogger, "a=%d@%s", joyA, hwPortname(boardConfiguration->joystickAPin));
	scheduleMsg(sharedLogger, "b=%d@%s", joyB, hwPortname(boardConfiguration->joystickBPin));
	scheduleMsg(sharedLogger, "c=%d@%s", joyC, hwPortname(boardConfiguration->joystickCPin));
	scheduleMsg(sharedLogger, "d=%d@%s", joyD, hwPortname(boardConfiguration->joystickDPin));
}

/**
 * EXTI is a funny thing: you can only use same pin on one port. For example, you can use
 * PA0 PB5 PE2 PD7
 * but you cannot use
 * PA0 PB0 PE2 PD7
 * because pin '0' would be used on two different ports
 */

static EXTConfig extcfg = { {
/* CH#00 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#01 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#02 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#03 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#04 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#05 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#06 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#07 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#08 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#09 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#10 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#11 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#12 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#13 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#14 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#15 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#16 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#17 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#18 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#19 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#20 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#21 */{ EXT_CH_MODE_DISABLED, NULL },
/* CH#22 */{ EXT_CH_MODE_DISABLED, NULL } } };

static uint32_t getExtMode(GPIO_TypeDef * port) {
	if (port == GPIOA) {
		return EXT_MODE_GPIOA;
	} else if (port == GPIOB) {
		return EXT_MODE_GPIOB;
	} else if (port == GPIOC) {
		return EXT_MODE_GPIOC;
	} else if (port == GPIOD) {
		return EXT_MODE_GPIOD;
	} else if (port == GPIOE) {
		return EXT_MODE_GPIOE;
	} else if (port == GPIOF) {
		return EXT_MODE_GPIOF;
	}
	firmwareError("Unsupported %d", port);
	return 0;
}

static void applyPin(brain_pin_e pin) {
	if (pin == GPIO_UNASSIGNED)
		return;

	int index = getHwPin(pin);
	GPIO_TypeDef * port = getHwPort(pin);

	extcfg.channels[index].mode = EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | getExtMode(port);
	extcfg.channels[index].cb = extCallback;
}

void initJoystick(Logging *shared) {
	if (!engineConfiguration->isJoystickEnabled)
		return;
	sharedLogger = shared;

	applyPin(boardConfiguration->joystickCenterPin);
	applyPin(boardConfiguration->joystickAPin);
	applyPin(boardConfiguration->joystickBPin);
	applyPin(boardConfiguration->joystickCPin);
	applyPin(boardConfiguration->joystickDPin);

	mySetPadMode2("joy center", boardConfiguration->joystickCenterPin, PAL_MODE_INPUT_PULLUP);
	mySetPadMode2("joy A", boardConfiguration->joystickAPin, PAL_MODE_INPUT_PULLUP);
	mySetPadMode2("joy B", boardConfiguration->joystickBPin, PAL_MODE_INPUT_PULLUP);
	mySetPadMode2("joy C", boardConfiguration->joystickCPin, PAL_MODE_INPUT_PULLUP);
	mySetPadMode2("joy D", boardConfiguration->joystickDPin, PAL_MODE_INPUT_PULLUP);

	addConsoleAction("joystickinfo", joystickInfo);

	extStart(&EXTD1, &extcfg);
}

#endif
