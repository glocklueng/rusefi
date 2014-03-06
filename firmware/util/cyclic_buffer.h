/**
 * @file	cyclic_buffer.h
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CYCLIC_BUFFER_H_
#define CYCLIC_BUFFER_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


#define CB_MAX_SIZE 16

typedef struct {
	volatile int elements[CB_MAX_SIZE];
	volatile int currentIndex;
	volatile int count;
} cyclic_buffer;

void cbInit(cyclic_buffer *cb);
void cbAdd(cyclic_buffer *cb, int value);
int cbSum(cyclic_buffer *cb, int length);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* CYCLIC_BUFFER_H_ */
