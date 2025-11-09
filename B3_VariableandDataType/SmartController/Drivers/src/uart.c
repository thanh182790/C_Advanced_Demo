#include "uart.h"
#include <stdio.h>

static uint32_t s_uartBaud = 0;

void uartInit(uint32_t baud)
{
    s_uartBaud = baud;
    printf("[UART] Init baudrate %lu\n", (unsigned long)baud);
}

void uartSend(const char *msg)
{
    printf("\t[UART] %s", msg);
}
