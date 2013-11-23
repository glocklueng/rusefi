/**
 * @file	tunerstudio.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TUNERSTUDIO_H_
#define TUNERSTUDIO_H_

#include "fuel_map.h"


#if EFI_TUNER_STUDIO_OVER_USB
#define TS_SERIAL_DEVICE (&SDU1)
#else
#define TS_SERIAL_DEVICE &SD3
#define TS_SERIAL_SPEED 115200

#define TS_SERIAL_PORT GPIOD
#define TS_SERIAL_TX_PIN 8
#define TS_SERIAL_RX_PIN 9
#endif /* EFI_TUNER_STUDIO_OVER_USB */



#if defined __GNUC__
typedef struct
	__attribute__((packed)) {
#else
		typedef __packed struct {
#endif

			short int offset;
			unsigned char value;
		} TunerStudioWriteRequest;

		void startTunerStudioConnectivity(void);
		void syncTunerStudioCopy(void);
		void updateTunerStudioState(void);

#endif /* TUNERSTUDIO_H_ */
