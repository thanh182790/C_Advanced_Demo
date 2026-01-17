#ifndef SENSOR_WINDOW_H
#define SENSOR_WINDOW_H

#define MAX_WINDOW 10

typedef struct
{
    double buf[MAX_WINDOW];
    int count;
    int idx;
} SensorWindow;

void window_init(SensorWindow *w);
void window_add(SensorWindow *w, double v);
double window_avg(SensorWindow *w);

#endif
