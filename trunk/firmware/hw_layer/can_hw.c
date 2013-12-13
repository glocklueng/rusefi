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

#define CAN_Mode_Normal             ((uint8_t)0x00)  /*!< normal mode */
#define CAN_Mode_LoopBack           ((uint8_t)0x01)  /*!< loopback mode */
#define CAN_Mode_Silent             ((uint8_t)0x02)  /*!< silent mode */
#define CAN_Mode_Silent_LoopBack    ((uint8_t)0x03)  /*!< loopback combined with silent mode */

#define CAN_SJW_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_SJW_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_SJW_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_SJW_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */

#define CAN_BS1_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_BS1_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_BS1_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_BS1_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */
#define CAN_BS1_5tq                 ((uint8_t)0x04)  /*!< 5 time quantum */
#define CAN_BS1_6tq                 ((uint8_t)0x05)  /*!< 6 time quantum */
#define CAN_BS1_7tq                 ((uint8_t)0x06)  /*!< 7 time quantum */
#define CAN_BS1_8tq                 ((uint8_t)0x07)  /*!< 8 time quantum */
#define CAN_BS1_9tq                 ((uint8_t)0x08)  /*!< 9 time quantum */
#define CAN_BS1_10tq                ((uint8_t)0x09)  /*!< 10 time quantum */
#define CAN_BS1_11tq                ((uint8_t)0x0A)  /*!< 11 time quantum */
#define CAN_BS1_12tq                ((uint8_t)0x0B)  /*!< 12 time quantum */
#define CAN_BS1_13tq                ((uint8_t)0x0C)  /*!< 13 time quantum */
#define CAN_BS1_14tq                ((uint8_t)0x0D)  /*!< 14 time quantum */
#define CAN_BS1_15tq                ((uint8_t)0x0E)  /*!< 15 time quantum */
#define CAN_BS1_16tq                ((uint8_t)0x0F)  /*!< 16 time quantum */

#define CAN_BS2_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_BS2_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_BS2_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_BS2_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */
#define CAN_BS2_5tq                 ((uint8_t)0x04)  /*!< 5 time quantum */
#define CAN_BS2_6tq                 ((uint8_t)0x05)  /*!< 6 time quantum */
#define CAN_BS2_7tq                 ((uint8_t)0x06)  /*!< 7 time quantum */
#define CAN_BS2_8tq                 ((uint8_t)0x07)  /*!< 8 time quantum */

static Logging logger;
static CANConfig canConfig;

static CANRxFrame rxFrame;

static void canRead(void) {
	scheduleSimpleMsg(&logger, "waiting for CAN ", 0);
	canReceive(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.FMI);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.TIME);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.DLC);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.SID);
}

void initCan(void) {
	initLogging(&logger, "CAN driver");

	int CAN_Prescaler = 4;// (STM32_PCLK1 / 15) / 500000;        // baudrate is set to 500k bit/s

	int CAN_Mode = CAN_Mode_Normal;
	int CAN_SJW = CAN_SJW_4tq;
	int CAN_BS1 = CAN_BS1_10tq;
	int CAN_BS2 = CAN_BS2_5tq;

	canConfig.btr = (uint32_t)((uint32_t)CAN_Mode << 30) | \
                ((uint32_t)CAN_SJW << 24) | \
                ((uint32_t)CAN_BS1 << 16) | \
                ((uint32_t)CAN_BS2 << 20) | \
               ((uint32_t)CAN_Prescaler - 1);

	canConfig.mcr = (CAN_MCR_NART | CAN_MCR_INRQ);       // init mode, disable auto. retransmission

	canObjectInit(&EFI_CAN_DEVICE);
	canStart(&EFI_CAN_DEVICE, &canConfig);

	mySetPadMode("CAN TX", EFI_CAN_TX_PORT, EFI_CAN_TX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_TX_AF));
	mySetPadMode("CAN RX", EFI_CAN_RX_PORT, EFI_CAN_RX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_RX_AF));

	addConsoleAction("canr", canRead);
}

