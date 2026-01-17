#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor/sensor_parser.h"

static sensor_type_t parse_type(const char *line)
{
    if (strstr(line, ":TEMP")) return SENSOR_TEMP;
    if (strstr(line, ":HUMI")) return SENSOR_HUMI;
    if (strstr(line, ":LIGHT")) return SENSOR_LIGHT;
    if (strstr(line, ":PRESS")) return SENSOR_PRESS;
    if (strstr(line, ":POWER")) return SENSOR_POWER_VOLT;
    if (strstr(line, ":ACCEL")) return SENSOR_ACCEL;
    return SENSOR_MAX;
}

int sensor_parse_line(const char *line, sensor_sample_t *out)
{
    char bin[32];

    sscanf(line, "%2d:%2d:%2d-%2d/%2d/%2d",
           &out->ts.hour, &out->ts.min, &out->ts.sec,
           &out->ts.day, &out->ts.month, &out->ts.year);

    out->type = parse_type(line);

    char *p = strstr(line, "Value:");
    if (!p) return -1;

    sscanf(p, "Value: %s", bin);

    int raw = strtol(bin, NULL, 2);

    switch (out->type) {
    case SENSOR_TEMP:
    case SENSOR_HUMI:
        out->value = raw / 10.0f;
        break;
    case SENSOR_LIGHT:
        out->value = raw;
        break;
    case SENSOR_PRESS:
        out->value = raw + 900;
        break;
    case SENSOR_POWER_VOLT:
        out->value = ((raw >> 8) & 0xFF) / 10.0f;
        out->aux   = (raw & 0xFF) / 10.0f;
        break;
    case SENSOR_ACCEL: {
        int8_t x = raw >> 16;
        int8_t y = raw >> 8;
        int8_t z = raw;
        out->value = (x*x + y*y + z*z) / 100.0f;
        break;
    }
    default:
        return -1;
    }
    return 0;
}

