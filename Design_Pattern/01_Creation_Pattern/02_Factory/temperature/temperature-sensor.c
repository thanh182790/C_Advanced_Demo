#include <stdio.h>
#include "temperature-sensor.h"

static void temperatureSensorInit(Sensor *self) {
    printf("Temperature sensor initialized\n");
}

static float temperatureSensorReadData(Sensor *self) {
    return 25.5f;
}

static void temperatureSensorDestroy(Sensor *self) {
    /* nothing to free */
}

Sensor createTemperatureSensor(void) {
    Sensor s;
    s.init     = temperatureSensorInit;
    s.readData = temperatureSensorReadData;
    s.destroy  = temperatureSensorDestroy;
    return s;
}

