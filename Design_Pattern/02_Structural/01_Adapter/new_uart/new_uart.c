#include <stdio.h>
#include "new_uart.h"

static void new_uart_init(UART_Config *cfg)
{
    printf("[NEW UART] init\n");
    printf("  baud=%u\n", cfg->baudrate);
    printf("  mode=%s\n",
           cfg->mode == UART_MODE_INTERRUPT ? "INTERRUPT" : "POLLING");
}

static void new_uart_write(uint8_t *data, uint32_t len)
{
    printf("[NEW UART] Send: ");
    for (uint32_t i = 0; i < len; i++)
        printf("%c", data[i]);
    printf("\n");
}

static uint32_t new_uart_read(uint8_t *buf, uint32_t len)
{
    const char *msg = "OK";
    uint32_t rlen = 2;
    if (rlen > len) rlen = len;

    for (uint32_t i = 0; i < rlen; i++)
        buf[i] = msg[i];

    printf("[NEW UART] Receive %u bytes\n", rlen);
    return rlen;
}

UART_Interface NewUART_Create(void)
{
    UART_Interface uart = {
        .init  = new_uart_init,
        .write = new_uart_write,
        .read  = new_uart_read
    };
    return uart;
}

