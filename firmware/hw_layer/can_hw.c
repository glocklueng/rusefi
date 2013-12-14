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
/*
 * Internal loopback mode, 500KBaud, automatic wakeup, automatic recover
 * from abort mode.
 * See section 22.7.7 on the STM32 reference manual.
 */
static const CANConfig canConfig = {
CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
CAN_BTR_SJW(0) | CAN_BTR_TS2(1) |
CAN_BTR_TS1(8) | CAN_BTR_BRP(6) };

static CANRxFrame rxBuffer;
static CANTxFrame txmsg;

#define CAN_BMW_E46_CLUSTER_STATUS 0x613

static void printPacket(CANRxFrame *rx) {
	scheduleSimpleMsg(&logger, "GOT FMI ", rx->FMI);
	scheduleSimpleMsg(&logger, "GOT TIME ", rx->TIME);
	scheduleSimpleMsg(&logger, "GOT DLC ", rx->DLC);
	scheduleSimpleMsg(&logger, "GOT SID ", rx->SID);

	if ( rx->SID == CAN_BMW_E46_CLUSTER_STATUS) {
		int odometerKm = 10 * (rx->data8[1] << 8) + rx->data8[0];
		int odometerMi = odometerKm * 0.621371;
		scheduleSimpleMsg(&logger, "GOT odometerKm ", odometerKm);
		scheduleSimpleMsg(&logger, "GOT odometerMi ", odometerKm);
		int timeValue = (rx->data8[4] << 8) + rx->data8[3];
		scheduleSimpleMsg(&logger, "GOT time ", timeValue);
	}

	chThdSleepMilliseconds(5);
	print("d0 %d\r\n", rx->data8[0]);
	print("d1 %d\r\n", rx->data8[1]);
	print("d2 %d\r\n", rx->data8[2]);
	print("d3 %d\r\n", rx->data8[3]);
	print("d4 %d\r\n", rx->data8[4]);
	print("d5 %d\r\n", rx->data8[5]);
	print("d6 %d\r\n", rx->data8[6]);
	print("d7 %d\r\n", rx->data8[7]);

	chThdSleepMilliseconds(5);

}

void sendRpm(void) {
	txmsg.IDE = CAN_IDE_STD;
	txmsg.EID = 0x316;
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = 8;
	txmsg.data16[1] = 1500 * 6.4;
//	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, MS2ST(100));
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE);

}

static void canRead(void) {
	scheduleSimpleMsg(&logger, "waiting for CAN ", 0);
	canReceive(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &rxBuffer, TIME_INFINITE);

	printPacket(&rxBuffer);

//	while(1) {
	sendRpm();
//		chThdSleepMilliseconds(1);
//	}

//txmsg.IDE = CAN_IDE_EXT;
}

void initCan(void) {
	initLogging(&logger, "CAN driver");

	canObjectInit(&EFI_CAN_DEVICE);
	canStart(&EFI_CAN_DEVICE, &canConfig);

	mySetPadMode("CAN TX", EFI_CAN_TX_PORT, EFI_CAN_TX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_TX_AF));
	mySetPadMode("CAN RX", EFI_CAN_RX_PORT, EFI_CAN_RX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_RX_AF));

	addConsoleAction("canr", canRead);
}

