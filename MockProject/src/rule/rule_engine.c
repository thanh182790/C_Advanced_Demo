#include "rule/rule_engine.h"
#include "rule/rule_condition.h"
#include "sensor/sensor_buffer.h"
#include "action/action_dispatcher.h"

static rule_t rule_table[16];
static int rule_count;

void rule_engine_init(void)
{
    rule_count = rule_parse_file("config/ruleSensor.cfg",
                                 rule_table, 16);
}

void rule_engine_eval(sensor_sample_t *s)
{
    for (int i = 0; i < rule_count; i++) {
        rule_t *r = &rule_table[i];
        if (r->sensor != s->type) continue;

        float val = (r->mode == MODE_AVG) ?
            sensor_buffer_avg(s->type) : s->value;

        int ok = rule_condition_eval(r->condition, val);

        if (ok) {
            r->hit++;
            if (!r->stateful || r->hit >= r->persist) {
                action_dispatch(r, s);
                r->hit = 0;
            }
        } else {
            r->hit = 0;
        }
    }
}

