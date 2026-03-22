#ifndef BASE_UART_H
#define BASE_UART_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CommunicationChannel
{
    int (*send)(struct CommunicationChannel *self, const uint8_t *data, size_t length);
    int (*receive)(struct CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen);
    struct CommunicationChannel *wrappee;
    void* context; /* Nếu kênh truyền cần mã hoá thì dùng để lưu key mã hoá */
} CommunicationChannel;

int uart_base_send(CommunicationChannel *self, const uint8_t *data, size_t length);
int uart_base_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen);

#endif