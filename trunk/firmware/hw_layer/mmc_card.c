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
static SPIConfig hs_spicfg = { NULL, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN, SPI_BaudRatePrescaler_128 };
static SPIConfig ls_spicfg = { NULL, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN, SPI_BaudRatePrescaler_256 };

/* MMC/SD over SPI driver configuration.*/
// don't forget check if STM32_SPI_USE_SPI2 defined and spi has init with correct GPIO in hardware.c
static MMCConfig mmccfg = { &SPID2, &ls_spicfg, &hs_spicfg };

static bool_t fs_ready = FALSE;

#define PUSHPULLDELAY 500

static WORKING_AREA(tp_MMC_Monitor,UTILITY_THREAD_STACK_SIZE);		// MMC monitor thread

/**
 * fatfs MMC/SPI
 */
static FATFS MMC_FS;
static FIL FDLogFile;
char LogFileName[_MAX_LFN];

// print FAT error function
static void printError(char *str, FRESULT err) {
	print("FATfs Error \"%s\" %d\r\n", str, err);
}

/**
 * @brief Create a new file with the specified name
 */
FRESULT createLogFile(char *fileName) {
	FRESULT err;

	if (fs_ready) {
		err = f_open(&FDLogFile, fileName, FA_CREATE_NEW | FA_WRITE);	// Create new file 
		if (err == FR_OK || err == FR_EXIST) {
			f_sync(&FDLogFile);
			f_close(&FDLogFile);										// if Ok or exist - close file
			strcpy(LogFileName, fileName);
			return FR_OK;
		} else
			printError("Can't create Log file", err);					// else - show error
		return err;
	} else {
		print("Error: No File system is mounted.\r\n");
		return FR_NO_FILESYSTEM;
	}
}

/**
 * @brief Appends specified line to the current log file
 */
void appendToLog(char *line) {
	FRESULT err;
	UINT bytesWrited;
	
	if (fs_ready) {
		err = f_open(&FDLogFile, LogFileName, FA_WRITE);
		if (err == FR_OK || err == FR_EXIST) {
			err = f_lseek(&FDLogFile, f_size(&FDLogFile));			// Move to end of the file to append data
			if( err ){
				printError("Seek error", err);
				return;
			}
			err = f_write(&FDLogFile, line, strlen(line), &bytesWrited);
			if (bytesWrited < strlen(line)) {
				printError("write error or disk full", err);		// error or disk full
			}
			f_sync(&FDLogFile);
			f_close(&FDLogFile);
		} else {
			print("Can't open Log file %s\r\n", LogFileName);
		}
	} else
		print("Error: No File system is mounted.\r\n");				// FR_NO_FILESYSTEM
}

/*
 * MMC card removal event.
 */
static void MMCRemoved(void) {
	f_mount(0, NULL);							// FATFS: Unregister work area prior to discard it
	mmcDisconnect(&MMCD1);						// MMC: disconnect
	fs_ready = FALSE;							// status = false
	print("MMC/SD card removed.\r\n");
}

/*
 * MMC card insertion event.
 */
static int MMCInserted(void) {
	FRESULT err;

	/*
	 * On insertion MMC initialization and FS mount.
	 */
	if (mmcConnect(&MMCD1)) {						// try to connect to MMC
		return -1;
	}
	err = f_mount(0, &MMC_FS);						// if Ok - mount FS now
	if (err != FR_OK) {
		printError("can't mount FS", err);
		return -1;
	}
	fs_ready = TRUE;
	print("MMC/SD card inserted and mounted success.\r\n");
	
	/*
	 *	ticket aims: only create file and append two strings
	 */
		err = createLogFile("rusefi.log");
		if (err != FR_OK)
			printError("create", err);
		else {
			appendToLog("hello line 1\r\n");
			appendToLog("hello line 2\r\n");
		}

	/* end of TICKET aims */
	
	return 0;
}

//  this thread is a in/out MMC/SD monitor
#if defined __GNUC__
__attribute__((noreturn))     static msg_t MMCmonThread(void)
#else
static msg_t MMCmonThread(void)
#endif
{
	chRegSetThreadName("MMC_Monitor");
	
	while (TRUE) {
		// if inserted
		if (blkIsInserted(&MMCD1) && fs_ready == FALSE)
			MMCInserted();
	
		// TODO: if removed not working!!!
		// TODO: require correct new coding
		if (!blkIsInserted(&MMCD1) && fs_ready == TRUE)
			MMCRemoved();
		
		// this thread is activated 2 times per second
		chThdSleepMilliseconds(PUSHPULLDELAY);
	}
}

void initMmcCard(void) {
	// start to initialize MMC/SD
	mmcObjectInit(&MMCD1);
	mmcStart(&MMCD1, &mmccfg);

	chThdCreateStatic(tp_MMC_Monitor, sizeof(tp_MMC_Monitor), LOWPRIO, (tfunc_t) MMCmonThread, NULL );
}
