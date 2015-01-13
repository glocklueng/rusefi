/**
 * @file	io_pins.c
 * @brief	It could be that the main purpose of this file is the status LED blinking
 *
 * @date Jan 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include <board.h>
#include "main.h"
#include "io_pins.h"
#include "efiGpio.h"

#include "pin_repository.h"
#include "gpio_helper.h"
#include "status_loop.h"
#include "engine_configuration.h"
#include "console_io.h"

#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)
#include "main_trigger_callback.h"
#endif /* EFI_ENGINE_CONTROL */

extern board_configuration_s *boardConfiguration;

static Logging logger;

static OutputPin sdCsPin;

extern NamedOutputPin outputs[IO_PIN_COUNT];
extern engine_pins_s enginePins;

#if defined(STM32F4XX)
static GPIO_TypeDef *PORTS[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH };
#else
static GPIO_TypeDef *PORTS[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOF};
#endif

pin_output_mode_e DEFAULT_OUTPUT = OM_DEFAULT;

static void outputPinRegisterExt(const char *msg, OutputPin *output, GPIO_TypeDef *port, uint32_t pin,
		pin_output_mode_e *outputMode) {
#if EFI_GPIO
	if (port == GPIO_NULL) {
		// that's for GRIO_NONE
		output->port = port;
		return;
	}

	assertOMode(*outputMode);
	iomode_t mode = (*outputMode == OM_DEFAULT || *outputMode == OM_INVERTED) ?
	PAL_MODE_OUTPUT_PUSHPULL :
																				PAL_MODE_OUTPUT_OPENDRAIN;

	initOutputPinExt(msg, output, port, pin, mode);

	output->setDefaultPinState(outputMode);
#endif
}

GPIO_TypeDef * getHwPort(brain_pin_e brainPin) {
	if (brainPin == GPIO_UNASSIGNED)
		return GPIO_NULL;
	if (brainPin > GPIO_UNASSIGNED || brainPin < 0) {
		firmwareError("Invalid brain_pin_e: %d", brainPin);
		return GPIO_NULL;
	}
	return PORTS[brainPin / 16];
}

ioportmask_t getHwPin(brain_pin_e brainPin) {
	if (brainPin == GPIO_UNASSIGNED)
		return EFI_ERROR_CODE;
	if (brainPin > GPIO_UNASSIGNED || brainPin < 0) {
		firmwareError("Invalid brain_pin_e: %d", brainPin);
		return EFI_ERROR_CODE;
	}
	return brainPin % 16;
}

void outputPinRegisterExt2(const char *msg, OutputPin *output, brain_pin_e brainPin, pin_output_mode_e *outputMode) {
	if (brainPin == GPIO_UNASSIGNED)
		return;
	GPIO_TypeDef *hwPort = getHwPort(brainPin);
	int hwPin = getHwPin(brainPin);

	outputPinRegisterExt(msg, output, hwPort, hwPin, outputMode);
}

void outputPinRegister(const char *msg, OutputPin *output, GPIO_TypeDef *port, uint32_t pin) {
	outputPinRegisterExt(msg, output, port, pin, &DEFAULT_OUTPUT);
}

OutputPin errorLedPin;
extern OutputPin checkEnginePin;

void initPrimaryPins(void) {
	outputPinRegister("LED_ERROR", &errorLedPin, LED_ERROR_PORT, LED_ERROR_PIN);
}

static void getPinValue(const char *name) {
	io_pin_e pin = getPinByName(name);
	if (pin == IO_INVALID) {
		return;
	}
	OutputPin * outputPin = &outputs[pin];
	int value = outputPin->getLogicValue();
	scheduleMsg(&logger, "pin_value %s %d", name, value);
}

void initOutputPins(void) {
	initLogging(&logger, "io_pins");

	for (int i = 0; i < IO_PIN_COUNT;i++)
		outputs[i].name = getPinName((io_pin_e)i);

	/**
	 * want to make sure it's all zeros so that we can compare in initOutputPinExt() method
	 */
// todo: it's too late to clear now? this breaks default status LEDs
// todo: fix this?
//	memset(&outputs, 0, sizeof(outputs));
//	outputPinRegister("ext led 1", LED_EXT_1, EXTRA_LED_1_PORT, EXTRA_LED_1_PIN);
//	outputPinRegister("ext led 2", LED_EXT_2, EXTRA_LED_2_PORT, EXTRA_LED_2_PIN);
//	outputPinRegister("ext led 3", LED_EXT_3, EXTRA_LED_2_PORT, EXTRA_LED_3_PIN);
//	outputPinRegister("alive1", LED_DEBUG, GPIOD, 6);
	outputPinRegisterExt2("MalfunctionIndicator", &checkEnginePin, boardConfiguration->malfunctionIndicatorPin, &DEFAULT_OUTPUT);

// todo: are these needed here? todo: make configurable
//	outputPinRegister("spi CS1", SPI_CS_1, SPI_CS1_PORT, SPI_CS1_PIN);
//	outputPinRegister("spi CS2", SPI_CS_2, SPI_CS2_PORT, SPI_CS2_PIN);
//	outputPinRegister("spi CS3", SPI_CS_3, SPI_CS3_PORT, SPI_CS3_PIN);
//	outputPinRegister("spi CS4", SPI_CS_4, SPI_CS4_PORT, SPI_CS4_PIN);
#if HAL_USE_SPI || defined(__DOXYGEN__)
	outputPinRegister("spi CS5", &sdCsPin, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN);
#endif

	// todo: should we move this code closer to the fuel pump logic?
	outputPinRegisterExt2("fuel pump relay", &enginePins.fuelPumpRelay, boardConfiguration->fuelPumpPin, &DEFAULT_OUTPUT);

	outputPinRegisterExt2("main relay", &enginePins.mainRelay, boardConfiguration->mainRelayPin, &boardConfiguration->mainRelayPinMode);

	outputPinRegisterExt2("fan relay", &enginePins.fanRelay, boardConfiguration->fanPin, &DEFAULT_OUTPUT);
	outputPinRegisterExt2("o2 heater", &enginePins.o2heater, boardConfiguration->o2heaterPin, &DEFAULT_OUTPUT);
	outputPinRegisterExt2("A/C relay", &enginePins.acRelay, boardConfiguration->acRelayPin, &boardConfiguration->acRelayPinMode);

	// digit 1
	/*
	 ledRegister(LED_HUGE_0, GPIOB, 2);
	 ledRegister(LED_HUGE_1, GPIOE, 7);
	 ledRegister(LED_HUGE_2, GPIOE, 8);
	 ledRegister(LED_HUGE_3, GPIOE, 9);
	 ledRegister(LED_HUGE_4, GPIOE, 10);
	 ledRegister(LED_HUGE_5, GPIOE, 11);
	 ledRegister(LED_HUGE_6, GPIOE, 12);

	 // digit 2
	 ledRegister(LED_HUGE_7, GPIOE, 13);
	 ledRegister(LED_HUGE_8, GPIOE, 14);
	 ledRegister(LED_HUGE_9, GPIOE, 15);
	 ledRegister(LED_HUGE_10, GPIOB, 10);
	 ledRegister(LED_HUGE_11, GPIOB, 11);
	 ledRegister(LED_HUGE_12, GPIOB, 12);
	 ledRegister(LED_HUGE_13, GPIOB, 13);

	 // digit 3
	 ledRegister(LED_HUGE_14, GPIOE, 0);
	 ledRegister(LED_HUGE_15, GPIOE, 2);
	 ledRegister(LED_HUGE_16, GPIOE, 4);
	 ledRegister(LED_HUGE_17, GPIOE, 6);
	 ledRegister(LED_HUGE_18, GPIOE, 5);
	 ledRegister(LED_HUGE_19, GPIOE, 3);
	 ledRegister(LED_HUGE_20, GPIOE, 1);
	 */

	addConsoleActionS("get_pin_value", getPinValue);
}

#if EFI_GPIO

static io_pin_e TO_BE_TURNED_OFF_ON_ERROR[] = { SPARKOUT_1_OUTPUT, SPARKOUT_2_OUTPUT, SPARKOUT_3_OUTPUT,
		SPARKOUT_4_OUTPUT, SPARKOUT_5_OUTPUT, SPARKOUT_6_OUTPUT, SPARKOUT_7_OUTPUT, SPARKOUT_8_OUTPUT,
		SPARKOUT_9_OUTPUT, SPARKOUT_10_OUTPUT, SPARKOUT_11_OUTPUT, SPARKOUT_12_OUTPUT,

		INJECTOR_1_OUTPUT, INJECTOR_2_OUTPUT, INJECTOR_3_OUTPUT, INJECTOR_4_OUTPUT, INJECTOR_5_OUTPUT,
		INJECTOR_6_OUTPUT, INJECTOR_7_OUTPUT, INJECTOR_8_OUTPUT, INJECTOR_9_OUTPUT, INJECTOR_10_OUTPUT,
		INJECTOR_11_OUTPUT, INJECTOR_12_OUTPUT };

/**
 * This method is part of fatal error handling.
 * Please note that worst case scenario the pins might get re-enabled by some other code :(
 * The whole method is pretty naive, but that's at least something.
 */
void turnAllPinsOff(void) {
	int l = sizeof(TO_BE_TURNED_OFF_ON_ERROR) / sizeof(io_pin_e);
	for (int i = 0; i < l; i++) {
		OutputPin *output = &outputs[TO_BE_TURNED_OFF_ON_ERROR[l]];
		output->setValue(false);
	}
}
#endif
