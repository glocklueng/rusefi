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
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "engine.h"
#include "settings.h"
#include "pin_repository.h"
#include "hardware.h"
#include "rpm_calculator.h"
#include "trigger_central.h"
#include "hip9011_lookup.h"
#include "HIP9011.h"

#if EFI_HIP_9011 || defined(__DOXYGEN__)

static OutputPin intHold;
static OutputPin hipCs;

extern pin_output_mode_e DEFAULT_OUTPUT;

/**
 * band index is only send to HIP chip on startup
 */
static int bandIndex;
static int currentGainIndex = -1;
static int currentIntergratorIndex = -1;
static int settingUpdateCount = 0;

/**
 * Int/Hold pin is controlled from scheduler callbacks which are set according to current RPM
 *
 * The following flags make sure that we only have SPI communication while not integrating
 */
static bool_t isIntegrating = false;
/**
 */
static bool_t isSendingSpiCommand = false;

static scheduling_s startTimer[2];
static scheduling_s endTimer[2];

static LoggingWithStorage logger;

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
static int nonZeroResponse = 0;

#define SPI_SYNCHRONOUS(value) \
	spiSelect(driver); \
	tx_buff[0] = value; \
	spiExchange(driver, 1, tx_buff, rx_buff); \
	spiUnselect(driver); \
	if (rx_buff[0] != 0) nonZeroResponse++;

// todo: make this configurable
static SPIDriver *driver = &SPID2;

EXTERN_ENGINE
;

static void showHipInfo(void) {
	printSpiState(&logger, boardConfiguration);
	scheduleMsg(&logger, "bore=%f freq=%f", engineConfiguration->cylinderBore, BAND(engineConfiguration->cylinderBore));

	scheduleMsg(&logger, "band_index=%d gain %f/index=%d", bandIndex, boardConfiguration->hip9011Gain, currentGainIndex);
	scheduleMsg(&logger, "integrator index=%d", currentIntergratorIndex);

	scheduleMsg(&logger, "spi= int=%s response count=%d", hwPortname(boardConfiguration->hip9011IntHoldPin), nonZeroResponse);
	scheduleMsg(&logger, "CS=%s updateCount=%d", hwPortname(boardConfiguration->hip9011CsPin), settingUpdateCount);
}

void setHip9011FrankensoPinout(void) {
	/**
	 * SPI on PB13/14/15
	 */
	boardConfiguration->isHip9011Enabled = true;
	boardConfiguration->hip9011CsPin = GPIOD_0;
	boardConfiguration->hip9011IntHoldPin = GPIOB_11;
	boardConfiguration->is_enabled_spi_2 = true;
}

static void startIntegration(void) {
	if (!isSendingSpiCommand) {
		/**
		 * SPI communication is only allowed while not integrating, so we postpone the exchange
		 * until we are done integrating
		 */
		isIntegrating = true;
		intHold.setValue(true);
	}
}

static void endIntegration(void) {
	/**
	 * isIntegrating could be 'false' if an SPI command was pending thus we did not integrate during this
	 * engine cycle
	 */
	if (isIntegrating) {
		intHold.setValue(false);
		isIntegrating = false;

		int integratorIndex = getIntegrationIndexByRpm(engine->rpmCalculator.rpmValue);
		int gainIndex = getHip9011GainIndex(boardConfiguration->hip9011Gain);

		if (currentGainIndex != gainIndex) {
			tx_buff[0] = gainIndex;
			currentGainIndex = gainIndex;

			isSendingSpiCommand = true;
			spiSelectI(driver);
			spiStartExchangeI(driver, 1, tx_buff, rx_buff);
			return;
		}

		if (currentIntergratorIndex != integratorIndex) {
			tx_buff[0] = integratorIndex;
			currentIntergratorIndex = integratorIndex;

			isSendingSpiCommand = true;
			spiSelectI(driver);
			spiStartExchangeI(driver, 1, tx_buff, rx_buff);
			return;
		}
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

static void endOfSpiCommunication(SPIDriver *spip) {
	spiUnselectI(driver);
	isSendingSpiCommand = false;
}

void initHip9011(void) {
	if (!boardConfiguration->isHip9011Enabled)
		return;
	initLogging(&logger, "HIP driver");

	// todo: apply new properties on the fly
	prepareHip9011RpmLookup(
			engineConfiguration->knockDetectionWindowEnd - engineConfiguration->knockDetectionWindowStart);

	// todo: configurable
//	driver = getSpiDevice(boardConfiguration->hip9011SpiDevice);

	spicfg.ssport = getHwPort(boardConfiguration->hip9011CsPin);
	spicfg.sspad = getHwPin(boardConfiguration->hip9011CsPin);

	outputPinRegisterExt2("hip int/hold", &intHold, boardConfiguration->hip9011IntHoldPin, &DEFAULT_OUTPUT);
	outputPinRegisterExt2("hip CS", &hipCs, boardConfiguration->hip9011CsPin, &DEFAULT_OUTPUT);

	scheduleMsg(&logger, "Starting HIP9011/TPIC8101 driver");
	spiStart(driver, &spicfg);

	bandIndex = getHip9011BandIndex(engineConfiguration->cylinderBore);

	/**
	 * this engine cycle callback would be scheduling actual integration start and end callbacks
	 */
	addTriggerEventListener(&intHoldCallback, "DD int/hold", engine);

	// MISO PB14
//	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(EFI_SPI2_AF) | PAL_STM32_PUDR_PULLUP);
	// MOSI PB15
//	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(EFI_SPI2_AF) | PAL_STM32_OTYPE_OPENDRAIN);

	addConsoleAction("hipinfo", showHipInfo);
	addConsoleActionF("set_gain", setGain);

	// '0' for 4MHz
	SPI_SYNCHRONOUS(SET_PRESCALER_CMD + 0);

	// '0' for channel #1
	SPI_SYNCHRONOUS(SET_CHANNEL_CMD + 0);

	// band index depends on cylinder bore
	SPI_SYNCHRONOUS(SET_BAND_PASS_CMD + bandIndex);

	/**
	 * Let's restart SPI to switch it from synchronous mode into
	 * asynchronous mode
	 */
	spiStop(driver);
	spicfg.end_cb = endOfSpiCommunication;
	spiStart(driver, &spicfg);
}

#endif
