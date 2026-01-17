#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rule/rule_parser.h"

static sensor_type_t parse_sensor(const char *s)
{
    if (!strcmp(s, "TEMP")) return SENSOR_TEMP;
    if (!strcmp(s, "HUMI")) return SENSOR_HUMI;
    if (!strcmp(s, "LIGHT")) return SENSOR_LIGHT;
    if (!strcmp(s, "PRESS")) return SENSOR_PRESS;
    if (!strcmp(s, "POWER_VOLTAGE")) return SENSOR_POWER_VOLT;
    if (!strcmp(s, "POWER_CURRENT")) return SENSOR_POWER_CURR;
    if (!strcmp(s, "ACCEL")) return SENSOR_ACCEL;
    return SENSOR_MAX;
}

static rule_mode_t parse_mode(const char *s)
{
    if (!strcmp(s, "AVG")) return MODE_AVG;
    return MODE_INSTANT;
}

int rule_parse_file(const char *path, rule_t *rules, int max_rule)
{
    FILE *fp = fopen(path, "r");
    if (!fp) return -1;

    char line[256];
    rule_t *r = NULL;
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {

        if (line[0] == '[') {
            if (count >= max_rule) break;
            r = &rules[count++];
            memset(r, 0, sizeof(*r));
            sscanf(line, "[%63[^]]", r->name);
            continue;
        }

        if (!r || line[0] == '#' || line[0] == '\n')
            continue;

        char key[64], val[128];
        if (sscanf(line, "%63[^=]=%127[^\n]", key, val) != 2)
            continue;

        if (!strcmp(key, "SENSOR"))
            r->sensor = parse_sensor(val);
        else if (!strcmp(key, "MODE"))
            r->mode = parse_mode(val);
        else if (!strcmp(key, "WINDOW"))
            r->window = atoi(val);
        else if (!strcmp(key, "STATEFUL"))
            r->stateful = (!strcmp(val, "YES"));
        else if (!strcmp(key, "PERSIST_COUNT"))
            r->persist = atoi(val);
        else if (!strcmp(key, "CONDITION"))
            strncpy(r->condition, val, sizeof(r->condition));
        else if (!strcmp(key, "MESSAGE"))
            strncpy(r->message, val, sizeof(r->message));
        else if (!strcmp(key, "ACTION")) {
            if (strstr(val, "LOG")) r->action_mask |= ACTION_LOG;
            if (strstr(val, "ALERT")) r->action_mask |= ACTION_ALERT;
            if (strstr(val, "SHUTDOWN")) r->action_mask |= ACTION_SHUTDOWN;
        }
    }

    fclose(fp);
    return count;
}

