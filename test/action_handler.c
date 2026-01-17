#include <stdio.h>
#include "rule.h"

void execute_action(Rule *r) {
    printf("[ACTION] %s : %s\n", r->name, r->message);
}

