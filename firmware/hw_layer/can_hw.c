/**
 * @file	can_hw.c
 * @brief	CAN bus low level code
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "can_hw.h"
#include "pin_repository.h"
#include "rficonsole_logic.h"

static Logging logger;
static CANConfig canConfig;

static CANRxFrame rxFrame;

static void canRead(void) {
	canReceive(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);
}

void initCan(void) {

	unsigned int brp = STM32_PCLK1;

	/* Note: this calculations fit for PCLK1 = 36MHz */
	brp = (brp / 18) / 500000;                     // baudrate is set to 500k bit/s

	/* set BTR register so that sample point is at about 72% bit time from bit start */
	/* TSEG1 = 12, TSEG2 = 5, SJW = 4 => 1 CAN bit = 18 TQ, sample at 72%    */
	canConfig.btr &= ~(((0x03) << 24) | ((0x07) << 20) | ((0x0F) << 16) | (0x1FF));
	canConfig.btr |= ((((4 - 1) & 0x03) << 24) | (((5 - 1) & 0x07) << 20) | (((12 - 1) & 0x0F) << 16)
			| ((brp - 1) & 0x1FF));

	canConfig.btr = brp;

	canConfig.mcr = (CAN_MCR_NART | CAN_MCR_INRQ);       // init mode, disable auto. retransmission

	canObjectInit(&EFI_CAN_DEVICE);
	canStart(&EFI_CAN_DEVICE, &canConfig);

	initLogging(&logger, "CAN driver");

	mySetPadMode("CAN TX", EFI_CAN_TX_PORT, EFI_CAN_TX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_TX_AF));
	mySetPadMode("CAN RX", EFI_CAN_RX_PORT, EFI_CAN_RX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_RX_AF));

	addConsoleAction("canr", canRead);
}

