/**
 * @file	mmc_card.c
 *
 * @date Dec 28, 2013
 * @author Kot_dnz
 * @author Andrey Belomutskiy, (c) 2012-2013
 *
 * pinouts for our SPI2 connected to MMC: PB13 - SCK, PB14 - MISO, PB15 - MOSI, PD11 - CS, 3.3v
 *
 */
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "mmc_card.h"
#include "rficonsole_logic.h"

/**
 * MMC driver instance.
 */
MMCDriver MMCD1;

// Peripherial Clock 42MHz SPI2 SPI3
// Peripherial Clock 84MHz SPI1                                SPI1        SPI2/3
#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000) //  42 MHz      21 MHZ
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008) //  21 MHz      10.5 MHz
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010) //  10.5 MHz    5.25 MHz
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018) //  5.25 MHz    2.626 MHz  
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020) //  2.626 MHz   1.3125 MHz
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028) //  1.3125 MHz  656.25 KHz
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030) //  656.25 KHz  328.125 KHz
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038) //  328.125 KHz 164.06 KHz
static SPIConfig hs_spicfg = { NULL, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN,
SPI_BaudRatePrescaler_8 };
static SPIConfig ls_spicfg = { NULL, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN,
SPI_BaudRatePrescaler_256 };

/* MMC/SD over SPI driver configuration.*/
// don't forget check if STM32_SPI_USE_SPI2 defined and spi has init with correct GPIO in hardware.c
static MMCConfig mmccfg = { &SPID2, &ls_spicfg, &hs_spicfg };

static bool_t fs_ready = FALSE;

#define PUSHPULLDELAY 500

/**
 * fatfs MMC/SPI
 */
static FATFS MMC_FS;

// print FAT error function
static void printError(char *str, FRESULT f_error) {
	print("FATfs Error \"%s\" %d\r\n", str, f_error);
}

static FIL FDLogFile;

static Logging logger;
static int totalLoggedBytes = 0;

static void sdStatistics(void) {
	scheduleMsg(&logger, "fs_ready=%d totalLoggedBytes=%d", fs_ready, totalLoggedBytes);
}

/**
 * @brief Create a new file with the specified name
 *
 * This function saves the name of the file in a global variable
 * so that we can later append to that file
 */
// todo: extract method

static void ff_cmd_dir(char *path) {
	DIR dir;
	FILINFO fno;
	int i;
	char *fn;

	if (!fs_ready) {
		print("Error: No File system is mounted.\r\n");
		return;
	}

	FRESULT res = f_opendir(&dir, path);

	if (res == FR_OK) {
		i = strlen(path);
		for (;;) {
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0)
				break;
			if (fno.lfname[0] == '.')
				continue;
			fn = fno.lfname;
			if (fno.fattrib & AM_DIR) {
				path[i++] = '/';
				strcpy(&path[i], fn);
				// res = ff_cmd_ls(path);
				if (res != FR_OK)
					break;
				path[i] = 0;
			} else {
				print("%s/%s\t%i byte(s)\r\n", path, fn, fno.lfsize);
			}
		}
	}
}

static int errorReported = FALSE; // this is used to report the error only once

/**
 * @brief Appends specified line to the current log file
 */
void appendToLog(char *line) {
	UINT bytesWrited;

	if (!fs_ready) {
		if (!errorReported)
			print("appendToLog Error: No File system is mounted.\r\n");
		errorReported = TRUE;
		return;
	}
	int lineLength = strlen(line);
	totalLoggedBytes += lineLength;
	FRESULT err = f_write(&FDLogFile, line, lineLength, &bytesWrited);
	if (bytesWrited < lineLength) {
		printError("write error or disk full", err); // error or disk full
	}
	f_sync(&FDLogFile);
}

/*
 * MMC card umount.
 */
static void MMCumount(void) {
	if (!fs_ready) {
		print("Error: No File system is mounted. \"mountsd\" first.\r\n");
		return;
	}
	f_close(&FDLogFile);						// close file
	f_sync(&FDLogFile);							// sync ALL
	mmcDisconnect(&MMCD1);						// Brings the driver in a state safe for card removal.
	mmcStop(&MMCD1);							// Disables the MMC peripheral.
	f_mount(0, NULL);							// FATFS: Unregister work area prior to discard it
	memset(&FDLogFile, 0, sizeof(FIL));			// clear FDLogFile
	fs_ready = FALSE;							// status = false
	print("MMC/SD card removed.\r\n");
}

/*
 * MMC card mount.
 */
static void MMCmount(void) {

	if (fs_ready) {
		print("Error: Already mounted. \"umountsd\" first\r\n");
		return;
	}
	// start to initialize MMC/SD
	mmcObjectInit(&MMCD1);						// Initializes an instance.
	mmcStart(&MMCD1, &mmccfg);					// Configures and activates the MMC peripheral.

	if (mmcConnect(&MMCD1) == CH_SUCCESS) {				// Performs the initialization procedure on the inserted card.
		memset(&MMC_FS, 0, sizeof(FATFS));			// reserve the memory
		FRESULT err = f_mount(0, &MMC_FS);					// if Ok - mount FS now
		if (err == FR_OK) {
			memset(&FDLogFile, 0, sizeof(FIL));						// clear the memory
			FRESULT err = f_open(&FDLogFile, "rusefi.log", FA_OPEN_ALWAYS | FA_WRITE);				// Create new file
			if (err == FR_OK || err == FR_EXIST) {
				err = f_lseek(&FDLogFile, f_size(&FDLogFile)); // Move to end of the file to append data
				if (err) {
					printError("Seek error", err);
					return;
				}
				f_sync(&FDLogFile);
				fs_ready = TRUE;						// everything Ok
			} else {
				printError("Card mounted...\r\nCan't create Log file, check your SD.\r\nFS mount failed", err);	// else - show error
				return;
			}
			print(
					"MMC/SD card inserted and mounted success.\r\nDon't forget umountsd before remove to prevent lost your data.\r\n");
			return;
		}
	}
	print("Can't connect or mount MMC/SD\r\n");
}

void initMmcCard(void) {
	initLogging(&logger, "mmcCard");

	MMCmount();

	addConsoleAction("sdstat", sdStatistics);
	addConsoleAction("mountsd", MMCmount);
	addConsoleActionS("appendToLog", appendToLog);
	addConsoleAction("umountsd", MMCumount);
	addConsoleActionS("ls", ff_cmd_dir);
}
