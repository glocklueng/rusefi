/**
 *
 * https://github.com/wdalmut/libgps/tree/develop/src
 *
 */
#ifndef _NMEA_H_
#define _NMEA_H_

#define GPS_MAX_STRING 256

typedef enum {
	NMEA_UNKNOWN = 0x00,
	NMEA_GPRMC = 0x01,
	NMEA_GPGGA = 0x02
} nmea_message_type;

#define _EMPTY 0x00
#define NMEA_GPRMC_STR "$GPRMC"
#define NMEA_GPGGA_STR "$GPGGA"
#define _COMPLETED 0x03

#define NMEA_CHECKSUM_ERR 0x80
#define NMEA_MESSAGE_ERR 0xC0

struct gpgga {
	// Latitude eg: 4124.8963 (XXYY.ZZKK.. DEG, MIN, SEC.SS)
	double latitude;
	// Latitude eg: N
	char lat;
	// Longitude eg: 08151.6838 (XXXYY.ZZKK.. DEG, MIN, SEC.SS)
	double longitude;
	// Longitude eg: W
	char lon;
	// Quality 0, 1, 2
	unsigned int quality;
	// Number of satellites: 1,2,3,4,5...
	unsigned int satellites;
	// Altitude eg: 280.2 (Meters above mean sea level)
	double altitude;
};
typedef struct gpgga gpgga_t;

struct gprmc {
	double latitude;
	char lat;
	double longitude;
	char lon;
	double speed;
	double course;
};
typedef struct gprmc gprmc_t;

struct GPSlocation {
	double latitude;
	double longitude;
	double speed;
	double altitude;
	double course;
	nmea_message_type type;
};
typedef struct GPSlocation loc_t;

nmea_message_type nmea_get_message_type(const char *);
int nmea_valid_checksum(const char *);
void nmea_parse_gpgga(char *, gpgga_t *);
void nmea_parse_gprmc(char *, gprmc_t *);
void gps_location(loc_t *, char *);

#endif
