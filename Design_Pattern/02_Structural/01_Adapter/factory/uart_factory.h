#ifndef UART_FACTORY_H
#define UART_FACTORY_H

#include "uart_interface.h"

typedef enum {
    UART_DRIVER_NEW,
    UART_DRIVER_LEGACY
} UART_DriverType;

UART_Interface UART_Factory_Create(UART_DriverType type);

#endif

