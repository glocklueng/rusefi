#include <string.h>
#include <math.h>
#include "nmea.h"
#include "rficonsole_logic.h"

double gps_deg_dec(double deg_point) {
	double ddeg;
	double sec = modf(deg_point, &ddeg) * 60;
	int deg = (int) (ddeg / 100);
	int min = (int) (deg_point - (deg * 100));

	double absdlat = round(deg * 1000000.);
	double absmlat = round(min * 1000000.);
	double absslat = round(sec * 1000000.);

	return round(absdlat + (absmlat / 60) + (absslat / 3600)) / 1000000;
}

// Convert lat e lon to decimals (from deg)
void gps_convert_deg_to_dec(double *latitude, char ns, double *longitude, char we) {
	double lat = (ns == 'N') ? *latitude : -1 * (*latitude);
	double lon = (we == 'E') ? *longitude : -1 * (*longitude);

	*latitude = gps_deg_dec(lat);
	*longitude = gps_deg_dec(lon);
}

// in string collect all char till comma and convert to double
int str_till_comma(char *a, char *dStr) {

	int i = 0, sLen = strlen(a);
	if (sLen > GPS_MAX_STRING)
		sLen = GPS_MAX_STRING;

	while (a[i] != 44 && i < sLen) {	// while not comma or end
		dStr[i] = a[i];
		i++;
	}
	dStr[i] = '\0';
	return i;
}

void nmea_parse_gpgga(char *nmea, gpgga_t *loc) {
	char *p = nmea;
	char dStr[GPS_MAX_STRING];

	p = strchr(p, ',') + 1; //skip time

	p = strchr(p, ',') + 1;								// in p string started with searching address
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->latitude = atof(dStr);

	p = strchr(p, ',') + 1;
	switch (p[0]) {
	case 'N':
		loc->lat = 'N';
		break;
	case 'S':
		loc->lat = 'S';
		break;
	case ',':
		loc->lat = '\0';
		break;
	}

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->longitude = atof(dStr);

	p = strchr(p, ',') + 1;
	switch (p[0]) {
	case 'W':
		loc->lon = 'W';
		break;
	case 'E':
		loc->lon = 'E';
		break;
	case ',':
		loc->lon = '\0';
		break;
	}

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->quality = atoi(dStr);

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->satellites = atoi(dStr);

	p = strchr(p, ',') + 1;

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->altitude = atof(dStr);
}

void nmea_parse_gprmc(char *nmea, gprmc_t *loc) {
	char *p = nmea;
	char dStr[GPS_MAX_STRING];

	p = strchr(p, ',') + 1; //skip time
	p = strchr(p, ',') + 1; //skip status

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->latitude = atof(dStr);

	p = strchr(p, ',') + 1;
	switch (p[0]) {
	case 'N':
		loc->lat = 'N';
		break;
	case 'S':
		loc->lat = 'S';
		break;
	case ',':
		loc->lat = '\0';
		break;
	}

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->longitude = atof(dStr);

	p = strchr(p, ',') + 1;
	switch (p[0]) {
	case 'W':
		loc->lon = 'W';
		break;
	case 'E':
		loc->lon = 'E';
		break;
	case ',':
		loc->lon = '\0';
		break;
	}

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->speed = atof(dStr);

	p = strchr(p, ',') + 1;
	str_till_comma(p, dStr);				// str to double till comma saved modified string
	loc->course = atof(dStr);
}

/**
 * Get the message type (GPGGA, GPRMC, etc..)
 *
 * This function filters out also wrong packages (invalid checksum)
 *
 * @param message The NMEA message
 * @return The type of message if it is valid
 */
int nmea_get_message_type(const char *message) {
	int checksum = nmea_valid_checksum(message);
	if (checksum != _EMPTY) {
		return checksum;
	}

	if (strstr(message, NMEA_GPGGA_STR) != NULL) {
		return NMEA_GPGGA;
	}

	if (strstr(message, NMEA_GPRMC_STR) != NULL) {
		return NMEA_GPRMC;
	}

	return NMEA_UNKNOWN;
}

long hex2int(char *a, int len) {
	int i;
	long val = 0;

	for (i = 0; i < len; i++)
		if (a[i] <= 57)
			val += (a[i] - 48) * (1 << (4 * (len - 1 - i))); // it's number
		else
			val += (a[i] - 87) * (1 << (4 * (len - 1 - i))); // it's a-f -> work only with low case hex
	return val;
}

int nmea_valid_checksum(const char *message) {
	char p;
	int sum = 0;
	char *starPtr = strrchr(message, '*');
	if (starPtr == NULL)
		return NMEA_CHECKSUM_ERR;
	char *int_message = starPtr + 1;
	long checksum = hex2int(int_message, 2);

	++message;
	while ((p = *message++) != '*') {
		sum ^= p;
	}

	if (sum != checksum) {
		return NMEA_CHECKSUM_ERR;
	}
	return _EMPTY;
}

void resetLocation(loc_t *coord) {
	coord->latitude = 0;
	coord->longitude = 0;
	coord->speed = 0;
	coord->altitude = 0;
	coord->course = 0;
}

// Compute the GPS location using decimal scale
void gps_location(loc_t *coord, char *buffer) {
	gpgga_t gpgga;
	gprmc_t gprmc;

	resetLocation(coord);

	switch (nmea_get_message_type(buffer)) {
	case NMEA_GPGGA:
		nmea_parse_gpgga(buffer, &gpgga);

		gps_convert_deg_to_dec(&(gpgga.latitude), gpgga.lat, &(gpgga.longitude), gpgga.lon);

		coord->latitude = gpgga.latitude;
		coord->longitude = gpgga.longitude;
		coord->altitude = gpgga.altitude;
		break;
	case NMEA_GPRMC:
		nmea_parse_gprmc(buffer, &gprmc);

		coord->speed = gprmc.speed;
		coord->course = gprmc.course;

		break;
	}
}

// 		print("GPS latitude = %f, speed = %f\r\n", GPSdata.latitude, GPSdata.speed);

