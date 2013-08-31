/*
 * print.h
 *
 *  Created on: Jun 15, 2013
 */

/**
 * @file    print.h
 * @brief   print() header
 */

#ifndef PRINT_H_
#define PRINT_H_

void print(const char *fmt, ...);
void consolePutChar(int x);

void consoleOututBuffer(char *buf, int size);

#endif /* PRINT_H_ */
