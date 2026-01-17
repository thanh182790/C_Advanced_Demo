#include <stdio.h>
#include "sensor/sensor_parser.h"
#include "rule/rule_parser.h"
#include "rule/rule_engine.h"

int main(void)
{
    FILE *fp = fopen("config/sensor_data.log", "r");
    if (!fp) return -1;

    rule_engine_init();

    char line[128];
    sensor_sample_t s;

    while (fgets(line, sizeof(line), fp)) {
        if (sensor_parse_line(line, &s) == 0) {
            sensor_buffer_push(s.type, &s);
            rule_engine_eval(&s);
        }
    }

    fclose(fp);
    return 0;
}

