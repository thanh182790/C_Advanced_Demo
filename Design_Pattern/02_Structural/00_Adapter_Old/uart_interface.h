#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include <stdint.h>

/* Interface chuẩn cho hệ thống mới */
typedef struct {
    void (*init)(void);
    void (*write)(uint8_t *data, uint32_t len);
    uint32_t (*read)(uint8_t *buf, uint32_t len);
} UART_Interface;

#endif

