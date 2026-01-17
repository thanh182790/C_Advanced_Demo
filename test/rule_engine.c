#include "rule.h"
#include "sensor_window.h"
#include <string.h>

extern int eval_simple(double, const char *);
extern void execute_action(Rule *);

void eval_rules(const char *sensor, double value, SensorWindow *w) {
    for (int i = 0; i < rule_count; i++) {
        Rule *r = &rules[i];
        if (strcmp(r->sensor, sensor)) continue;

        double v = (r->mode == MODE_AVG) ? window_avg(w) : value;
        if (eval_simple(v, r->condition)) {
            execute_action(r);
        }
    }
}

