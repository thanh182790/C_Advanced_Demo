#include "../base-uart/base-uart.h"

int encryption_send(CommunicationChannel *self, const uint8_t *data, size_t length)
{
    uint8_t key = (uint8_t)(uintptr_t)self->context;
    uint8_t encrypted[length];
    for (size_t i = 0; i < length; i++)
    {
        encrypted[i] = data[i] ^ key; // Thuật toán XOR
    }
    printf("[ENCRYPT] XOR with 0x%02X\n", key);
    return self->wrappee->send(self->wrappee, encrypted, length);
}

int encryption_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen)
{
    // 1. Nhận dữ liệu (đang bị mã hóa) từ tầng dưới
    int res = self->wrappee->receive(self->wrappee, buffer, maxLen, rxLen);

    if (res == 0 && *rxLen > 0)
    {
        uint8_t key = (uint8_t)(uintptr_t)self->context;
        // 2. Giải mã bằng cách XOR ngược lại với cùng một Key
        for (size_t i = 0; i < *rxLen; i++)
        {
            buffer[i] = buffer[i] ^ key;
        }
        printf("[DECRYPT] Data decrypted with key 0x%02X\n", key);
    }
    return res;
}