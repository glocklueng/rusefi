/**
 * @file    pin_repository.cpp
 * @brief   I/O pin registry code
 *
 * This job of this class is to make sure that we are not using same hardware pin for two
 * different purposes.
 *
 * @date Jan 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "pin_repository.h"
#include "eficonsole.h"
#include "memstreams.h"
#include "chprintf.h"
#include "rusefi.h"

#define PIN_REPO_SIZE 7 * PORT_SIZE
const char *PIN_USED[PIN_REPO_SIZE];
static int initialized = FALSE;

static LoggingWithStorage logger("pin repos");
static int totalPinsUsed = 0;

static GPIO_TypeDef* ports[7] = {GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOH,
};

/**
 * @deprecated - use hwPortname() instead
 */
const char *portname(GPIO_TypeDef* GPIOx) {
	if (GPIOx == GPIOA)
		return "PA";
	if (GPIOx == GPIOB)
		return "PB";
	if (GPIOx == GPIOC)
		return "PC";
	if (GPIOx == GPIOD)
		return "PD";
#if defined(STM32F4XX)
	if (GPIOx == GPIOE)
		return "PE";
	if (GPIOx == GPIOH)
		return "PH";
#endif
	if (GPIOx == GPIOF)
		return "PF";
	return "unknown";
}

static int getPortIndex(GPIO_TypeDef* port) {
	if (port == GPIOA)
		return 0;
	if (port == GPIOB)
		return 1;
	if (port == GPIOC)
		return 2;
	if (port == GPIOD)
		return 3;
#if defined(STM32F4XX)
	if (port == GPIOE)
		return 4;
#endif /* defined(STM32F4XX) */
	if (port == GPIOF)
		return 5;
#if defined(STM32F4XX)
	if (port == GPIOH)
		return 6;
#endif /* defined(STM32F4XX) */
	firmwareError("portindex");
	return -1;
}

static void reportPins(void) {
	for (int i = 0; i < PIN_REPO_SIZE; i++) {
		const char *name = PIN_USED[i];
		int portIndex = i / PORT_SIZE;
		int pin = i % PORT_SIZE;
		GPIO_TypeDef* port = ports[portIndex];
		if (name != NULL) {
			scheduleMsg(&logger, "pin %s%d: %s", portname(port), pin, name);
		}
	}

	scheduleMsg(&logger, "Total pins count: %d", totalPinsUsed);
}

static MemoryStream portNameStream;
static char portNameBuffer[20];

/**
 * Parse string representation of physical pin into brain_pin_e ordinal.
 *
 * @return GPIO_UNASSIGNED for "none", GPIO_INVALID for invalid entry
 */
brain_pin_e parseBrainPin(const char *str) {
	if (strEqual(str, "none"))
		return GPIO_UNASSIGNED;
	// todo: create method toLowerCase?
	if (str[0] != 'p' && str[0] != 'P') {
		return GPIO_INVALID;
	}
	char port = str[1];
	brain_pin_e basePin;
	if (port >= 'a' && port <= 'z') {
		basePin = (brain_pin_e) ((int) GPIOA_0 + 16 * (port - 'a'));
	} else if (port >= 'A' && port <= 'Z') {
		basePin = (brain_pin_e) ((int) GPIOA_0 + 16 * (port - 'A'));
	} else {
		return GPIO_INVALID;
	}
	const char *pinStr = str + 2;
	int pin = atoi(pinStr);
	return (brain_pin_e)(basePin + pin);
}

const char *hwPortname(brain_pin_e brainPin) {
	if (brainPin == GPIO_INVALID) {
		return "INVALID";
	}
	GPIO_TypeDef *hwPort = getHwPort(brainPin);
	if (hwPort == GPIO_NULL) {
		return "NONE";
	}
	int hwPin = getHwPin(brainPin);
	portNameStream.eos = 0; // reset
	chprintf((BaseSequentialStream *) &portNameStream, "%s%d", portname(hwPort), hwPin);
	portNameStream.buffer[portNameStream.eos] = 0; // need to terminate explicitly
	return portNameBuffer;
}

void initPinRepository(void) {
	/**
	 * this method cannot use console because this method is invoked before console is initialized
	 */

	msObjectInit(&portNameStream, (uint8_t*) portNameBuffer, sizeof(portNameBuffer), 0);

	for (int i = 0; i < PIN_REPO_SIZE; i++)
		PIN_USED[i] = 0;
	initialized = true;
	addConsoleAction("pins", reportPins);
}

static inline void markUsed(int index, const char *msg) {
	PIN_USED[index] = msg;
	totalPinsUsed++;
}

void mySetPadMode2(const char *msg, brain_pin_e pin, iomode_t mode) {
	mySetPadMode(msg, getHwPort(pin), getHwPin(pin), mode);
}

iomode_t getInputMode(pin_input_mode_e mode) {
	switch (mode) {
	case PI_PULLUP:
		return PAL_MODE_INPUT_PULLUP;
	case PI_PULLDOWN:
		return PAL_MODE_INPUT_PULLDOWN;
	case PI_DEFAULT:
	default:
		return PAL_MODE_INPUT;
	}
}

static int getIndex(ioportid_t port, ioportmask_t pin) {
	int portIndex = getPortIndex(port);
	return portIndex * PORT_SIZE + pin;
}

const char * getPinFunction(brain_input_pin_e brainPin) {
	ioportid_t port = getHwPort(brainPin);
	ioportmask_t pin = getHwPin(brainPin);

	int index = getIndex(port, pin);
	return PIN_USED[index];
}

/**
 * This method would set an error condition if pin is already used
 */
void mySetPadMode(const char *msg, ioportid_t port, ioportmask_t pin, iomode_t mode) {
	if (!initialized) {
		firmwareError("repository not initialized");
		return;
	}
	if (port == GPIO_NULL)
		return;
	print("%s on %s:%d\r\n", msg, portname(port), pin);

	appendPrintf(&logger, "msg,%s", msg);
	appendPrintf(&logger, " on %s%d%s", portname(port), pin, DELIMETER);
	printLine(&logger);

	int index = getIndex(port, pin);

	if (PIN_USED[index] != NULL) {
		/**
		 * todo: the problem is that this warning happens before the console is even
		 * connected, so the warning is never displayed on the console and that's quite a problem!
		 */
//		warning(OBD_PCM_Processor_Fault, "%s%d req by %s used by %s", portname(port), pin, msg, PIN_USED[index]);
		firmwareError("%s%d req by %s used by %s", portname(port), pin, msg, PIN_USED[index]);
		return;
	}
	markUsed(index, msg);

	palSetPadMode(port, pin, mode);
}

void unmarkPin(brain_pin_e brainPin) {
	ioportid_t port = getHwPort(brainPin);
	ioportmask_t pin = getHwPin(brainPin);

	int index = getIndex(port, pin);

	if (PIN_USED[index] != NULL) {
		PIN_USED[index] = NULL;
		totalPinsUsed--;
	}
}

/**
 * This method would crash the program if pin is already in use
 */
void registedFundamentralIoPin(char *msg, ioportid_t port, ioportmask_t pin, iomode_t mode) {
	efiAssertVoid(initialized, "repo not initialized");

	int index = getIndex(port, pin);

	if (PIN_USED[index] != NULL) {
		print("!!!!!!!!!!!!! Already used [%s] %d\r\n", msg, pin);
		print("!!!!!!!!!!!!! Already used by [%s]\r\n", PIN_USED[index]);
		firmwareError("pin already used");
		return;
	}
	markUsed(index, msg);
	palSetPadMode(port, pin, mode);
}

void efiIcuStart(ICUDriver *icup, const ICUConfig *config) {
	  efiAssertVoid((icup->state == ICU_STOP) || (icup->state == ICU_READY),
	              "input already used?");

	icuStart(icup, config);
}
