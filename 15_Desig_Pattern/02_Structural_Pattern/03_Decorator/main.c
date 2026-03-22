#include "base-uart/base-uart.h"
#include <stdio.h>
#include <string.h>

// --- KHAI BÁO PROTOTYPE CÁC HÀM DECORATOR ---
int logging_send(CommunicationChannel *self, const uint8_t *data, size_t length);
int logging_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen);
int encryption_send(CommunicationChannel *self, const uint8_t *data, size_t length);
int encryption_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen);
int crc_send(CommunicationChannel *self, const uint8_t *data, size_t length);
int crc_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen);
int compression_send(CommunicationChannel *self, const uint8_t *data, size_t length);
int compression_receive(CommunicationChannel *self, uint8_t *buffer, size_t maxLen, size_t *rxLen);

// Helper in kết quả cuối cùng tại tầng Application
// void print_app_final_result(int status, uint8_t *buf, size_t len)
// {
//     if (status == 0 && len > 0)
//     {
//         buf[len] = '\0'; // Đảm bảo là chuỗi kết thúc bằng null để in
//         printf("\n[APP FINAL] Dữ liệu nhận được: %s\n", (char *)buf);
//     }
//     else
//     {
//         printf("\n[APP FINAL] Nhận dữ liệu thất bại hoặc lỗi Checksum!\n");
//     }
//     printf("==================================================================\n\n");
// }

int main()
{
    // Dữ liệu JSON cảm biến mẫu
    const char *sensor_json = "{\"temp\":25.5,\"humi\":60,\"status\":\"OKKKK\"}";
    uint8_t rx_buf[512];
    size_t rx_len;
    int status;

    FILE *fLog = fopen("sensor_system.log", "a");
    if (!fLog)
    {
        printf("Lỗi mở file log!\n");
        return 1;
    }

    // 0. KHỞI TẠO TẦNG VẬT LÝ (BASE)
    CommunicationChannel rawChannel = {
        .send = uart_base_send,
        .receive = uart_base_receive,
        .wrappee = NULL};

    printf("--- BẮT ĐẦU CHƯƠNG TRÌNH MÔ PHỎNG 5 BƯỚC ---\n\n");

    // ============================================================
    printf("STEP 1: GỬI DỮ LIỆU THÔ (RAW ONLY)\n");
    rawChannel.send(&rawChannel, (uint8_t *)sensor_json, strlen(sensor_json));
    // status = rawChannel.receive(&rawChannel, rx_buf, 512, &rx_len);
    // print_app_final_result(status, rx_buf, rx_len);

    // ============================================================
    printf("\nSTEP 2: GỬI KÈM CHECKSUM (RAW -> CRC)\n");
    CommunicationChannel app_step2 = {
        .send = crc_send,
        .receive = crc_receive,
        .wrappee = &rawChannel};
    app_step2.send(&app_step2, (uint8_t *)sensor_json, strlen(sensor_json));
    // status = app_step2.receive(&app_step2, rx_buf, 512, &rx_len);

    // ============================================================
    printf("\nSTEP 2: GỬI DỮ LIỆU ĐƯỢC NÉN (RAW -> COMPRESS)\n");
    CommunicationChannel compressChanel = {
        .send = compression_send,
        .receive = compression_receive,
        .wrappee = &rawChannel};
    compressChanel.send(&app_step2, (uint8_t *)sensor_json, strlen(sensor_json));
    // status = app_step2.receive(&app_step2, rx_buf, 512, &rx_len);

    // // ============================================================
    printf("\nSTEP 3: GỬI MÃ HÓA (RAW -> ENCRYPT -> CRC)\n");
    // Cấu trúc: App -> Encrypt -> CRC -> Hardware
    CommunicationChannel app_step3 = {
        .send = encryption_send,
        .receive = encryption_receive,
        .wrappee = &app_step2,
        .context = (void *)0xAB // Key XOR: 0xAB
    };
    app_step3.send(&app_step3, (uint8_t *)sensor_json, strlen(sensor_json));
    // status = app_step3.receive(&app_step3, rx_buf, 512, &rx_len);

    // // ============================================================
    // printf("\nSTEP 4: GỬI NÉN (RAW -> COMPRESS -> ENCRYPT -> CRC )\n");
    // // Cấu trúc: App -> Compress -> Encrypt -> CRC -> Hardware
    // CommunicationChannel app_step4 = {
    //     .send = compression_send,
    //     .receive = compression_receive,
    //     .wrappee = &app_step3};
    // app_step4.send(&app_step4, (uint8_t *)sensor_json, strlen(sensor_json));
    // status = app_step4.receive(&app_step4, rx_buf, 512, &rx_len);

    // // ============================================================
    // printf("\nSTEP 5: FULL OPTION + LOGGING TO FILE (TEXT MODE)\n");
    // // Cấu trúc: App -> Logging -> Compress -> Encrypt -> CRC -> Hardware
    // // Logging đặt ngoài cùng để ghi lại chuỗi JSON sạch trước khi bị biến đổi
    // CommunicationChannel app_step5 = {
    //     .send = logging_send,
    //     .receive = logging_receive,
    //     .wrappee = &app_step4,
    //     .context = (void *)fLog};

    // printf("[INFO] Đang gửi JSON và ghi log vào file 'sensor_system.log'...\n");
    // app_step5.send(&app_step5, (uint8_t *)sensor_json, strlen(sensor_json));
    // status = app_step5.receive(&app_step5, rx_buf, 512, &rx_len);

    fclose(fLog);
    printf("--- KẾT THÚC MÔ PHỎNG ---\n");
    return 0;
}
