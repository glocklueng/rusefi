/*
 * main_loop.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

#define MAF_MODE 1

#define ASPIRE_MAGIC_DUTY_CYCLE 0.3877
#define CYLINDERS	4

/**
 * "For ALL 4 cycle (four-stroke) engines, no matter how many cylinders, the crankshaft
 * turns twice for every turn of the camshaft."
 *
 * Cam revolution time in milliseconds = 1000 / (RPM / 60 / 2) = 120000 / RPM
 * One stroke is 90 degrees = so, we divide revolution constant by four
 */

#define STROKE_TIME_CONSTANT (1000 * 60 * 2 / 4 * TICKS_IN_MS)

void initMainLoop(void);
void onEveryMillisecondTimerSignal(void);

myfloat getMaf(void);
myfloat getAfr(void);
myfloat getVRef(void);
myfloat getTPS(void);
myfloat getMap(void);
myfloat getCoolantTemperature(void);
myfloat getIntakeAirTemperature(void);

#endif /* MAIN_LOOP_H_ */
