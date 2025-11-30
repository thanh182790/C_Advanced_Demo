#include <stdio.h>
#include "uart_driver.h"

static uart_rx_callback_t app_callback = NULL;

void uart_init(void)
{
    printf("[DRIVER] UART initialized\n");
}

void uart_register_callback(uart_rx_callback_t cb)
{
    app_callback = cb;
    printf("[DRIVER] APP callback registered!\n");
}

// Hàm này mô phỏng việc UART nhận được dữ liệu từ hardware
void uart_simulate_receive(const uint8_t *data, size_t len)
{
    printf("[DRIVER] UART received %zu bytes\n", len);

    if (app_callback)
    {
        printf("[DRIVER] Calling APP callback...\n");
        app_callback(data, len);
    }
    else
    {
        printf("[DRIVER] No callback registered!\n");
    }
}
