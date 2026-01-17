#include "sensor_decoder.h"
#include <string.h>
#include <math.h>

double decode_sensor(const char *sensor, unsigned int raw) {
    if (!strcmp(sensor, "TEMP")) return raw / 10.0;
    if (!strcmp(sensor, "HUMI")) return raw / 10.0;
    if (!strcmp(sensor, "LIGHT")) return raw;
    if (!strcmp(sensor, "PRESS")) return raw;
    if (!strcmp(sensor, "POWER")) return raw / 100.0;
    if (!strcmp(sensor, "ACCEL")) {
        double x = ((raw >> 16) & 0xFF) / 10.0;
        double y = ((raw >> 8) & 0xFF) / 10.0;
        double z = (raw & 0xFF) / 10.0;
        return sqrt(x*x + y*y + z*z);
    }
    return 0;
}

