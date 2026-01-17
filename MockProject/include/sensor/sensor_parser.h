#ifndef SENSOR_PARSER_H
#define SENSOR_PARSER_H

#include "sensor_types.h"

int sensor_parse_line(const char *line, sensor_sample_t *out);

#endif

