#ifndef LEGACY_UART_H
#define LEGACY_UART_H

#include <stdint.h>

typedef enum {
    LEGACY_UART_BAUD_9600,
    LEGACY_UART_BAUD_115200
} Legacy_Baud;

typedef enum {
    LEGACY_UART_MODE_POLLING,
    LEGACY_UART_MODE_INTERRUPT
} Legacy_Mode;

void legacy_uart_set_baud(Legacy_Baud baud);
void legacy_uart_set_mode(Legacy_Mode mode);
void legacy_uart_enable(void);

void legacy_uart_send(uint8_t *data, uint32_t len);
uint32_t legacy_uart_recv(uint8_t *buf, uint32_t max_len);

#endif

