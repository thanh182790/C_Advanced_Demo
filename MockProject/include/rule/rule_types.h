#ifndef RULE_TYPES_H
#define RULE_TYPES_H

#include "sensor/sensor_types.h"

typedef enum {
    MODE_INSTANT,
    MODE_AVG
} rule_mode_t;

typedef struct {
    char name[64];
    sensor_type_t sensor;
    rule_mode_t mode;
    int window;
    int stateful;
    int persist;
    float threshold;
    int hit;
} rule_t;

#endif

