/*
 * data_buffer.c
 *
 *  Created on: Dec 8, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "data_buffer.h"
#include "rficonsole_logic.h"
#include "print.h"

int dbIsFull(data_buffer_s *db) {
	return db->size == MAX_SIZE;
}

void dbClear(data_buffer_s *db) {
	db->size = 0;
}

void dbCopy(data_buffer_s *source, data_buffer_s *target) {
	int s = source->size;
	target->size = s;
	for (int i = 0; i < s; i++)
		target->elements[i] = source->elements[i];
}

void dbAdd(data_buffer_s *db, int value) {
	if (db->size == MAX_SIZE)
		return;
	int s = db->size;
	db->elements[s] = value;
	db->size = s + 1;
}

int modp(int param) {
	return param > EF_PERIOD ? param - EF_PERIOD : param;
}

void dbPrint(data_buffer_s *db, char *message, int withDiff) {
	int s = db->size;
	print("buffer [%s] size=%d\r\n", message, s);
	int range = db->elements[s - 1] - db->elements[0];
	print("range %d ms\r\n", systicks2ms(range));

	for (int i = 0; i < s; i++) {
		print("%d: %d", i, db->elements[i]);
		if (withDiff && i > 0) {
			int diff = modp(db->elements[i]) - modp(db->elements[i - 1]);
			print(" d=%d", diff);
			print(" t=%d", systicks2ms(diff));
		}
		print("\r\n");
	}
}

void dbPrintTable(data_buffer_s *table[], char *caption[], int columns) {
	for (int c = 0; c < columns; c++)
		print("%7s", caption[c]);
	print("\r\n");

	for (int r = 0; r < MAX_SIZE; r++) {
		for (int c = 0; c < columns; c++) {
			data_buffer_s *buf = table[c];
			print("%7d", buf->elements[r]);
		}
		print("\r\n");
	}
}

