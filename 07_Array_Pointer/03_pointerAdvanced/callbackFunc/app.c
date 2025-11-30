#include <stdio.h>
#include "uart_driver.h"

void app_uart_rx_handler(const uint8_t *data, size_t len)
{
    printf("[APP] Callback invoked! Received message: ");

    for (size_t i = 0; i < len; i++)
    {
        printf("%c", data[i]);
    }
    printf("\n");
}

void app_init(void)
{
    printf("[APP] Initializing APP layer...\n");

    uart_register_callback(app_uart_rx_handler);
}
