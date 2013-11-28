/*
 * @date Sep 20, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    crc.c
 */

#include "crc.h"

#define WIDTH  (8)
#define TOPBIT (1 << (WIDTH - 1))
#define POLYNOMIAL 0xD8

crc calc_crc(const crc message[], int nBytes) {
	crc remainder = 0;

	/*
	 * Perform modulo-2 division, a byte at a time.
	 */
	for (int byte = 0; byte < nBytes; ++byte) {
		/*
		 * Bring the next byte into the remainder.
		 */
		remainder ^= (message[byte] << (WIDTH - 8));

		/*
		 * Perform modulo-2 division, a bit at a time.
		 */
		for (unsigned char bit = 8; bit > 0; --bit) {
			/*
			 * Try to divide the current data bit.
			 */
			if (remainder & TOPBIT) {
				remainder = (remainder << 1) ^ POLYNOMIAL;
			} else {
				remainder = (remainder << 1);
			}
		}
	}

	/*
	 * The final remainder is the CRC result.
	 */
	return remainder;
}
