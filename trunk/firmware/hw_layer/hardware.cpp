/**
 * @file    hardware.cpp
 * @brief   Hardware package entry point
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "hardware.h"
#include "pin_repository.h"
#include "io_pins.h"
#include "rtc_helper.h"
#include "rfiutil.h"
#include "console_io.h"

#include "adc_inputs.h"
#include "stepper.h"
#include "vehicle_speed.h"

#include "trigger_input.h"
#include "eficonsole.h"
#include "max31855.h"
#include "can_hw.h"

#if EFI_PROD_CODE
#include "board_test.h"
#include "mcp3208.h"
#include "HIP9011.h"
#include "histogram.h"
#include "mmc_card.h"
#include "neo6m.h"
#include "lcd_HD44780.h"
#include "settings.h"
#include "algo.h"
#include "joystick.h"
#include "trigger_central.h"
#include "svnversion.h"
#include "engine_configuration.h"
#include "ec2.h"
#endif

#if EFI_INTERNAL_FLASH
#include "flash_main.h"
#endif /* EFI_INTERNAL_FLASH */

EXTERN_ENGINE
;
extern bool hasFirmwareErrorFlag;

static StepperMotor iacMotor;

static Mutex spiMtx;

int maxNesting = 0;

#if HAL_USE_SPI || defined(__DOXYGEN__)
static bool isSpiInitialized[5] = { false, false, false, false, false };

static void initSpiModule(SPIDriver *driver, brain_pin_e sck, brain_pin_e miso,
		brain_pin_e mosi, int af) {

	mySetPadMode2("SPI clock", sck,	PAL_MODE_ALTERNATE(af));

	mySetPadMode2("SPI master out", mosi, PAL_MODE_ALTERNATE(af));
	mySetPadMode2("SPI master in ", miso, PAL_MODE_ALTERNATE(af));
}

/**
 * Only one consumer can use SPI bus at a given time
 */
void lockSpi(spi_device_e device) {
	// todo: different locks for different SPI devices!
	chMtxLock(&spiMtx);
}

void unlockSpi(void) {
	chMtxUnlock();
}

void turnOnSpi(spi_device_e device) {
	if (isSpiInitialized[device])
		return; // already initialized
	isSpiInitialized[device] = true;
	if (device == SPI_DEVICE_1) {
#if STM32_SPI_USE_SPI1
//	scheduleMsg(&logging, "Turning on SPI1 pins");
		initSpiModule(&SPID1, boardConfiguration->spi1sckPin,
				boardConfiguration->spi1misoPin,
				boardConfiguration->spi1mosiPin,
				EFI_SPI1_AF);
#endif /* STM32_SPI_USE_SPI1 */
	}
	if (device == SPI_DEVICE_2) {
#if STM32_SPI_USE_SPI2
//	scheduleMsg(&logging, "Turning on SPI2 pins");
		initSpiModule(&SPID2, boardConfiguration->spi2sckPin,
				boardConfiguration->spi2misoPin,
				boardConfiguration->spi2mosiPin,
				EFI_SPI2_AF);
#endif /* STM32_SPI_USE_SPI2 */
	}
	if (device == SPI_DEVICE_3) {
#if STM32_SPI_USE_SPI3
//	scheduleMsg(&logging, "Turning on SPI3 pins");
		initSpiModule(&SPID3, boardConfiguration->spi3sckPin,
				boardConfiguration->spi3misoPin,
				boardConfiguration->spi3mosiPin,
				EFI_SPI3_AF);
#endif /* STM32_SPI_USE_SPI3 */
	}
}

static void initSpiModules(board_configuration_s *boardConfiguration) {
	if (boardConfiguration->is_enabled_spi_2) {
		turnOnSpi(SPI_DEVICE_2);
	}
	if (boardConfiguration->is_enabled_spi_3) {
		turnOnSpi(SPI_DEVICE_3);
	}
}

SPIDriver * getSpiDevice(spi_device_e spiDevice) {
	if (spiDevice == SPI_NONE) {
		return NULL;
	}
#if STM32_SPI_USE_SPI1 || defined(__DOXYGEN__)
	if (spiDevice == SPI_DEVICE_1) {
		return &SPID1;
	}
#endif
#if STM32_SPI_USE_SPI2 || defined(__DOXYGEN__)
	if (spiDevice == SPI_DEVICE_2) {
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

void initSpiCs(SPIConfig *spiConfig, brain_pin_e csPin) {
	spiConfig->end_cb = NULL;
	ioportid_t port = getHwPort(csPin);
	ioportmask_t pin = getHwPin(csPin);
	spiConfig->ssport = port;
	spiConfig->sspad = pin;
	mySetPadMode("chip select", port, pin, PAL_STM32_MODE_OUTPUT);
}
#endif

#if HAL_USE_I2C || defined(__DOXYGEN__)
static I2CConfig i2cfg = { OPMODE_I2C, 100000, STD_DUTY_CYCLE, };

void initI2Cmodule(void) {
	print("Starting I2C module\r\n");
	i2cInit();
	i2cStart(&I2CD1, &i2cfg);

	mySetPadMode("I2C clock", EFI_I2C_SCL_PORT, EFI_I2C_SCL_PIN,
	PAL_MODE_ALTERNATE(EFI_I2C_AF) | PAL_STM32_OTYPE_OPENDRAIN);
	mySetPadMode("I2C data", EFI_I2C_SDA_PORT, EFI_I2C_SDA_PIN,
	PAL_MODE_ALTERNATE(EFI_I2C_AF) | PAL_STM32_OTYPE_OPENDRAIN);
}

//static char txbuf[1];

static void sendI2Cbyte(int addr, int data) {
//	i2cAcquireBus(&I2CD1);
//	txbuf[0] = data;
//	i2cMasterTransmit(&I2CD1, addr, txbuf, 1, NULL, 0);
//	i2cReleaseBus(&I2CD1);
}

#endif

static Logging *sharedLogger;

#if EFI_PROD_CODE

void initHardware(Logging *l, Engine *engine) {
	sharedLogger = l;
	engine_configuration_s *engineConfiguration = engine->engineConfiguration;
	efiAssertVoid(engineConfiguration!=NULL, "engineConfiguration");
	board_configuration_s *boardConfiguration = &engineConfiguration->bc;

	printMsg(sharedLogger, "initHardware()");
	// todo: enable protection. it's disabled because it takes
	// 10 extra seconds to re-flash the chip
	//flashProtect();

	chMtxInit(&spiMtx);

#if EFI_HISTOGRAMS
	/**
	 * histograms is a data structure for CPU monitor, it does not depend on configuration
	 */
	initHistogramsModule();
#endif /* EFI_HISTOGRAMS */

	/**
	 * This is so early because we want to init logger
	 * which would be used while finding trigger synch index
	 * while config read
	 */
	initTriggerDecoder();

	/**
	 * We need the LED_ERROR pin even before we read configuration
	 */
	initPrimaryPins();

	if (hasFirmwareError()) {
		return;
	}

	initDataStructures(PASS_ENGINE_PARAMETER_F);

#if EFI_INTERNAL_FLASH

	palSetPadMode(CONFIG_RESET_SWITCH_PORT, CONFIG_RESET_SWITCH_PIN,
			PAL_MODE_INPUT_PULLUP);

	initFlash(engine);
	/**
	 * this call reads configuration from flash memory or sets default configuration
	 * if flash state does not look right.
	 */
	if (SHOULD_INGORE_FLASH()) {
		engineConfiguration->engineType = DEFAULT_ENGINE_TYPE;
		resetConfigurationExt(sharedLogger, engineConfiguration->engineType,
				engine);
		writeToFlash();
	} else {
		readFromFlash();
	}
#else
	engineConfiguration->engineType = DEFAULT_ENGINE_TYPE;
	resetConfigurationExt(logger, engineConfiguration->engineType, engine);
#endif /* EFI_INTERNAL_FLASH */

	if (hasFirmwareError()) {
		return;
	}

	mySetPadMode2("board test", boardConfiguration->boardTestModeJumperPin,
	PAL_MODE_INPUT_PULLUP);
	bool isBoardTestMode_b = GET_BOARD_TEST_MODE_VALUE();

#if HAL_USE_ADC || defined(__DOXYGEN__)
	initAdcInputs(isBoardTestMode_b);
#endif

	if (isBoardTestMode_b) {
		// this method never returns
		initBoardTest();
	}

	initRtc();

	initOutputPins();

#if EFI_MAX_31855
	initMax31855(getSpiDevice(boardConfiguration->max31855spiDevice),
			boardConfiguration->max31855_cs);
#endif /* EFI_MAX_31855 */

//	iacMotor.initialize(GPIOD_11, GPIOD_10);

#if EFI_CAN_SUPPORT
	initCan();
#endif /* EFI_CAN_SUPPORT */

//	init_adc_mcp3208(&adcState, &SPID2);
//	requestAdcValue(&adcState, 0);

	// todo: figure out better startup logic
	initTriggerCentral(engine);

#if EFI_SHAFT_POSITION_INPUT || defined(__DOXYGEN__)
	initShaftPositionInputCapture();
#endif /* EFI_SHAFT_POSITION_INPUT */

#if HAL_USE_SPI || defined(__DOXYGEN__)
	initSpiModules(boardConfiguration);
#endif

#if EFI_HIP_9011
	initHip9011();
#endif /* EFI_HIP_9011 */

#if EFI_FILE_LOGGING
	initMmcCard();
#endif /* EFI_FILE_LOGGING */

//	initFixedLeds();

	//	initBooleanInputs();

#if EFI_UART_GPS
	initGps();
#endif

#if ADC_SNIFFER
	initAdcDriver();
#endif

#if EFI_HD44780_LCD
//	initI2Cmodule();
	lcd_HD44780_init();
	if (hasFirmwareError())
		return;

	lcd_HD44780_print_string(VCS_VERSION);

#endif /* EFI_HD44780_LCD */

#if HAL_USE_I2C || defined(__DOXYGEN__)
	addConsoleActionII("i2c", sendI2Cbyte);
#endif

//	while (true) {
//		for (int addr = 0x20; addr < 0x28; addr++) {
//			sendI2Cbyte(addr, 0);
//			int err = i2cGetErrors(&I2CD1);
//			print("I2C: err=%x from %d\r\n", err, addr);
//			chThdSleepMilliseconds(5);
//			sendI2Cbyte(addr, 255);
//			chThdSleepMilliseconds(5);
//		}
//	}

	initVehicleSpeed(sharedLogger);

	initJoystick(sharedLogger);

	printMsg(sharedLogger, "initHardware() OK!");
}

#endif /* EFI_PROD_CODE */
