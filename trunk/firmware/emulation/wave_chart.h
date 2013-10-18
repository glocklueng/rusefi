/*
 * wave_chart.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef WAVE_CHART_H_
#define WAVE_CHART_H_

#include "datalogging.h"

typedef struct {
//	char *name;
	Logging logging;
	int counter;
	int isPrinted;
} WaveChart;

void addWaveChartEvent(WaveChart *chart, char *name, char * msg);
void initWaveChart(WaveChart *chart, char *name);
void resetWaveChart(WaveChart *chart);
int isWaveChartFull(WaveChart *chart);

#endif /* WAVE_CHART_H_ */
