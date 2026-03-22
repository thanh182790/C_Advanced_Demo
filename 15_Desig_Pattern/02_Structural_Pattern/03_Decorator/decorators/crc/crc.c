#include "../base-uart/base-uart.h"

/* Hàm tính checksum của data */
uint8_t calculate_crc8_simple(const uint8_t *data, size_t length)
{
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x07;
            else
                crc <<= 1;
        }
    }
    return crc;
}

int crc_send(CommunicationChannel *self, const uint8_t *data, size_t length)
{
    uint8_t packet[length + 1];
    memcpy(packet, data, length);
    /* Thêm 1 field checksum vào cuối data */
    packet[length] = calculate_crc8_simple(data, length);
    printf("[CRC] Appended: 0x%02X\n", packet[length]);
    /* Gọi sang hàm send của đối tượng con */
    return self->wrappee->send(self->wrappee, packet, length + 1);
}

int crc_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen)
{
    uint8_t tempBuffer[maxLen + 1];
    size_t tempLen = 0;

    // 1. Lấy dữ liệu từ tầng dưới (có kèm byte CRC ở cuối)
    int res = self->wrappee->receive(self->wrappee, tempBuffer, maxLen + 1, &tempLen);

    if (res == 0 && tempLen > 0)
    {
        // 2. Tách byte CRC cuối cùng
        uint8_t received_crc = tempBuffer[tempLen - 1];
        size_t data_len = tempLen - 1;

        // 3. Tính toán lại CRC dựa trên data thực tế nhận được
        uint8_t calculated_crc = calculate_crc8_simple(tempBuffer, data_len);

        if (received_crc == calculated_crc)
        {
            // 4. Khớp mã: Copy data sạch vào buffer cho App
            memcpy(buffer, tempBuffer, data_len);
            *rxLen = data_len;
            printf("[CRC] Checksum OK (0x%02X)\n", received_crc);
            return 0;
        }
        else
        {
            // 5. Sai mã: Hủy gói tin
            *rxLen = 0;
            printf("[CRC] Checksum ERROR! (Recv: 0x%02X != Calc: 0x%02X)\n", received_crc, calculated_crc);
            return -1; // Trả về lỗi
        }
    }
    return res;
}