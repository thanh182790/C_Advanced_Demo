#include "rule.h"
#include <stdio.h>
#include <string.h>

Rule rules[16];
int rule_count = 0;

void parse_rules(const char *file)
{
    FILE *f = fopen(file, "r");
    char line[256];
    Rule *r = NULL;

    while (fgets(line, sizeof(line), f))
    {
        if (line[0] == '[')
        {
            r = &rules[rule_count++];
            sscanf(line, "[%[^]]", r->name);
        }
        else if (r)
        {
            sscanf(line, "SENSOR=%s", r->sensor);
            if (strstr(line, "MODE=AVG"))
                r->mode = MODE_AVG;
            if (strstr(line, "MODE=INSTANT"))
                r->mode = MODE_INSTANT;
            sscanf(line, "WINDOW=%d", &r->window);
            sscanf(line, "STATEFUL=%d", &r->stateful);
            sscanf(line, "PERSIST_COUNT=%d", &r->persist);
            sscanf(line, "CONDITION=%[^\n]", r->condition);
            sscanf(line, "ACTION=%[^\n]", r->action);
            sscanf(line, "MESSAGE=%[^\n]", r->message);
        }
    }
    fclose(f);
}

void print_all_rules(void) {
    printf("========== LOADED RULES ==========\n");

    for (int i = 0; i < rule_count; i++) {
        Rule *r = &rules[i];

        printf("Rule #%d\n", i + 1);
        printf("  Name       : %s\n", r->name);
        printf("  Sensor     : %s\n", r->sensor);
        printf("  Mode       : %s\n",
               r->mode == MODE_AVG ? "AVG" : "INSTANT");
        printf("  Window     : %d\n", r->window);
        printf("  Stateful   : %s\n", r->stateful ? "YES" : "NO");
        printf("  PersistCnt : %d\n", r->persist);
        printf("  Condition  : %s\n", r->condition);
        printf("  Action     : %s\n", r->action);
        printf("  Message    : %s\n", r->message);
        printf("---------------------------------\n");
    }

    printf("Total rules loaded: %d\n", rule_count);
    printf("=================================\n");
}