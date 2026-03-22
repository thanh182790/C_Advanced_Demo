#include <stdio.h>
#include "legacy_uart.h"

static Legacy_Baud current_baud;
static Legacy_Mode current_mode;

void legacy_uart_set_baud(Legacy_Baud baud)
{
    current_baud = baud;
    printf("[LEGACY UART] Set baud = %s\n",
           baud == LEGACY_UART_BAUD_115200 ? "115200" : "9600");
}

void legacy_uart_set_mode(Legacy_Mode mode)
{
    current_mode = mode;
    printf("[LEGACY UART] Set mode = %s\n",
           mode == LEGACY_UART_MODE_INTERRUPT ? "INTERRUPT" : "POLLING");
}

void legacy_uart_enable(void)
{
    printf("[LEGACY UART] Enabled\n");
}

void legacy_uart_send(uint8_t *data, uint32_t len)
{
    printf("[LEGACY UART] Send: ");
    for (uint32_t i = 0; i < len; i++)
        printf("%c", data[i]);
    printf("\n");
}

uint32_t legacy_uart_recv(uint8_t *buf, uint32_t max_len)
{
    const char *msg = "OK";
    uint32_t len = 2;
    if (len > max_len) len = max_len;

    for (uint32_t i = 0; i < len; i++)
        buf[i] = msg[i];

    printf("[LEGACY UART] Receive %u bytes\n", len);
    return len;
}

