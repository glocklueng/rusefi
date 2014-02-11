/**
 * @file    hardware.c
 * @brief   Hardware package entry point
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "hardware.h"
#include "pin_repository.h"
#include "io_pins.h"
#include "rtc_helper.h"

#include "adc_inputs.h"

#include "shaft_position_input.h"

#include "mcp3208.h"
#include "HIP9011.h"
#include "can_hw.h"
#include "histogram.h"
#include "mmc_card.h"
#include "neo6m.h"
#include "lcd_2x16.h"

McpAdcState adcState;

static void initSpiModule(SPIDriver *driver, ioportid_t sckPort, ioportmask_t sckPin, ioportid_t misoPort, ioportmask_t misoPin, ioportid_t mosiPort, ioportmask_t mosiPin, int af) {
	mySetPadMode("SPI clock", sckPort, sckPin, PAL_MODE_ALTERNATE(af));

	mySetPadMode("SPI master out", mosiPort, mosiPin, PAL_MODE_ALTERNATE(af));
	mySetPadMode("SPI master in ", misoPort, misoPin, PAL_MODE_ALTERNATE(af));
}

void initSpiModules(void) {
#if STM32_SPI_USE_SPI2
//	scheduleMsg(&logging, "Turning on SPI2 pins");
	initSpiModule(&SPID2,
			EFI_SPI2_SCK_PORT, EFI_SPI2_SCK_PIN,
			EFI_SPI2_MISO_PORT, EFI_SPI2_MISO_PIN,
			EFI_SPI2_MOSI_PORT, EFI_SPI2_MOSI_PIN,
			EFI_SPI2_AF);
#endif
#if STM32_SPI_USE_SPI3
//	scheduleMsg(&logging, "Turning on SPI3 pins");
	initSpiModule(&SPID3,
			EFI_SPI3_SCK_PORT, EFI_SPI3_SCK_PIN,
			EFI_SPI3_MISO_PORT, EFI_SPI3_MISO_PIN,
			EFI_SPI3_MOSI_PORT, EFI_SPI3_MOSI_PIN,
			EFI_SPI3_AF);
#endif
}


void initHardware() {
	// todo: enable protection. it's disabled because it takes
	// 10 extra seconds to re-flash the chip
	//flashProtect();

	initHistograms();

	initRtc();

	initPinRepository();

	initOutputPins();
	initAdcInputs();

#if EFI_HIP_9011
	initHip9011();
#endif /* EFI_HIP_9011 */

#if EFI_CAN_SUPPORT
	initCan();
#endif /* EFI_CAN_SUPPORT */


//	init_adc_mcp3208(&adcState, &SPID2);
//	requestAdcValue(&adcState, 0);

	initShaftPositionInputCapture();

#if EFI_FILE_LOGGING
	initSpiModules();
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
	lcd_HD44780_init();
#endif
}
