/**
 * @file	mmc_card.c
 *
 * @date Dec 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

/**
 * MMC driver instance.
 */
MMCDriver MMCD1;

/* Maximum speed SPI configuration (18MHz, CPHA=0, CPOL=0, MSb first).*/
//static SPIConfig hs_spicfg = {NULL, GPIOB, CSPIN, SPI_CR1_BR_2};

/* Low speed SPI configuration (281.250kHz, CPHA=0, CPOL=0, MSb first).*/
//static SPIConfig ls_spicfg = {NULL, GPIOB, CSPIN,
//                              SPI_CR1_BR_2 | SPI_CR1_BR_1};


void initMmcCard(void) {
	// I believe at some poing I had SD card working in MMC SPI mode - so, check MMC demo - something like
//	mmcObjectInit(&MMCD1, &SPID2, &ls_spicfg, &hs_spicfg, mmc_is_protected, mmc_is_inserted);
//	mmcStart(&MMCD1, NULL);

}
