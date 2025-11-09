#ifndef GPIO_H
#define GPIO_H
#include "registers.h"

void gpioInit(void);
void gpioWritePin(uint8_t pin, uint8_t value);

#endif
