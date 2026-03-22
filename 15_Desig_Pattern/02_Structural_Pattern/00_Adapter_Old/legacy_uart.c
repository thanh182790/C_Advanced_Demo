#include <stdio.h>
#include "legacy_uart.h"

void legacy_uart_init(uint32_t baud)
{
    printf("[LEGACY] UART init, baud=%u\n", baud);
}

void legacy_uart_send_bytes(uint8_t *data, uint32_t len)
{
    printf("[LEGACY] Send %u bytes: ", len);
    for (uint32_t i = 0; i < len; i++)
        printf("%c", data[i]);
    printf("\n");
}

uint32_t legacy_uart_receive(uint8_t *buf, uint32_t max_len)
{
    const char *msg = "OK";
    uint32_t len = 2;

    if (len > max_len) len = max_len;

    for (uint32_t i = 0; i < len; i++)
        buf[i] = msg[i];

    printf("[LEGACY] Receive %u bytes\n", len);
    return len;
}

