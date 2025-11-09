#include "system.h"
#include "adc.h"
#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include "config.h"

#ifndef DEMO_STORAGE_CLASS
#include "controller.h"
#include "sensors.h"
#endif /* DEMO_STORAGE_CLASS */

static uint32_t s_tickCounter = 0;
void delayMs(uint32_t ms);

void System_init(void)
{
    uartInit(BAUD_RATE);
    gpioInit();
    adcInit();

#ifndef DEMO_STORAGE_CLASS
    controllerInit();
#endif /* DEMO_STORAGE_CLASS */

    printf("-->[SYSTEM] Init done.\n\n");
    GpioReg_dumpLayout();
}

void System_run(void)
{
    static uint8_t s_localCounter = 0;
    SystemState_t retState = SYS_IDLE;

    s_tickCounter++;
    s_localCounter++;

#ifndef DEMO_STORAGE_CLASS
    /* --- Full system demo --- */
    SensorData_t sensor;
    sensorUpdate(&sensor);
    controllerRun(&sensor);
#endif /* DEMO_STORAGE_CLASS */
    adcRead();
    printf("\t[SYSTEM] Global Tick=%lu | Local Counter=%u | Value ADC=%u\n\n",
           (unsigned long)s_tickCounter, s_localCounter, g_adcDataReg);
    delayMs(2000);
}
