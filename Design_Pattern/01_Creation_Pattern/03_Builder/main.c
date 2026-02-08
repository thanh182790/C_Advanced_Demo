#include <stdio.h>
#include "uart-builder.h"

static void print_uart_config(const UART_Config_t* cfg) {
    printf("UART Configuration:\n");
    printf("  Baud Rate : %u\n", cfg->baudRate);
    printf("  Parity    : %d\n", cfg->parity);
    printf("  Stop Bits : %d\n", cfg->stopBits);
    printf("  Data Bits : %d\n", cfg->dataBits);
}

int main(void) {
    UART_Builder builder = UART_Builder_Init();
    // UART_Config_t uartConfig = builder.build(&builder);
    UART_Config_t uartConfig =
        builder.setBaudRate(&builder, BAUDRATE_115200)
               ->setParity(&builder, UART_PARITY_ODD)
               ->setStopBits(&builder, 2)
               ->setDataBits(&builder, 9)
               ->build(&builder);

    print_uart_config(&uartConfig);

    return 0;
}

