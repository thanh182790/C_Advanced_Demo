#if 0

#include "uart_interface.h"
#include "legacy_uart.h"

int main(void)
{
    UART_Interface uart;

    /*  Không gán được:
     * legacy_uart_init cần baud
     * interface init() không có tham số
     */

    uart.init = legacy_uart_init;   // SAI THIẾT KẾ 
    uart.write = legacy_uart_send_bytes;
    uart.read = legacy_uart_receive;

    return 0;
}

#endif


#if 1

#include <stdio.h>
#include "uart_adapter.h"

int main(void)
{
    UART_Interface uart = UART_Adapter_Create();

    uart.init();

    uint8_t msg[] = "Hello UART";
    uart.write(msg, sizeof(msg) - 1);

    uint8_t buf[10];
    uint32_t len = uart.read(buf, sizeof(buf));

    printf("App received %u bytes: %.*s\n", len, len, buf);

    return 0;
}

#endif


