#ifndef SENSOR_BUFFER_H
#define SENSOR_BUFFER_H

#include "sensor_types.h"

#define SENSOR_WINDOW 3

typedef struct {
    sensor_sample_t buf[SENSOR_WINDOW];
    int idx;
    int count;
} sensor_buffer_t;

void sensor_buffer_push(sensor_type_t t, sensor_sample_t *s);
float sensor_buffer_avg(sensor_type_t t);

#endif

