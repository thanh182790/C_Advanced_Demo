#include <stdio.h>
#include "light-sensor.h"

static void lightSensorInit(Sensor *self) {
    printf("Light sensor initialized\n");
}

static float lightSensorReadData(Sensor *self) {
    return 300.0f;
}

static void lightSensorDestroy(Sensor *self) {
    /* nothing to free */
}

Sensor createLightSensor(void) {
    Sensor s;
    s.init     = lightSensorInit;
    s.readData = lightSensorReadData;
    s.destroy  = lightSensorDestroy;
    return s;
}


