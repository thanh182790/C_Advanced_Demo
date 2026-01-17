#include <stdio.h>
#include "sensor_parser.h"
#include "sensor_decoder.h"
#include "sensor_window.h"
#include "rule.h"

extern void parse_rules(const char *);
extern void eval_rules(const char *, double, SensorWindow *);

int main()
{
    parse_rules("ruleSensor.cfg");
    print_all_rules();

    SensorWindow temp;
    window_init(&temp);

    FILE *f = fopen("sensor_data.log", "r");
    char line[256];
    SensorRecord rec;

    while (fgets(line, sizeof(line), f))
    {
        if (parse_sensor_line(line, &rec) == 0)
        {
            double v = decode_sensor(rec.sensor, rec.raw);
            window_add(&temp, v);
            eval_rules(rec.sensor, v, &temp);
        }
    }
    fclose(f);
}
