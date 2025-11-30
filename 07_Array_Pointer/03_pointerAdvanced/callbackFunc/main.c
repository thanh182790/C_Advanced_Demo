// main.c
#include <stdio.h>
#include "uart_driver.h"

void app_init(void);

int main()
{
    uart_init(); // Init UART driver
    app_init();  // APP đăng ký callback

    // Mô phỏng UART driver nhận dữ liệu
    const uint8_t data[] = "Hello from UART!";
    uart_simulate_receive(data, sizeof(data) - 1);

    return 0;
}
