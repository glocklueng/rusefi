/**
 * @file	cyclic_buffer.h
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CYCLIC_BUFFER_H_
#define CYCLIC_BUFFER_H_

#define CB_MAX_SIZE 16

typedef struct {
	int elements[CB_MAX_SIZE];
	int currentIndex;
	int count;
} cyclic_buffer;

void cbInit(cyclic_buffer *cb);
void cbAdd(cyclic_buffer *cb, int value);
int cbSum(cyclic_buffer *cb, int length);

#endif /* CYCLIC_BUFFER_H_ */
