#include <stdio.h>
#include "pressure-sensor.h"

static void pressureSensorInit(Sensor *self) {
    printf("Pressure sensor initialized\n");
}

static float pressureSensorReadData(Sensor *self) {
    return 20.0f;
}

static void pressureSensorDestroy(Sensor *self) {
    /* nothing to free */
}

Sensor createPressureSensor(void) {
    Sensor s;
    s.init     = pressureSensorInit;
    s.readData = pressureSensorReadData;
    s.destroy  = pressureSensorDestroy;
    return s;
}

