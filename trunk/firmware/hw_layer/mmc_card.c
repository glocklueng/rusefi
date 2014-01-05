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
		SPI_BaudRatePrescaler_128 };
static SPIConfig ls_spicfg = { NULL, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN,
		SPI_BaudRatePrescaler_256 };

/* MMC/SD over SPI driver configuration.*/
// don't forget check if STM32_SPI_USE_SPI2 defined and spi has init with correct GPIO in hardware.c
static MMCConfig mmccfg = { &SPID2, &ls_spicfg, &hs_spicfg };

static bool_t fs_ready = FALSE;

#define PUSHPULLDELAY 500

static WORKING_AREA(tp_MMC_Monitor,UTILITY_THREAD_STACK_SIZE); // MMC monitor thread

/**
 * fatfs MMC/SPI
 */
static FATFS MMC_FS;
char LogFileName[_MAX_LFN];

// print FAT error function
static void printError(char *str, FRESULT err) {
	print("FATfs Error \"%s\" %d\r\n", str, err);
}

static FRESULT createFile(char *fileName, FIL *f) {
	if (!fs_ready) {
		print("Error: No File system is mounted.\r\n");
		return FR_NO_FILESYSTEM;
	}

	memset(f, 0, sizeof(FIL));						// clear the memory
	FRESULT err = f_open(f, fileName, FA_CREATE_NEW | FA_WRITE);// Create new file
	if (err == FR_OK || err == FR_EXIST) {
		f_sync(f);
		f_close(f);					// if Ok or exist - close file
		return FR_OK;
	} else
		printError("Can't create Log file", err);			// else - show error
	return err;

}

static FIL FDLogFile;

/**
 * @brief Create a new file with the specified name
 *
 * This function saves the name of the file in a global variable
 * so that we can later append to that file
 */
FRESULT createLogFile(char *fileName) {
	strcpy(LogFileName, fileName);
	return createFile(fileName, &FDLogFile);
}

/**
 * @brief Appends specified line to the current log file
 */
void appendToLog(char *line) {
	FRESULT err;
	UINT bytesWrited;

	if (!fs_ready)
		return; // it is normal to have no flash card so no special message

		err = f_open(&FDLogFile, LogFileName, FA_WRITE);
		if (err == FR_OK || err == FR_EXIST) {
			err = f_lseek(&FDLogFile, f_size(&FDLogFile));// Move to end of the file to append data
			if (err) {
				printError("Seek error", err);
				return;
			}
			err = f_write(&FDLogFile, line, strlen(line), &bytesWrited);
			if (bytesWrited < strlen(line)) {
				printError("write error or disk full", err);// error or disk full
			}
			f_sync(&FDLogFile);
			f_close(&FDLogFile);
		} else {
			print("Can't open Log file %s\r\n", LogFileName);
		}
}

/*
 * MMC card removal event.
 */
static void MMCRemoved(void) {
	f_mount(0, NULL );		// FATFS: Unregister work area prior to discard it
	memset(&FDLogFile, 0, sizeof(FIL));			// clear FDLogFile
	fs_ready = FALSE;							// status = false
	print("MMC/SD card removed.\r\n");
}

/*
 * MMC card insertion event.
 */
static int MMCInserted(void) {
	FRESULT err;

	memset(&MMC_FS, 0, sizeof(FATFS));				// reserve the memory
	err = f_mount(0, &MMC_FS);						// if Ok - mount FS now
	if (err == FR_OK) {
		fs_ready = TRUE;
		print("MMC/SD card inserted and mounted success.\r\n");

		return err;
	}
	printError("can't mount FS", err);
	return FR_NO_FILESYSTEM;
}

//  this thread is a in/out MMC/SD monitor
#if defined __GNUC__
__attribute__((noreturn))        static msg_t MMCmonThread(void)
#else
static msg_t MMCmonThread(void)
#endif
{
	chRegSetThreadName("MMC_Monitor");

	while (TRUE) {
		// try to connect to MMC
		if (mmcConnect(&MMCD1) == CH_SUCCESS) {
			if (!fs_ready) {
				// is first success connect
				// mount FS
				if (MMCInserted() != FR_OK)
					print("MMC Insertion failed\r\n");
			}
		} else {
			if (fs_ready) {					// if removed detected first time
				mmcDisconnect(&MMCD1);						// MMC: disconnect
				MMCRemoved();							// umount FS, clear data
			}
		}
		// this thread is activated 2 times per second
		chThdSleepMilliseconds(PUSHPULLDELAY);
	}
}

void testFs(void) {
	if (!fs_ready)
		return;
	FRESULT err;
	err = createLogFile("rusefi.log");		// create Log file
	if (err != FR_OK)
		printError("create", err);

	// todo: we need to figure out the times for f_open, f_sync and f_close
	// out target should be at least 16 lines per second - so, we
	// need to deside if we will be f_open/f_close each time or only f_open once
	// anf then f_sync for each line or every tenth line

	appendToLog("hello line 1\r\n");
	appendToLog("hello line 2\r\n");
}

void initMmcCard(void) {
	// start to initialize MMC/SD
	mmcObjectInit(&MMCD1);
	mmcStart(&MMCD1, &mmccfg);

	chThdCreateStatic(tp_MMC_Monitor, sizeof(tp_MMC_Monitor), LOWPRIO,
			(tfunc_t) MMCmonThread, NULL );

	addConsoleAction("testfs", testFs);
}
