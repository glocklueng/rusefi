/**
 * @file	efilib2.h
 *
 * @date Apr 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef EFILIB2_H_
#define EFILIB2_H_

#include <stdint.h>


class Overflow64Counter
{
  public:
	Overflow64Counter();

	void offer(uint32_t value);
	uint64_t get();

  private:
	uint64_t currentBase;
	uint32_t currentValue;
};


#endif /* EFILIB2_H_ */
