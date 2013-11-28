/*
 * print.h
 *
 * @date Jun 15, 2013
 */

/**
 * @file    print.h
 * @brief   print() header
 */

#ifndef PRINT_H_
#define PRINT_H_

void print(const char *fmt, ...);

void consoleOutputBuffer(char *buf, int size);
int is_serial_ready(void);

#endif /* PRINT_H_ */
