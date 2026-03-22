/******************************************************************************
 * TRIỂN KHAI QUEUE DÙNG LINKED LIST
 * ----------------------------------------------------------------------------
 * 1. CHỨC NĂNG:
 * - Khởi tạo Queue (Init).
 * - Thêm gói tin vào cuối hàng đợi (Enqueue).
 * - Lấy gói tin ở đầu hàng đợi ra xử lý (Dequeue).
 * - Kiểm tra trạng thái hàng đợi (IsEmpty, IsFull).
 * - Quản lý bộ nhớ động cho từng Message.
 * * 2. BÀI TOÁN THỰC TẾ: "MESSAGE DISPATCHER FOR IOT GATEWAY"
 * - Gateway nhận dữ liệu từ nhiều Node cảm biến khác nhau.
 * - Các tin nhắn được xếp hàng theo thứ tự thời gian (FIFO).
 * - Main Loop của Gateway sẽ lấy từng tin nhắn ra để gửi lên Server Cloud.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

#define MAX_QUEUE_SIZE 10 

typedef struct
{
    int node_id;
    char type[10]; // "TEMP", "HUMI", "SMOKE", "PIR"
    float value;
    uint32_t timestamp;
} Message;

typedef struct QNode
{
    Message msg;
    struct QNode *next;
} QNode;

typedef struct
{
    QNode *front, *rear;
    int count;
} GatewayQueue;

void initQueue(GatewayQueue *q)
{
    q->front = q->rear = NULL;
    q->count = 0;
}

bool enqueue(GatewayQueue *q, Message data)
{
    if (q->count >= MAX_QUEUE_SIZE)
    {
        printf(RED "    [DROP] Hàng đợi đầy! Bỏ qua tin nhắn từ Node %d\n" RESET, data.node_id);
        return false;
    }

    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    if (!newNode)
        return false;

    newNode->msg = data;
    newNode->next = NULL;

    if (q->rear == NULL) //Queue rỗng
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
    return true;
}

bool dequeue(GatewayQueue *q, Message *outData)
{
    if (q->front == NULL)
        return false;

    QNode *temp = q->front;
    *outData = temp->msg;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    q->count--;
    return true;
}

int main()
{
    srand(time(NULL));
    GatewayQueue myGW;
    initQueue(&myGW);

    printf(CYAN "====================================================\n" RESET);
    printf(CYAN "        IOT GATEWAY BURST DATA SIMULATION           \n" RESET);
    printf(CYAN "====================================================\n" RESET);

    // GIAI ĐOẠN 1: Dữ liệu đổ về dồn dập (Burst Load)
    printf(YELLOW "\n[*] GIAI ĐOẠN 1: Nhận dữ liệu từ 15 Node cảm biến...\n" RESET);
    char *types[] = {"TEMP", "HUMI", "SMOKE", "PIR"};

    for (int i = 1; i <= 15; i++)
    {
        Message newMsg;
        newMsg.node_id = 100 + i;
        strcpy(newMsg.type, types[rand() % 4]);
        newMsg.value = (float)(rand() % 100);
        newMsg.timestamp = (uint32_t)time(NULL);

        if (enqueue(&myGW, newMsg))
        {
            printf("    [RECV] Node %d [%s] -> Queue (Size: %d)\n",
                   newMsg.node_id, newMsg.type, myGW.count);
        }
    }

    // GIAI ĐOẠN 2: Kiểm tra trạng thái hàng đợi
    printf(YELLOW "\n[*] GIAI ĐOẠN 2: Kiểm tra Backlog...\n" RESET);
    printf("    Hiện có %d tin nhắn đang chờ xử lý trong bộ đệm RAM.\n", myGW.count);

    // GIAI ĐOẠN 3: Xử lý theo thứ tự FIFO
    printf(YELLOW "\n[*] GIAI ĐOẠN 3: Main Loop bắt đầu xử lý tin nhắn (Dispatch)...\n" RESET);
    Message processMsg;
    int processed = 0;

    while (dequeue(&myGW, &processMsg))
    {
        processed++;
        printf(GREEN "    [DISPATCH %d] Đang gửi Node %d [%s: %.2f] lên Cloud... OK\n" RESET,
               processed, processMsg.node_id, processMsg.type, processMsg.value);

        // Giả lập xử lý tốn thời gian
        if (processed % 3 == 0)
            printf("    ...Đang chờ xác nhận từ Server (ACK)...\n");
    }

    printf(CYAN "\n====================================================\n" RESET);
    printf("Hoàn tất! Tổng cộng đã xử lý %d tin nhắn thành công.\n", processed);
    printf(CYAN "====================================================\n" RESET);

    return 0;
}