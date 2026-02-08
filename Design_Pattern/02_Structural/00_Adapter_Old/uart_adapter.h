#ifndef UART_ADAPTER_H
#define UART_ADAPTER_H

#include "uart_interface.h"

/* Tạo UART interface từ legacy driver */
UART_Interface UART_Adapter_Create(void);

#endif

