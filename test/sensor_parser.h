#ifndef SENSOR_PARSER_H
#define SENSOR_PARSER_H

#include <time.h>

typedef struct {
    char sensor[16];
    time_t timestamp;
    unsigned int raw;
} SensorRecord;

int parse_sensor_line(const char *line, SensorRecord *rec);

#endif

