#include "uart_adapter.h"
#include "legacy_uart.h"

/* Adapter functions */

static void adapter_init(void)
{
    /* Adapter quyết định cấu hình */
    legacy_uart_init(115200);
}

static void adapter_write(uint8_t *data, uint32_t len)
{
    legacy_uart_send_bytes(data, len);
}

static uint32_t adapter_read(uint8_t *buf, uint32_t len)
{
    return legacy_uart_receive(buf, len);
}

UART_Interface UART_Adapter_Create(void)
{
    UART_Interface uart;

    uart.init  = adapter_init;
    uart.write = adapter_write;
    uart.read  = adapter_read;

    return uart;
}

