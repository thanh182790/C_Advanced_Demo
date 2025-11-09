#ifndef ADC_H
#define ADC_H
#include "types.h"

extern volatile uint16_t g_adcDataReg;

void adcInit(void);
uint16_t adcRead(void);

#endif
