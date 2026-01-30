#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

// === HÀM IN RA MỘT GIÁ TRỊ THEO KIỂU (để debug) ===
void print_arg(const char *type, void *value)
{
    if (strcmp(type, "int") == 0)
    {
        printf("int: %d", *(int *)value);
    }
    else if (strcmp(type, "double") == 0)
    {
        printf("double: %.6f", *(double *)value);
    }
    else if (strcmp(type, "char*") == 0)
    {
        printf("string: \"%s\"", (char *)value);
    }
    else if (strcmp(type, "long") == 0)
    {
        printf("long: %ld", *(long *)value);
    }
    else
    {
        printf("unknown type: %s", type);
    }
}

/*
va_list: Một kiểu dữ liệu để chứa danh sách các đối số.
va_start(ap, last_arg): Khởi tạo danh sách đối số ap. last_arg là tên của đối số cố định cuối cùng trước khi danh sách thay đổi bắt đầu.
va_arg(ap, type): Lấy đối số tiếp theo từ danh sách ap với kiểu dữ liệu là type.
va_end(ap): Dọn dẹp danh sách đối số sau khi sử dụng xong
*/
// === LOGGER CHÍNH: DÙNG va_copy ĐỂ IN DEBUG + GHI LOG ===
void Logger(const char *level, const char *fmt, ...)
{
    // --- BƯỚC 1: LẤY THỜI GIAN ---
    time_t now = time(NULL);
    char *t = ctime(&now);
    t[24] = '\0'; // Xóa \n

    // --- BƯỚC 2: KHỞI ĐỘNG va_list ---
    va_list ap;
    va_start(ap, fmt);

    // --- BƯỚC 3: SAO CHÉP va_list ĐỂ DÙNG 2 LẦN ---
    va_list ap_copy;
    va_copy(ap_copy, ap);

    // --- DEBUG: IN RA TẤT CẢ CÁC THAM SỐ TRUYỀN VÀO ---
    printf("-> [DEBUG] Tham so truyen vao: ");
    const char *p = fmt;
    int in_format = 0;
    char current_type[20] = {0};

    while (*p)
    {
        if (*p == '%')
        {
            if (in_format)
            {
                // Đã gặp %% → bỏ qua
                in_format = 0;
            }
            else
            {
                in_format = 1;
            }
        }
        else if (in_format)
        {
            // Xác định kiểu từ format specifier
            if (*p == 'd' || *p == 'i')
            {
                strcpy(current_type, "int");
                int val = va_arg(ap, int);
                print_arg(current_type, &val);
            }
            else if (*p == 'f' || *p == 'g' || *p == 'e')
            {
                strcpy(current_type, "double");
                double val = va_arg(ap, double);
                print_arg(current_type, &val);
            }
            else if (*p == 's')
            {
                strcpy(current_type, "char*");
                char *val = va_arg(ap, char *);
                print_arg(current_type, val);
            }
            else if (*p == 'l' && *(p + 1) == 'd')
            {
                strcpy(current_type, "long");
                long val = va_arg(ap, long);
                print_arg(current_type, &val);
                p++; // Bỏ qua 'd'
            }
            else
            {
                printf("[unknown: %%%c]", *p);
            }
            printf(", ");
            in_format = 0;
        }
        p++;
    }
    printf("\n");

    // --- GHI LOG THẬT SỰ DÙNG va_copy ---
    printf("[%s] [%s] ", t, level);
    vprintf(fmt, ap_copy); // DÙNG BẢN SAO
    printf("\n");

    // --- BƯỚC 4: DỌN DẸP ---
    va_end(ap_copy); // Dọn bản sao
    va_end(ap);      // Dọn bản gốc
}

int main()
{
    Logger("INFO", "Khoi dong he thong");
    Logger("WARN", "CPU qua tai: %d%%", 92);
    Logger("ERROR", "Khong ket noi duoc %s tai port %d", "db.server.com", 3306);
    Logger("DEBUG", "Gia tri: %f, ma: %ld, chuoi: %s", 3.14159, 987654321L, "Test va_list");

    return 0;
}
