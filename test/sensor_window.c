#include "sensor_window.h"

void window_init(SensorWindow *w)
{
    w->count = 0;
    w->idx = 0;
}

void window_add(SensorWindow *w, double v)
{
    w->buf[w->idx++] = v;
    if (w->idx >= MAX_WINDOW)
        w->idx = 0;
    if (w->count < MAX_WINDOW)
        w->count++;
}

double window_avg(SensorWindow *w)
{
    if (w->count == 0)
        return 0;
    double s = 0;
    for (int i = 0; i < w->count; i++)
        s += w->buf[i];
    return s / w->count;
}
