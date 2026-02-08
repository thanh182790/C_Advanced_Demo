#include <stdio.h>
#include "legacy_uart_adapter.h"
#include "legacy_uart.h"

static Legacy_Baud map_baud(uint32_t baud)
{
    switch (baud) {
    case 115200: return LEGACY_UART_BAUD_115200;
    case 9600:
    default:
        return LEGACY_UART_BAUD_9600;
    }
}

static Legacy_Mode map_mode(UART_Mode mode)
{
    return (mode == UART_MODE_INTERRUPT)
           ? LEGACY_UART_MODE_INTERRUPT
           : LEGACY_UART_MODE_POLLING;
}

static void adapter_init(UART_Config *cfg)
{
    printf("[ADAPTER] Translating UART_Config -> legacy API\n");

    legacy_uart_set_baud(map_baud(cfg->baudrate));
    legacy_uart_set_mode(map_mode(cfg->mode));
    legacy_uart_enable();
}

static void adapter_write(uint8_t *data, uint32_t len)
{
    legacy_uart_send(data, len);
}

static uint32_t adapter_read(uint8_t *buf, uint32_t len)
{
    return legacy_uart_recv(buf, len);
}

UART_Interface LegacyUART_Adapter_Create(void)
{
    UART_Interface uart = {
        .init  = adapter_init,
        .write = adapter_write,
        .read  = adapter_read
    };
    return uart;
}

