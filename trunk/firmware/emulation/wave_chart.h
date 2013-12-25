/**
 * @file	wave_chart.h
 * @brief	Dev console wave sniffer
 *
 * @date Jun 23, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef WAVE_CHART_H_
#define WAVE_CHART_H_

#include "datalogging.h"

/**
 * @brief	Dev console sniffer data buffer
 */
typedef struct {
	Logging logging;
	int counter;
	volatile int isInitialized;
} WaveChart;

void addWaveChartEvent3(WaveChart *chart, char *name, char * msg);
void publishChart(WaveChart *chart);
void initWaveChart(WaveChart *chart);
void resetWaveChart(WaveChart *chart);
void setChartSize(int newSize);
int isWaveChartFull(WaveChart *chart);

#endif /* WAVE_CHART_H_ */
