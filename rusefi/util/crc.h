/*
 *  Created on: Sep 20, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    crc.h
 */


#ifndef CRC_H_
#define CRC_H_

typedef unsigned char crc;

crc calc_crc(const crc message[], int nBytes);

#endif /* CRC_H_ */
