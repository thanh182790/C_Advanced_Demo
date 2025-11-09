#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "sensors.h"
#include "error.h"

typedef enum
{
    SYS_IDLE = 0,
    SYS_ACTIVE,
    SYS_ERROR
} SystemState_t;

void controllerInit(void);
SystemState_t controllerRun(SensorData_t *sensor);

#endif
