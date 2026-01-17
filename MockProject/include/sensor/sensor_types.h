#ifndef SENSOR_TYPES_H
#define SENSOR_TYPES_H

typedef enum {
    SENSOR_TEMP,
    SENSOR_HUMI,
    SENSOR_LIGHT,
    SENSOR_PRESS,
    SENSOR_POWER_VOLT,
    SENSOR_POWER_CURR,
    SENSOR_ACCEL,
    SENSOR_MAX
} sensor_type_t;

typedef struct {
    int hour, min, sec;
    int day, month, year;
} timestamp_t;

typedef struct {
    timestamp_t ts;
    sensor_type_t type;
    float value;
    float aux;    /* dùng cho POWER hoặc ACCEL */
} sensor_sample_t;

#endif

