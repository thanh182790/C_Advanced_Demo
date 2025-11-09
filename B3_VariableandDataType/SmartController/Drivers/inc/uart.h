#ifndef UART_H
#define UART_H
#include <stdint.h>

void uartInit(uint32_t baud);
void uartSend(const char* msg);

#endif
