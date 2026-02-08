#include <stdio.h>
#include "uart_factory.h"

int main(void)
{
    UART_Config cfg = {
        .baudrate = 115200,
        .mode     = UART_MODE_INTERRUPT
    };

    /* Đổi NEW <-> LEGACY mà app không đổi dòng nào */
    UART_Interface uart =
        UART_Factory_Create(UART_DRIVER_NEW);
        // UART_Factory_Create(UART_DRIVER_LEGACY);

    uart.init(&cfg);

    uint8_t msg[] = "Hello UART Interface";
    uart.write(msg, sizeof(msg) - 1);

    uint8_t buf[8];
    uint32_t len = uart.read(buf, sizeof(buf));

    printf("[APP] Received %u bytes: %.*s\n", len, len, buf);
    return 0;
}

