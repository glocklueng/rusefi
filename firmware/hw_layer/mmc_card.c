/**
 * @file	mmc_card.c
 *
 * @date Dec 28, 2013
 * @author Kot_dnz
 * @author Andrey Belomutskiy, (c) 2012-2013
 *
 * pinouts for our SPI2 connected to MMC: PB13 - SCK, PB14 - MISO, PB15 - MOSI, PD11 - CS
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

#define PUSHPULLDELAY 100

static WORKING_AREA(tp_MMC_Monitor,UTILITY_THREAD_STACK_SIZE);		// MMC monitor thread

/**
 * fatfs MMC/SPI
 */
FATFS MMC_FS;
FIL MainLogFile;
char *LogFileName;

// print FAT error function
static void printError(char *str, FRESULT err) {
	print("FATfs Error \"%s\" %d\r\n", str, err);
}

// CLI command ls
static void ff_cmd_ls(char *path) {
	FRESULT res;
	FILINFO fno;
	DIR dir;
	int i;
	char *fn;

	if (fs_ready) {
		res = f_opendir(&dir, path);
		if (res == FR_OK) {
			i = strlen(path);
			for (;;) {
				res = f_readdir(&dir, &fno);
				if (res != FR_OK || fno.fname[0] == 0)
					break;
				if (fno.fname[0] == '.')
					continue;
				fn = fno.fname;
				if (fno.fattrib & AM_DIR) {
					path[i++] = '/';
					strcpy(&path[i], fn);
					// res = ff_cmd_ls(path);
					if (res != FR_OK)
						break;
					path[i] = 0;
				} else {
					print("%s/%s\t%d-%d-%d/tbyte(s)\r\n", path, fn, fno.fdate & 0xf0, (fno.fdate & 0xc) + 180,
							fno.fdate & 0x3, fno.fsize);
				}
			}
		}
	} else
		print("Error: No File system is mounted.\r\n");
}

/*
 * MMC card removal event.
 */
static void MMCRemoved(void) {
	f_mount(0, NULL );							// FATFS: Unregister work area prior to discard it
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
	err = f_mount(0, &MMC_FS);						// if Ok - mount FS
	if (err != FR_OK) {
		printError("mount", err);
		MMCRemoved();
		return -1;
	}
	fs_ready = TRUE;
	print("MMC/SD card inserted and mounted success.\r\n");
	return 0;
}

/**
 * @brief Create a new file with the specified name
 */
FRESULT createLogFile(char *fileName) {
	FRESULT err;

	err = f_open(&MainLogFile, fileName, FA_CREATE_NEW);		// Create new file 
	if (err == FR_OK || err == FR_EXIST) {
		f_close(&MainLogFile);					// if Ok or exist - close file
		strcpy(LogFileName, fileName);
	} else
		printError("create", err);				// else - show error
	return err;
}

/**
 * @brief Appends specified line to the current log file
 */
void appendToLog(char *line) {
	FRESULT err;
	UINT bytesWrited;

	err = f_open(&MainLogFile, LogFileName, FA_READ | FA_WRITE);
	if (err == FR_OK) {
		f_lseek(&MainLogFile, f_size(&MainLogFile));					// Move to end of the file to append data
		err = f_write(&MainLogFile, line, sizeof(line), &bytesWrited);
		f_sync(&MainLogFile);
		f_close(&MainLogFile);
	}
	if (err || bytesWrited < sizeof(line))
		printError("write error or disk full", err);	// error or disk full
}

//  our main thread for show check engine error
#if defined __GNUC__
__attribute__((noreturn))     static msg_t MMCmonThread(void)
#else
static msg_t MMCmonThread(void)
#endif
{
	chRegSetThreadName("MMC_Monitor");

	while (TRUE) {
		// is inserted first time
		if (blkIsInserted(&MMCD1) && fs_ready != TRUE)
			MMCInserted();

		// is first time removed
		if (!blkIsInserted(&MMCD1) && fs_ready == TRUE)
			MMCRemoved();

		// this thread is activated 10 times per second
		chThdSleepMilliseconds(PUSHPULLDELAY);
	}
}

void initMmcCard(void) {
	FRESULT err;

	//outputPinRegister("spi CS5", SPI_CS_SD_MODULE, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN);

	// start to initialize MMC/SD
	mmcObjectInit(&MMCD1);
	mmcStart(&MMCD1, &mmccfg);

	chThdCreateStatic(tp_MMC_Monitor, sizeof(tp_MMC_Monitor), LOWPRIO, (tfunc_t) MMCmonThread, NULL );

	addConsoleActionS("ls", &ff_cmd_ls);

	/*
	 *	ticket aims: only create file and append to strings
	 */
	MMCInserted();
	if (fs_ready) {
		err = createLogFile("rusefi.log");
		if (err != FR_OK)
			printError("create", err);
		else {
			appendToLog("hello line 1\r\n");
			appendToLog("hello line 2\r\n");
		}
	}
}
