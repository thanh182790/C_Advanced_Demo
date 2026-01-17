#include "action/action_dispatcher.h"
#include "common/log.h"

static void action_log(rule_t *r, sensor_sample_t *s)
{
    LOG_WARN("LOG: %s (value=%.2f)", r->message, s->value);
}

static void action_alert(rule_t *r, sensor_sample_t *s)
{
    LOG_ERR("ALERT: %s", r->message);
}

static void action_shutdown(rule_t *r, sensor_sample_t *s)
{
    LOG_ERR("SHUTDOWN TRIGGERED");
}

void action_dispatch(rule_t *r, sensor_sample_t *s)
{
    if (r->action_mask & ACTION_LOG)
        action_log(r, s);
    if (r->action_mask & ACTION_ALERT)
        action_alert(r, s);
    if (r->action_mask & ACTION_SHUTDOWN)
        action_shutdown(r, s);
}

