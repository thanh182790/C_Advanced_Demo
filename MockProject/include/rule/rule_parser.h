#ifndef RULE_PARSER_H
#define RULE_PARSER_H

#include "rule_types.h"

int rule_parse_file(const char *path, rule_t *rules, int max_rule);

#endif

