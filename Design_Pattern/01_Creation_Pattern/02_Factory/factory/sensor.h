#ifndef SENSOR_H
#define SENSOR_H

typedef struct Sensor {
    void (*init)(struct Sensor *self);
    float (*readData)(struct Sensor *self);
    void (*destroy)(struct Sensor *self);
} Sensor;

#endif // SENSOR_H

