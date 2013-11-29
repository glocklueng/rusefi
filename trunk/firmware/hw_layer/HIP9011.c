/**
 * @file	HIP9011.c
 * @brief	HIP9011/TPIC8101 driver
 *
 *	pin1	VDD
 *	pin2	GND
 *
 *	pin8	Chip Select - CS
 *	pin11	Slave Data Out - MISO-
 *	pin12	Slave Data In - MOSI
 *	pin13	SPI clock - SCLK
 *
 *
 *	SPI frequency: 5MHz
 *
 * @date Nov 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#define HIP9011_CS_PORT GPIOE
#define HIP9011_CS_PIN 11

static Logging logger;

static WORKING_AREA(htThreadStack, 512);

static int callbackc = 0;

static void spiCallback(SPIDriver *spip) {
	spiUnselectI(spip);

	scheduleSimpleMsg(&logger, "spiCallback HIP=", callbackc++);

}

// SPI_CR1_BR_1 // 5MHz

static const SPIConfig spicfg = { spiCallback,
/* HW dependent part.*/
HIP9011_CS_PORT,
HIP9011_CS_PIN,
//SPI_CR1_MSTR |
//SPI_CR1_BR_1 // 5MHz
		SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 };

static unsigned char tx_buff[8];
static unsigned char rx_buff[8];

static SPIDriver *driver = &SPID2;

#define HIP_ADVANCED_MODE 0b01110001

static msg_t ivThread(int param) {

	int counter = 0;

//	tx_buff[0] = 0b11100001;

	tx_buff[0] = HIP_ADVANCED_MODE;

	tx_buff[4] = 0b11111000;

	while (1) {
		chThdSleepMilliseconds(10);

		scheduleSimpleMsg(&logger, "poking HIP=", counter++);

		spiSelect(driver);

		spiStartExchange(driver, 8, tx_buff, rx_buff);
//		spiUnselect(driver);

	}
	return 0;

}

void initHip9011(void) {
	if (1 == 1)
		return; // not needed yet

	initLogging(&logger, "HIP driver", logger.DEFAULT_BUFFER, sizeof(logger.DEFAULT_BUFFER));

	print("Starting HIP9011/TPIC8101 driver\r\n");
	spiStart(driver, &spicfg);

	chThdCreateStatic(htThreadStack, sizeof(htThreadStack), NORMALPRIO, (tfunc_t) ivThread, NULL);
}
