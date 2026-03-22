#include "../base-uart/base-uart.h"

/**
 * @brief Hàm nén dữ liệu theo thuật toán RLE
 * Ví dụ: {0xAA, 0xAA, 0xAA} -> {3, 0xAA}
 */
size_t rle_compress(const uint8_t *input, size_t inputLen, uint8_t *output, size_t maxOutputLen)
{
    size_t outIdx = 0;
    for (size_t i = 0; i < inputLen; i++)
    {
        uint8_t count = 1;
        // Đếm các byte trùng lặp liên tiếp (tối đa 255 vì count là 1 byte)
        while (i + 1 < inputLen && input[i] == input[i + 1] && count < 255)
        {
            count++;
            i++;
        }

        // Kiểm tra xem còn đủ chỗ trong buffer output không (cần 2 byte cho mỗi cặp)
        if (outIdx + 2 <= maxOutputLen)
        {
            output[outIdx++] = count;    // Byte 1: Số lượng
            output[outIdx++] = input[i]; // Byte 2: Giá trị
        }
        else
        {
            break; // Buffer output đầy
        }
    }

    return outIdx;
}

/**
 * @brief Hàm giải nén dữ liệu RLE
 * Ví dụ: {3, 0xAA} -> {0xAA, 0xAA, 0xAA}
 */
size_t rle_decompress(const uint8_t *input, size_t inputLen, uint8_t *output, size_t maxOutputLen)
{
    size_t outIdx = 0;
    // Mỗi cặp nén chiếm 2 byte, nên ta nhảy bước i += 2
    for (size_t i = 0; i + 1 < inputLen; i += 2)
    {
        uint8_t count = input[i];
        uint8_t value = input[i + 1];

        // Bung dữ liệu ra theo số lượng đã lưu
        for (uint8_t j = 0; j < count; j++)
        {
            if (outIdx < maxOutputLen)
            {
                output[outIdx++] = value;
            }
            else
            {
                return outIdx; // Tránh tràn buffer nhận
            }
        }
    }
    return outIdx;
}

// --- HÀM DECORATOR CHO SEND ---
int compression_send(CommunicationChannel *self, const uint8_t *data, size_t length)
{
    uint8_t compressed[length * 2]; // Buffer tạm (trường hợp xấu nhất nén bị phình to)
    size_t compressedLen = rle_compress(data, length, compressed, sizeof(compressed));

    printf("[COMPRESS] Original: %zu bytes -> Compressed: %zu bytes\n", length, compressedLen);

    // Chuyển dữ liệu ĐÃ NÉN xuống lớp dưới (wrappee)
    return self->wrappee->send(self->wrappee, compressed, compressedLen);
}

// --- HÀM DECORATOR CHO RECEIVE ---
int compression_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen)
{
    uint8_t tempBuffer[maxLen]; // Chứa dữ liệu thô nhận được từ UART (đang ở dạng nén)
    size_t tempLen = 0;

    // 1. Nhận dữ liệu nén từ tầng dưới
    int res = self->wrappee->receive(self->wrappee, tempBuffer, maxLen, &tempLen);

    if (res == 0 && tempLen > 0)
    {
        // 2. Giải nén dữ liệu ra buffer chính của Application
        *rxLen = rle_decompress(tempBuffer, tempLen, buffer, maxLen);
        printf("[DECOMPRESS] Received %zu bytes -> Decompressed to: %zu bytes\n", tempLen, *rxLen);
    }
    else
    {
        *rxLen = 0;
    }
    return res;
}