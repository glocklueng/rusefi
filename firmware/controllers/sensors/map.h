/**
 * @author Andrey Belomutskiy, (c) 2012-2016
 */
#ifndef MAP_H_
#define MAP_H_

#include "engine_configuration.h"
#include "sensor_types.h"

void initMapDecoder(Logging *sharedLogger DECLARE_ENGINE_PARAMETER_S);

/**
 * @return Raw MAP sensor value right now
 */
float getRawMap(DECLARE_ENGINE_PARAMETER_F);
float getBaroPressure(DECLARE_ENGINE_PARAMETER_F);
bool_t hasBaroSensor(DECLARE_ENGINE_PARAMETER_F);
/**
 * @return MAP value averaged within a window of measurement
 */
float getMap(void);
float getMapVoltage(void);
float getMapByVoltage(float voltage DECLARE_ENGINE_PARAMETER_S);
float decodePressure(float voltage, air_pressure_sensor_config_s * config);
float validateMap(float mapKPa DECLARE_ENGINE_PARAMETER_S);

#endif
