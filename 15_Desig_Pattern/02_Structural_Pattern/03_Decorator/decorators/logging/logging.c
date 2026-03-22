#include "../base-uart/base-uart.h"
#include <time.h>
#include <stdio.h>
#include <ctype.h>

void write_log(FILE* f, const char* label, const uint8_t* data, size_t len) {
    if (!f) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // 1. Ghi Header: Thời gian | Loại (SEND/RECV) | Kích thước
    fprintf(f, "[%02d:%02d:%02d][%s] Size: %zu bytes\n", 
            t->tm_hour, t->tm_min, t->tm_sec, label, len);
    
    // 2. Ghi dữ liệu dạng HEX (Luôn cần thiết để debug lớp dưới)
    fprintf(f, "   HEX: ");
    for (size_t i = 0; i < len; i++) {
        fprintf(f, "%02X ", data[i]);
    }
    fprintf(f, "\n");

    // 3. Ghi dữ liệu dạng TEXT (Chuỗi JSON sạch)
    // Lưu ý: Chỉ in khi lớp Logging nằm ngoài cùng (dữ liệu chưa bị nén/mã hóa)
    fprintf(f, "   TEXT: ");
    for (size_t i = 0; i < len; i++) {
        // Kiểm tra nếu là ký tự in được thì in ra, không thì in dấu '.'
        if (isprint(data[i])) fprintf(f, "%c", data[i]);
        else fprintf(f, ".");
    }
    fprintf(f, "\n--------------------------------------------------\n");
    
    fflush(f);
}

int logging_send(CommunicationChannel* self, const uint8_t* data, size_t length) {
    write_log((FILE*)self->context, "APP_SEND", data, length);
    return self->wrappee->send(self->wrappee, data, length);
}

int logging_receive(CommunicationChannel* self, uint8_t* buffer, size_t maxLen, size_t* rxLen) {
    int res = self->wrappee->receive(self->wrappee, buffer, maxLen, rxLen);
    if (res == 0 && *rxLen > 0) {
        write_log((FILE*)self->context, "APP_RECV", buffer, *rxLen);
    }
    return res;
}