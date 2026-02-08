#include <stdio.h>
#include "humidity-sensor.h"

static void humiditySensorInit(Sensor *self) {
    printf("Humidity sensor initialized\n");
}

static float humiditySensorReadData(Sensor *self) {
    return 60.0f;
}

static void humiditySensorDestroy(Sensor *self) {
    /* nothing to free */
}

Sensor createHumiditySensor(void) {
    Sensor s;
    s.init     = humiditySensorInit;
    s.readData = humiditySensorReadData;
    s.destroy  = humiditySensorDestroy;
    return s;
}

