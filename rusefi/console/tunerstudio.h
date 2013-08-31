/*
 * tunerstudio.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TUNERSTUDIO_H_
#define TUNERSTUDIO_H_

#define SIGNATURE "MShift v0.01"

#define TS_SERIAL_SPEED 115200
#define TS_SERIAL_DEVICE &SD3

#define TS_SERIAL_PORT GPIOD
#define TS_SERIAL_TX_PIN 8
#define TS_SERIAL_RX_PIN 9

typedef struct {
	int rpm;
} TunerStudioOutputChannels;

void startTunerStudioConnectivity(void);

#endif /* TUNERSTUDIO_H_ */
