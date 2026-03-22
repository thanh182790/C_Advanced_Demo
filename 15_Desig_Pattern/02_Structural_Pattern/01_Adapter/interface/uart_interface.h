#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include <stdint.h>

typedef enum
{
    UART_MODE_POLLING,
    UART_MODE_INTERRUPT
} UART_Mode;

typedef struct
{
    uint32_t baudrate;
    UART_Mode mode;
} UART_Config;

/* Interface chuẩn */
typedef struct
{
    void (*init)(UART_Config *cfg);
    void (*write)(uint8_t *data, uint32_t len);
    uint32_t (*read)(uint8_t *buf, uint32_t len);
} UART_Interface;

#endif
