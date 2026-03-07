/******************************************************************************
 *TRIỂN KHAI STACK DÙNG LINKED LIST
 * ----------------------------------------------------------------------------
 * 1. CHỨC NĂNG:
 * - Khởi tạo Stack rỗng (Init).
 * - Thêm ký tự vào đỉnh Stack (Push).
 * - Lấy ký tự ra khỏi đỉnh Stack (Pop).
 * - Kiểm tra Stack rỗng (IsEmpty) để tránh lỗi truy cập vùng nhớ NULL.
 * - Giải phóng toàn bộ bộ nhớ Stack (Clear) sau khi xử lý xong gói tin.
 * * 2. BÀI TOÁN: "IOT DATA INTEGRITY CHECKER"
 * - Giả sử Gateway nhận được chuỗi dữ liệu (JSON-like) từ cảm biến qua UART.
 * - Trước khi tốn tài nguyên để Parse dữ liệu, hệ thống cần kiểm tra xem
 * các cặp ngoặc '{ }', '[ ]', '( )' có đóng/mở đúng thứ tự hay không.
 * - Nếu sai định dạng, Gateway sẽ hủy bỏ gói tin ngay lập tức để tiết kiệm CPU.
 * * 3. ƯU ĐIỂM CỦA LINKED LIST STACK TRONG NHÚNG:
 * - Kích thước linh hoạt: Chỉ tốn RAM khi gói tin phức tạp (nhiều lớp lồng nhau).
 * - Tránh Stack Overflow: Không bị giới hạn bởi kích thước mảng cố định.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
    int size; // Quản lý kích thước hiện tại của Stack
} Stack;

void initStack(Stack *s)
{
    s->top = NULL;
    s->size = 0;
}

bool isEmpty(Stack *s)
{
    return (s->top == NULL);
}

// Thêm phần tử vào đỉnh Stack - O(1)
void push(Stack *s, char val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf(RED "[SYSTEM ERROR] Out of Memory!\n" RESET);
        return;
    }
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

// Lấy phần tử ra khỏi đỉnh Stack - O(1)
char pop(Stack *s)
{
    if (isEmpty(s))
        return '\0';

    Node *temp = s->top;
    char val = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return val;
}

// Xóa sạch Stack để tránh rò rỉ bộ nhớ 
void clearStack(Stack *s)
{
    while (!isEmpty(s))
    {
        pop(s);
    }
}

// Ứng dụng
bool check_packet_integrity(const char *packet)
{
    Stack s;
    initStack(&s);

    printf("[PROCESS] Dang kiem tra goi tin: %s\n", packet);

    for (int i = 0; packet[i] != '\0'; i++)
    {
        char c = packet[i];

        // Nếu gặp dấu mở -> Lưu vào Stack để chờ dấu đóng tương ứng
        if (c == '{' || c == '[' || c == '(')
        {
            push(&s, c);
        }
        // Nếu gặp dấu đóng -> So khớp với thằng vừa vào gần nhất (LIFO)
        else if (c == '}' || c == ']' || c == ')')
        {
            if (isEmpty(&s))
            {
                printf(RED "    => Loi: Thua dau dong '%c' tai vi tri %d\n" RESET, c, i);
                return false;
            }

            char last_open = pop(&s);
            if ((c == '}' && last_open != '{') ||
                (c == ']' && last_open != '[') ||
                (c == ')' && last_open != '('))
            {
                printf(RED "    => Loi: Sai cap ngoặc! Tim thay '%c' nhung cho '%c'\n" RESET, last_open, c);
                clearStack(&s);
                return false;
            }
        }
    }

    // Nếu duyệt hết chuỗi mà Stack rỗng -> Mọi dấu mở đều có dấu đóng đúng
    bool is_valid = isEmpty(&s);
    if (!is_valid)
    {
        printf(RED "    => Loi: Goi tin ket thuc bat ngo, thieu dau dong!\n" RESET);
    }

    clearStack(&s);
    return is_valid;
}

int main()
{
    // Kịch bản 1: Gói tin chuẩn từ cảm biến DHT11 (JSON format)
    const char *packet_1 = "{\"sensor\":\"DHT11\", \"data\":[25, 60]}";

    // Kịch bản 2: Gói tin bị lỗi do nhiễu đường truyền UART (Sai cặp ngoặc)
    const char *packet_2 = "{\"sensor\":\"DHT11\", \"data\":(25, 60]}";

    // Kịch bản 3: Gói tin bị mất dữ liệu cuối (Thiếu dấu đóng)
    const char *packet_3 = "{\"sensor\":\"DHT11\", \"data\":[25, 60]";

    printf(YELLOW "=== IOT GATEWAY: PACKET INTEGRITY MODULE ===\n" RESET);

    printf("\nTest 1:\n");
    if (check_packet_integrity(packet_1))
        printf(GREEN "    => GOI TIN HOP LE (Success)\n" RESET);

    printf("\nTest 2:\n");
    if (!check_packet_integrity(packet_2))
        printf(RED "    => GOI TIN BI LOI (Discarded)\n" RESET);

    printf("\nTest 3:\n");
    if (!check_packet_integrity(packet_3))
        printf(RED "    => GOI TIN BI LOI (Discarded)\n" RESET);

    printf("\n" YELLOW "============================================" RESET "\n");

    return 0;
}
