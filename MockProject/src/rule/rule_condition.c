#include <stdio.h>
#include <string.h>
#include "rule/rule_condition.h"

int rule_condition_eval(const char *cond, float value)
{
    char op[3];
    float threshold;

    if (sscanf(cond, "AVG %2s %f", op, &threshold) == 2 ||
        sscanf(cond, "VALUE %2s %f", op, &threshold) == 2) {

        if (!strcmp(op, ">=")) return value >= threshold;
        if (!strcmp(op, "<=")) return value <= threshold;
        if (!strcmp(op, ">"))  return value > threshold;
        if (!strcmp(op, "<"))  return value < threshold;
        if (!strcmp(op, "==")) return value == threshold;
    }

    return 0;
}

