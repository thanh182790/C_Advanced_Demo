#ifndef ACTION_DISPATCHER_H
#define ACTION_DISPATCHER_H

#include "rule_types.h"
#include "sensor_types.h"

void action_dispatch(rule_t *r, sensor_sample_t *s);

#endif

