#include "gpio.h"
#include <stdio.h>

static uint8_t s_gpioState = 0;

void gpioInit(void)
{
    g_gpioSimReg.reg.CTRL.EN = 1;
    g_gpioSimReg.reg.CTRL.MODE = 1;
    printf("[GPIO] Initialized. EN=%d MODE=%d\n", g_gpioSimReg.reg.CTRL.EN, g_gpioSimReg.reg.CTRL.MODE);
}

void gpioWritePin(uint8_t pin, uint8_t value)
{
    if (g_gpioSimReg.reg.CTRL.EN)
    {
        BIT_WRITE(g_gpioSimReg.reg.DATA.all, pin, value);
        s_gpioState = value;
        printf("\t[GPIO] Pin %d set to %d (DATA=0x%04X), %s\n",
                pin, value, g_gpioSimReg.reg.DATA.all, (value == 0)?"LED OFF":"LED ON");
    }
}
