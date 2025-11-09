#include "sensors.h"
#include <stdlib.h>
#include <stdio.h>

void sensorUpdate(SensorData_t *data)
{
    data->env.temperature = (rand() % 4000) / 100.0f;
    data->env.humidity = (rand() % 10000) / 100.0f;
    printf("\t[SENSOR] Temp=%.2fC Hum=%.2f%%\n", data->env.temperature, data->env.humidity);
}
