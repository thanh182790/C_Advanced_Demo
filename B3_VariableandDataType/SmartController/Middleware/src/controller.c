#include "controller.h"
#include "gpio.h"
#include "uart.h"
#include <stdio.h>

static SystemState_t s_currentState = SYS_IDLE;

void controllerInit(void)
{
    s_currentState = SYS_IDLE;
    printf("[CTRL] Controller init.\n");
}

SystemState_t controllerRun(SensorData_t *sensor)
{
    if (sensor->env.temperature > 35.0f)
    {
        uartSend("[CTRL] High temperature!\n");
        gpioWritePin(1, 1);
        s_currentState = SYS_ERROR;
        return SYS_ERROR;
    }
    else
    {
        gpioWritePin(1, 0);
        s_currentState = SYS_ACTIVE;
        return SYS_ACTIVE;
    }
}
