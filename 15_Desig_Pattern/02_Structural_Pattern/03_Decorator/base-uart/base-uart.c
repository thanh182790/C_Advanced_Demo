#include "base-uart.h"

static uint8_t wire_buffer[512]; // Giả lập đường dây truyền dẫn
static size_t wire_len = 0;

int uart_base_send(CommunicationChannel *self, const uint8_t *data, size_t length)
{
    (void)self;
    printf("[UART HW] Physical Send: ");
    for (size_t i = 0; i < length; i++)
        printf("%02X ", data[i]);
    printf("\n");
    if (length <= 512)
    {
        memcpy(wire_buffer, data, length);
        wire_len = length;
    }

    return (int)length;
}

int uart_base_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen)
{
    (void)self;

    // Kiểm tra xem "dây" có dữ liệu không
    if (wire_len == 0)
    {
        *rxLen = 0;
        return -1; // Trả về lỗi nếu không có gì để nhận
    }

    // Copy từ "dây dẫn" vào buffer nhận của tầng trên
    size_t copy_size = (wire_len < maxLen) ? wire_len : maxLen;
    memcpy(buffer, wire_buffer, copy_size);
    *rxLen = copy_size;

    printf("[UART HW] Physical Receive (Loopback): ");
    for (size_t i = 0; i < *rxLen; i++)
        printf("%02X ", buffer[i]);
    printf("\n");

    wire_len = 0; // Xóa sạch đường dây sau khi nhận xong để sẵn sàng cho lần gửi tới
    return 0;
}
