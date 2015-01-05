/**
 * @file	HIP9011.cpp
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
 *
 * http://www.ti.com/lit/ds/symlink/tpic8101.pdf
 * http://www.intersil.com/content/dam/Intersil/documents/hip9/hip9011.pdf
 * http://www.intersil.com/content/dam/Intersil/documents/an97/an9770.pdf
 * http://e2e.ti.com/cfs-file/__key/telligent-evolution-components-attachments/00-26-01-00-00-42-36-40/TPIC8101-Training.pdf
 *
 * max SPI frequency: 5MHz max
 *
 * @date Nov 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "engine.h"
#include "settings.h"
#include "pin_repository.h"
#include "hardware.h"
#include "rpm_calculator.h"
#include "trigger_central.h"
#include "hip9011_lookup.h"

#if EFI_HIP_9011 || defined(__DOXYGEN__)

#define HIP_DEBUG FALSE

extern pin_output_mode_e DEFAULT_OUTPUT;

static int bandIndex;
static int gainIndex;
static int intergratorIndex = -1;

/**
 * Int/Hold pin is controlled from scheduler callbacks which are set according to current RPM
 *
 * The following flags make sure that we only have SPI communication while not integrating
 */
static bool_t isIntegrating = false;
static bool_t needToSendSpiCommand = false;

static scheduling_s startTimer[2];
static scheduling_s endTimer[2];

static Logging logger;

static THD_WORKING_AREA(htThreadStack, UTILITY_THREAD_STACK_SIZE);

// SPI_CR1_BR_1 // 5MHz
// SPI_CR1_CPHA Clock Phase
// todo: nicer method which would mention SPI speed explicitly?

static SPIConfig spicfg = { NULL,
/* HW dependent part.*/
NULL, 0,
SPI_CR1_MSTR |
//SPI_CR1_BR_1 // 5MHz
		SPI_CR1_CPHA | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 };

static unsigned char tx_buff[1];
static unsigned char rx_buff[1];

#define SPI_SYNCHRONOUS(value) \
	spiSelect(driver); \
	tx_buff[0] = value; \
	spiExchange(driver, 1, tx_buff, rx_buff); \
	spiUnselect(driver);

// todo: make this configurable
static SPIDriver *driver = &SPID2;

static msg_t ivThread(int param) {
	chRegSetThreadName("HIP");

	while (true) {
		chThdSleepMilliseconds(10);

//		int newValue = INTEGRATOR_INDEX;
//		if (newValue != intergratorIndex) {
//			intergratorIndex = newValue;
//			// todo: send new value, be sure to use non-synchnonious approach!
//
//		}
		// todo: move this into the end callback


//		scheduleMsg(&logger, "poking HIP=%d", counter++);

		spiSelect(driver);

//		// '0' for 4MHz
//		tx_buff[0] = SET_PRESCALER_CMD + 0 + 2;
//		spiExchange(driver, 1, tx_buff, rx_buff);
//
//		// '0' for channel #1
//		tx_buff[0] = SET_CHANNEL_CMD + 0;
//		spiExchange(driver, 1, tx_buff, rx_buff);
//
//		// band index depends on cylinder bore
//		tx_buff[0] = SET_BAND_PASS_CMD + bandIndex;
//		spiExchange(driver, 1, tx_buff, rx_buff);
//
//		// todo
//		tx_buff[0] = SET_GAIN_CMD + 41;
//		spiExchange(driver, 1, tx_buff, rx_buff);
//
//		tx_buff[0] = SET_ADVANCED_MODE;
//		spiExchange(driver, 1, tx_buff, rx_buff);

// BAND_PASS_CMD
		tx_buff[0] = 0x0 | (40 & 0x3F);
		spiExchange(driver, 1, tx_buff, rx_buff);

		// Set the gain 0b10000000
		tx_buff[0] = 0x80 | (49 & 0x3F);
		spiExchange(driver, 1, tx_buff, rx_buff);

		// Set the integration time constant 0b11000000
		tx_buff[0] = 0xC0 | (31 & 0x1F);
		spiExchange(driver, 1, tx_buff, rx_buff);

		// SET_ADVANCED_MODE 0b01110001
		tx_buff[0] = 0x71;
		spiExchange(driver, 1, tx_buff, rx_buff);

		spiUnselect(driver);

	}
#if defined __GNUC__
	return 0;
#endif

}

EXTERN_ENGINE
;

static const float gainLookupInReverseOrder[GAIN_LOOKUP_SIZE] = {
/* 00 */0.111, 0.118, 0.125, 0.129, 0.133, 0.138, 0.143, 0.148,
/* 08 */0.154, 0.160, 0.167, 0.174, 0.182, 0.190, 0.200, 0.211,
/* 16 */0.222, 0.236, 0.250, 0.258, 0.267, 0.276, 0.286, 0.296,
/* 24 */0.308, 0.320, 0.333, 0.348, 0.364, 0.381, 0.400, 0.421,
/* 32 */0.444, 0.471, 0.500, 0.548, 0.567, 0.586, 0.607, 0.630,
/* 40 */0.654, 0.680, 0.708, 0.739, 0.773, 0.810, 0.850, 0.895,
/* 48 */0.944, 1.000, 1.063, 1.143, 1.185, 1.231, 1.280, 1.333,
/* 56 */1.391, 1.455, 1.523, 1.600, 1.684, 1.778, 1.882, 2.0 };

#define GAIN_INDEX(gain) (GAIN_LOOKUP_SIZE - 1 - findIndex(gainLookupInReverseOrder, GAIN_LOOKUP_SIZE, (gain)))


static const float bandFreqLookup[BAND_LOOKUP_SIZE] = { 1.22, 1.26, 1.31, 1.35, 1.4, 1.45, 1.51, 1.57, 1.63, 1.71, 1.78,
		1.87, 1.96, 2.07, 2.18, 2.31, 2.46, 2.54, 2.62, 2.71, 2.81, 2.92, 3.03, 3.15, 3.28, 3.43, 3.59, 3.76, 3.95,
		4.16, 4.39, 4.66, 4.95, 5.12, 5.29, 5.48, 5.68, 5.9, 6.12, 6.37, 6.64, 6.94, 7.27, 7.63, 8.02, 8.46, 8.95, 9.5,
		10.12, 10.46, 10.83, 11.22, 11.65, 12.1, 12.6, 13.14, 13.72, 14.36, 15.07, 15.84, 16.71, 17.67, 18.76, 19.98 };

static float rpmLookup[INT_LOOKUP_SIZE];

/**
 *
 * We know the set of possible integration times, we know the knock detection window width
 */
static void prepareRpmLookup(engine_configuration_s *engineConfiguration) {
	for (int i = 0; i < INT_LOOKUP_SIZE; i++) {

		rpmLookup[i] = getRpmByAngleWindowAndTimeUs(integratorValues[i], engineConfiguration->knockDetectionWindowEnd
				- engineConfiguration->knockDetectionWindowStart);
	}
}

#define BAND(bore) (900 / (PIF * (bore) / 2))

#define INTEGRATOR_INDEX findIndex(rpmLookup, INT_LOOKUP_SIZE, engine->rpmCalculator.rpmValue)

static void showHipInfo(void) {
	printSpiState(&logger, boardConfiguration);
	scheduleMsg(&logger, "bore=%f freq=%f", engineConfiguration->cylinderBore, BAND(engineConfiguration->cylinderBore));

	scheduleMsg(&logger, "band_index=%d gain_index=%d", bandIndex, GAIN_INDEX(boardConfiguration->hip9011Gain));

	scheduleMsg(&logger, "integrator index=%d", INTEGRATOR_INDEX);

	scheduleMsg(&logger, "spi= int=%s CS=%s", hwPortname(boardConfiguration->hip9011IntHoldPin),
			hwPortname(boardConfiguration->hip9011CsPin));
}

void setHip9011FrankensoPinout(void) {
	/**
	 * SPI on PB13/14/15
	 */
	boardConfiguration->isHip9011Enabled = true;
	boardConfiguration->hip9011CsPin = GPIOD_11;
	boardConfiguration->hip9011IntHoldPin = GPIOB_11;
	boardConfiguration->is_enabled_spi_2 = true;
}

static void startIntegration(void) {
	if (!needToSendSpiCommand) {
		/**
		 * SPI communication is only allowed while not integrading, so we initiate the exchange
		 * once we are done integrating
		 */
		isIntegrating = false;
		turnPinHigh(HIP9011_INT_HOLD);
	}
}

static void endIntegration(void) {
	/**
	 * isIntegrating could be 'false' if an SPI command was pending thus we did not integrate during this
	 * engine cycle
	 */
	if (isIntegrating) {
		turnPinLow(HIP9011_INT_HOLD);
		isIntegrating = false;
	}
}

/**
 * Shaft Position callback used to start or finish HIP integration
 */
static void intHoldCallback(trigger_event_e ckpEventType, uint32_t index DECLARE_ENGINE_PARAMETER_S) {
	// this callback is invoked on interrupt thread

	if (index != 0)
		return;

	int rpm = engine->rpmCalculator.rpmValue;
	if (!isValidRpm(rpm))
		return;

	int structIndex = getRevolutionCounter() % 2;
	// todo: schedule this based on closest trigger event, same as ignition works
	scheduleByAngle(rpm, &startTimer[structIndex], engineConfiguration->knockDetectionWindowStart,
			(schfunc_t) &startIntegration, NULL);
	scheduleByAngle(rpm, &endTimer[structIndex], engineConfiguration->knockDetectionWindowEnd,
			(schfunc_t) &endIntegration,
			NULL);
}

static void setGain(float value) {
	boardConfiguration->hip9011Gain = value;
	showHipInfo();
}

void initHip9011(void) {
	if (!boardConfiguration->isHip9011Enabled)
		return;
	initLogging(&logger, "HIP driver");

//	driver = getSpiDevice(boardConfiguration->digitalPotentiometerSpiDevice);

	spicfg.ssport = getHwPort(boardConfiguration->hip9011CsPin);
	spicfg.sspad = getHwPin(boardConfiguration->hip9011CsPin);

	outputPinRegisterExt2("hip int/hold", HIP9011_INT_HOLD, boardConfiguration->hip9011IntHoldPin, &DEFAULT_OUTPUT);
	outputPinRegisterExt2("hip CS", SPI_CS_HIP9011, boardConfiguration->hip9011CsPin, &DEFAULT_OUTPUT);

	scheduleMsg(&logger, "Starting HIP9011/TPIC8101 driver");
	spiStart(driver, &spicfg);

	chThdCreateStatic(htThreadStack, sizeof(htThreadStack), NORMALPRIO,
			(tfunc_t) ivThread, NULL);
//#else
//	/**
//	 * for runtime we are re-starting SPI in non-synchronous mode
//	 */
//	spiStop(driver);
//	// todo spicfg.end_cb = spiEndCallback;
//	spiStart(driver, &spicfg);
//#endif /* HIP_DEBUG */

	bandIndex = findIndex(bandFreqLookup, BAND_LOOKUP_SIZE, BAND(engineConfiguration->cylinderBore));

	addTriggerEventListener(&intHoldCallback, "DD int/hold", engine);

	// MISO PB14
//	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(EFI_SPI2_AF) | PAL_STM32_PUDR_PULLUP);
	// MOSI PB15
//	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(EFI_SPI2_AF) | PAL_STM32_OTYPE_OPENDRAIN);

	addConsoleAction("hipinfo", showHipInfo);
	addConsoleActionF("set_gain", setGain);
}

#endif
