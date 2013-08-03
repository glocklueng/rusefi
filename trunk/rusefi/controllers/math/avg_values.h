/*
 * avg_values.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef AVG_VALUES_H_
#define AVG_VALUES_H_

#define AVG_TAB_SIZE 48

#define MAX_RPM 8000
#define MAX_KEY 5

typedef struct {
	float values[AVG_TAB_SIZE][AVG_TAB_SIZE];
	int counts[AVG_TAB_SIZE][AVG_TAB_SIZE];
} AvgTable;


void avgReset(AvgTable *table);
void avgFill(AvgTable *table, int count, float value);

void avgAddValue(AvgTable *table, int rpm, float key, float value);
float avgGetValueByIndexes(AvgTable *table, int i, int j);
float avgGetValue(AvgTable *table, int rpm, float key);
int avgGetValuesCount(AvgTable *table, int rpm, float key);

#endif /* AVG_VALUES_H_ */
