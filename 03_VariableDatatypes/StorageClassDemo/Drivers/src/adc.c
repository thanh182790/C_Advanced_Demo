#include "adc.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

volatile uint16_t g_adcDataReg = 0;

void adcInit(void)
{
    srand((unsigned)time(NULL));
    printf("[ADC] Initialized.\n");
}

void adcRead(void)
{
    g_adcDataReg = rand() % 1024;
}
