#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int eval_simple(double v, const char *cond) {
    char op[3];
    double x;
    sscanf(cond, "%*s %2s %lf", op, &x);

    if (!strcmp(op, ">")) return v > x;
    if (!strcmp(op, "<")) return v < x;
    if (!strcmp(op, ">=")) return v >= x;
    if (!strcmp(op, "<=")) return v <= x;
    return 0;
}

