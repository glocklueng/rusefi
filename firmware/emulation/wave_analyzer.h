/**
 * @file	wave_analyzer.h
 *
 *
 * @date Jan 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef WAVE_ANALYZER_H_
#define WAVE_ANALYZER_H_

#include "main.h"
#include "datalogging.h"

#include "wave_analyzer_hw.h"
#include "wave_chart.h"

typedef struct {
	WaveReaderHw hw;
	char *name;
	volatile int eventCounter;

	volatile int lastActivityTime; // timestamp in systimer ticks
	volatile int periodEventTime; // time of signal faoo (systimer ticks)
	volatile int widthEventTime; // time of signal rise (systimer ticks)

	volatile int signalPeriod; // period between two signal rises (systimer ticks)

	volatile int waveOffsetSystimer; // offset from CKP signal in systimer ticks
	volatile int last_wave_low_width; // time period in systimer ticks
	volatile int last_wave_high_width; // time period in systimer ticks
} WaveReader;

//#define WAVE_TIMER ICUD3
//#define WAVE_INPUT_PORT GPIOC
//#define WAVE_INPUT_PIN 6

void initWaveAnalyzer(void);
void pokeWaveInfo(void);
void reportWaveInfo(void);
int getWaveLowWidth(int index);
int getWaveHighWidth(int index);
int getWaveOffset(int index);

int getWaveMode(int index);

int getEventCounter(int index);

int getSignalPeriod(int index);
int getWidthEventTime(int index);
int getPeriodEventTime(int index);

//int getCrankStart();
//int getCrankPeriod();

void printWave(Logging *logging);

#endif /* WAVE_ANALYZER_H_ */
