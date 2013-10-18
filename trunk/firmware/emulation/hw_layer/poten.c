/*
 * poten.c
 *
 *  Created on: Mar 16, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "poten.h"
#include "rficonsole.h"
#include "pin_repository.h"
#include "datalogging.h"

/**
 * MCP42010 digital potentiometer driver
 *
 *
 * 1	CS		pin select						PB12
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

//#define POT_SPI &SPID1
//#define POTEN_CS_PORT GPIOB
//#define POTEN_CS_PIN 12
//#define POT_SPI_CK_PORT GPIOA
//#define POT_SPI_CK_PIN 5
//#define POT_SPI_MO_PORT GPIOA
//#define POT_SPI_MO_PIN 7
//#define POT_SPI_AF 5
// PA13 & PA14 are system pins
#define POT_SPI &SPID3
// chip select
#define POTEN_CS_PORT GPIOA
#define POTEN_CS_PIN 10
#define POT_SPI_CK_PORT GPIOC
#define POT_SPI_CK_PIN 10
#define POT_SPI_MO_PORT GPIOC
#define POT_SPI_MO_PIN 12
#define POT_SPI_AF 6

#ifdef EFI_POTENTIOMETER

/* Low speed SPI configuration (281.250kHz, CPHA=0, CPOL=0, MSb first).*/
static SPIConfig spicfg = { NULL, POTEN_CS_PORT, POTEN_CS_PIN, SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_DFF };
#endif

static Logging log;

static int getPotStep(int resistanceWA) {
	return 256 - (int) ((resistanceWA - 52) * 256 / 10000);
}

static void sendToPot(int channel, int value) {
#ifdef EFI_POTENTIOMETER
	spiSelect(POT_SPI);
	int word = (17 + channel) * 256 + value;
	spiSend(POT_SPI, 1, &word);
	spiUnselect(POT_SPI);
#endif
}

void setPotResistance(int channel, int resistance) {
	int value = getPotStep(resistance);

	Logging *logging = &log;
	resetLogging(logging);
	append(logging, "msg");
	append(logging, DELIMETER);
	append(logging, "Sending to potentiometer");
	appendInt(logging, channel);
	append(&log, ": ");
	appendInt(&log, value);
	append(&log, " for R=");
	appendInt(&log, resistance);
	append(logging, DELIMETER);


	scheduleLogging(logging);

	sendToPot(channel, value);
}

static void setPotResistance0(int value) {
	setPotResistance(0, value);
}

static void setPotResistance1(int value) {
	setPotResistance(1, value);
}

static void setPotValue1(value) {
	sendToPot(1, value);
}

void initPotentiometer() {
#ifdef EFI_POTENTIOMETER
	initLogging(&log, "potentiometer", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	mySetPadMode("pot chip select", POTEN_CS_PORT, POTEN_CS_PIN, PAL_STM32_MODE_OUTPUT);

	mySetPadMode("pot SPI clock", POT_SPI_CK_PORT, POT_SPI_CK_PIN, PAL_MODE_ALTERNATE(POT_SPI_AF));

	addConsoleAction1("pot0", setPotResistance0);
	addConsoleAction1("pot1", setPotResistance1);

	addConsoleAction1("potd1", setPotValue1);


//	palSetGroupMode(POT_SPI_MO_PORT, PAL_PORT_BIT(POT_SPI_MO_PIN),
//			0, PAL_STM32_MODE_OUTPUT);

	mySetPadMode("pot SPI master out", POT_SPI_MO_PORT, POT_SPI_MO_PIN, PAL_MODE_ALTERNATE(POT_SPI_AF));

	spiStart(POT_SPI, &spicfg);

	setPotResistance0(3000);
	setPotResistance1(7000);
#else
	print("potentiometer disabled\r\n");
#endif
}
