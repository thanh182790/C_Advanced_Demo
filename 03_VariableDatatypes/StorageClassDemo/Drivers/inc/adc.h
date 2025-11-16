#ifndef ADC_H
#define ADC_H
#include <stdint.h>

extern volatile uint16_t g_adcDataReg;

void adcInit(void);
void adcRead(void);

#endif
