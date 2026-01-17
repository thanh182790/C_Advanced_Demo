#include "sensor/sensor_buffer.h"

static sensor_buffer_t table[SENSOR_MAX];

void sensor_buffer_push(sensor_type_t t, sensor_sample_t *s)
{
    sensor_buffer_t *b = &table[t];
    b->buf[b->idx] = *s;
    b->idx = (b->idx + 1) % SENSOR_WINDOW;
    if (b->count < SENSOR_WINDOW) b->count++;
}

float sensor_buffer_avg(sensor_type_t t)
{
    sensor_buffer_t *b = &table[t];
    float sum = 0;
    for (int i = 0; i < b->count; i++)
        sum += b->buf[i].value;
    return b->count ? sum / b->count : 0;
}

