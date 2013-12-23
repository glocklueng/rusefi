/*
 * @file malfunction_indicator.c
 * @brief We can blink out OBD-II error codes using Malfunction Indicator Light (MIL)
 *
 *
 * @date Dec 20, 2013
 * @author Konstantin Nikonenko
 * @author Andrey Belomutskiy, (c) 2012-2013
 * we show 4 digit error code - 1,5sec * (4xxx+1) digit + 0,4sec * (x3xxx+1) + ....
 * ATTENTION!!! 0 = 1 blink, 1 = 2 blinks, ...., 9 = 10 blinks
 * sequence is the constant!!!
 */

#include "main.h"
#include "output_pins.h"
#include "malfunction_indicator.h"

#define MFI_LONG_BLINK	1500
#define MFI_SHORT_BLINK	400
#define MFI_BLINK_SEPARATOR 400
#define MFI_CHECKENGINE_LIGHT 10000

int iMFIerror = 32;			// in future this error code will be check from main status engine structure
// todo: we need to add a new output PIN (new value for PinEnum and new PIN configuration and initialization)
int MFIled = LED_RUNNING;	// specify what pin must be lighting

static WORKING_AREA(mfiThreadStack, UTILITY_THREAD_STACK_SIZE);	// declare thread

static void blink_digits(int digit, int duration) {
	for (int iter = 0; iter < digit; iter++) {
		turnOutputPinOn(MFIled);
		chThdSleepMilliseconds(duration);
		turnOutputPinOff(MFIled);
		chThdSleepMilliseconds(MFI_BLINK_SEPARATOR);
	}
}

//  our main thread for show check engine error
static msg_t mfiThread(void) {
	// todo: while it is the an C tradition to declare fields in the beginning of a method
	// todo: I think we better move declarations closer to the usages to reduce visibility
	// todo: and simply future refactoring
	int MFerr, digit, ErrLength;
	chRegSetThreadName("MFIndicator");

	while (TRUE) {
		// todo: extract this as 'blinkOneCode' method
		if (iMFIerror > 0) {
			// First at all calculate how many digits in this integer
			ErrLength = iMFIerror;
			int i=0;
			while (ErrLength>0) {
				ErrLength = ErrLength / 10;
				++i;
			}
			ErrLength = i;
			print("size of ErrKegth = %d == %d\n\r", iMFIerror, i);
			// switch on check engine light on 10sec (one long blink)
			blink_digits(1, MFI_CHECKENGINE_LIGHT);
			// MFerr - local copy of iMFIerror (part of general structure)
			MFerr = iMFIerror;
			for (int iter = ErrLength-1; iter >= 0; iter--) {
				int ourDigit = pow(10, iter);		// 10^0 = 1, 10^1 = 10, 10^2=100, 10^3 = 1000
				// todo: '0' as one blink and '1' as two blinks is crazy! we should make '0' ten blinks
				digit = 1;				// as we remember "0" we show as one blink 
				while (MFerr >= ourDigit) {
					MFerr = MFerr - ourDigit;
					digit++;
				}
				if (iter % 2 == 0)
					blink_digits(digit, MFI_SHORT_BLINK);		// even 2,0 - long blink
				else
					blink_digits(digit, MFI_LONG_BLINK); 		// odd  3,1 - short blink
			}
		}
	}
	return 0;
}

void initMalfunctionIndicator(void) {
	// create static thread
	chThdCreateStatic(mfiThreadStack, sizeof(mfiThreadStack), LOWPRIO, (tfunc_t) mfiThread, NULL );
}

