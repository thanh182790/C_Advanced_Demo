#include "sensor_parser.h"
#include <stdio.h>
#include <string.h>

int parse_sensor_line(const char *line, SensorRecord *rec) {
    char timebuf[16], datebuf[16], sensor[16], bin[64];

    if (sscanf(line, "%[^-]-%[^:]:%s Value: %s",
               timebuf, datebuf, sensor, bin) != 4)
        return -1;

    strcpy(rec->sensor, sensor);

    rec->raw = 0;
    for (int i = 0; bin[i]; i++) {
        rec->raw = (rec->raw << 1) | (bin[i] == '1');
    }
    return 0;
}

