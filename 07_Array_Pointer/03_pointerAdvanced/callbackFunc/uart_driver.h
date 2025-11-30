// uart_driver.h
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>
#include <stddef.h>

typedef void (*uart_rx_callback_t)(const uint8_t *data, size_t len);

void uart_init(void);
void uart_register_callback(uart_rx_callback_t cb);
void uart_simulate_receive(const uint8_t *data, size_t len);

#endif
