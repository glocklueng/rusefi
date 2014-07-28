/**
 * @file	poten.c
 * @brief	MCP42010 digital potentiometer driver
 *
 * @date Mar 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "poten.h"
#include "eficonsole.h"
#include "pin_repository.h"
#include "engine_configuration.h"
#include "hardware.h"

/**
 * MCP42010 digital potentiometer driver
 *
 *
 * 1	CS		pin select						PB12		PA10
 * 2	SCK		serial clock					PA5			PC10
 * 3	SI		serial input		(MOSI)		PA7			PC12
 * 4	Vss 	ground
 * 5	PB1
 * 6	PW1
 * 7	PA1
 * 8	PA0
 * 9	PW0
 * 10	PB0
 * 11	RS		Reset
 *
 * 14	Vdd 	V input
 *
 * Rwa = 10000 * (256 - d) / 256 + 52
 * d = 256 - (Rwa - 52) * 256 / 10000
 *
 */

SPIDriver * getDigiralPotDevice(spi_device_e spiDevice) {
#if STM32_SPI_USE_SPI1 || defined(__DOXYGEN__)
  if (spiDevice == SPI_DEVICE_1) {
		return &SPID1;
  }
#endif
#if STM32_SPI_USE_SPI2 || defined(__DOXYGEN__)
  if (spiDevic e== SPI_DEVICE_2) {
	return &SPID2;
  }
#endif
#if STM32_SPI_USE_SPI3 || defined(__DOXYGEN__)
  if (spiDevice == SPI_DEVICE_3) {
		return &SPID3;
  }
#endif
	firmwareError("Unexpected SPI device: %d", spiDevice);
	return NULL;
}

/* Low speed SPI configuration (281.250kHz, CPHA=0, CPOL=0, MSb first).*/
#define SPI_POT_CONFIG SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_DFF

static Logging logger;

#if EFI_POTENTIOMETER
Mcp42010Driver config[DIGIPOT_COUNT];

void initPotentiometer(Mcp42010Driver *driver, SPIDriver *spi, ioportid_t port, ioportmask_t pin) {
	driver->spiConfig.end_cb = NULL;
	driver->spiConfig.ssport = port;
	driver->spiConfig.sspad = pin;
	driver->spiConfig.cr1 = SPI_POT_CONFIG;
	driver->spi = spi;
	mySetPadMode("pot chip select", port, pin, PAL_STM32_MODE_OUTPUT);
}

static int getPotStep(int resistanceWA) {
	return 256 - (int) ((resistanceWA - 52) * 256 / 10000);
}

static void sendToPot(Mcp42010Driver *driver, int channel, int value) {
	lockSpi(SPI_NONE);
	spiStart(driver->spi, &driver->spiConfig);
	spiSelect(driver->spi);
	int word = (17 + channel) * 256 + value;
	spiSend(driver->spi, 1, &word);
	spiUnselect(driver->spi);
	spiStop(driver->spi);
	unlockSpi();
}

void setPotResistance(Mcp42010Driver *driver, int channel, int resistance) {
	int value = getPotStep(resistance);

	Logging *logging = &logger;
	resetLogging(logging);
	appendPrintf(logging, "msg");
	appendPrintf(logging, DELIMETER);
	appendPrintf(logging, "Sending to potentiometer%d", channel);
	appendPrintf(&logger, ": ");
	appendPrintf(&logger, "%d for R=%d", value, resistance);
	appendMsgPostfix(logging);

	scheduleLogging(logging);

	sendToPot(driver, channel, value);
}

static void setPotResistance0(int value) {
	setPotResistance(&config[0], 0, value);
}

static void setPotResistance1(int value) {
	setPotResistance(&config[0], 1, value);
}

static void setPotValue1(int value) {
	sendToPot(&config[0], 1, value);
}

#endif /* EFI_POTENTIOMETER */

void initPotentiometers(board_configuration_s *boardConfiguration) {
#if EFI_POTENTIOMETER
	initLogging(&logger, "potentiometer");
	if (boardConfiguration->digitalPotentiometerSpiDevice == SPI_NONE) {
		scheduleMsg(&logger, "digiPot spi disabled");
		return;
	}
	turnOnSpi(boardConfiguration->digitalPotentiometerSpiDevice);

	for (int i = 0; i < DIGIPOT_COUNT; i++) {
		brain_pin_e csPin = boardConfiguration->digitalPotentiometerChipSelect[i];
		if (csPin == GPIO_NONE) {
			continue;
                }

		initPotentiometer(&config[i], getDigiralPotDevice(boardConfiguration->digitalPotentiometerSpiDevice),
				getHwPort(csPin), getHwPin(csPin));
	}

	addConsoleActionI("pot0", setPotResistance0);
	addConsoleActionI("pot1", setPotResistance1);

	addConsoleActionI("potd1", setPotValue1);

	setPotResistance0(3000);
	setPotResistance1(7000);
#else
	print("digiPot logic disabled\r\n");
#endif
}
