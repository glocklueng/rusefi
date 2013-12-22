/**
 * @file malfunction_central.c
 * @brief This data structure holds current malfunction codes
 *
 * @date Dec 20, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "malfunction_central.h"

static error_codes_set_s error_codes_set;

void initMalfunctionCentral(void) {
	error_codes_set.count = 0;
}

void addError(obd_code_e errorCode) {

}

void removeError(obd_code_e errorCode) {

}

void setError(int flag, obd_code_e errorCode) {
	if (flag)
		addError(errorCode);
	else
		removeError(errorCode);
}
