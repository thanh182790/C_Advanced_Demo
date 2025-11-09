#ifndef SENSORS_H
#define SENSORS_H
#include "types.h"

typedef union
{
    struct
    {
        float temperature;
        float humidity;
    } env;
    uint8_t raw[8];
} SensorData_t;

void sensorUpdate(SensorData_t *data);

#endif
