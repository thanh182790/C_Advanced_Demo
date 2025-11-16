#include "system.h"
#include "adc.h"
#include "uart.h"
#include <stdio.h>
#include "config.h"

static uint32_t s_tickCounter = 0;
void delayMs(uint32_t ms);

void System_init(void)
{
    uartInit(BAUD_RATE);
    adcInit();
    printf("-->[SYSTEM] Init done.\n\n");
}

void System_run(void)
{
    static uint8_t s_localCounter = 0;

    s_tickCounter++;
    s_localCounter++;
    adcRead();
    printf("\t[SYSTEM] Global Tick=%lu | Local Counter=%u | Value ADC=%u\n\n",
           (unsigned long)s_tickCounter, s_localCounter, g_adcDataReg);
    delayMs(2000);
}
