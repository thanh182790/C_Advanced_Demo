#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

#include "publisher.h"

/* Các cảm biến chính là các thực thể cụ thể để các subcriber đki nhận thông báo */
typedef struct
{
    Publisher base;
    int isOpen;
} DoorSensor;

void doorSensorInit(DoorSensor *sensor);
void doorSensorTrigger(DoorSensor *sensor, int open);

#endif // DOOR_SENSOR_H
