#include <stdio.h>
#include "sensor-factory.h"
#include <stdlib.h>

int main(void) {
    Sensor *sensors[] = {
        createSensor(SENSOR_TEMPERATURE),
        createSensor(SENSOR_HUMIDITY),
        createSensor(SENSOR_LIGHT),
        createSensor(SENSOR_PRESSURE)
    };

    for (int i = 0; i < 4; i++) {
        sensors[i]->init(sensors[i]);
        printf("Read value = %.2f\n", sensors[i]->readData(sensors[i]));
    }

    for (int i = 0; i < 4; i++) {
        sensors[i]->destroy(sensors[i]);
        free(sensors[i]);
    }

    return 0;
}
