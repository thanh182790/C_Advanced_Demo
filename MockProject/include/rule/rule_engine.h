#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include "rule_types.h"

void rule_engine_init(void);
void rule_engine_eval(sensor_sample_t *s);

#endif

