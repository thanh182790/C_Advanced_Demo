#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct
{
    float *data;
    int size;     // Kich thước hiện tại
    int capacity; // Dung lượng có thể lưu trữ tối đa
} AdaptiveVector;

void init_vector(AdaptiveVector *v)
{
    v->size = 0;
    v->capacity = 2;
    v->data = (float *)malloc(v->capacity * sizeof(float));
}

/* Tăng kích thước lên gấp đôi khi mà chạm ngưỡng --> tránh tình trạng relocate nhiều lần ngốn CPU
 *   Giảm kích thước đi 1/2 khi mà số lượng phần tử nhở hơn dung lượng 4 lần
 */

void resize(AdaptiveVector *v)
{
    if (v->size == v->capacity)
    {
        v->capacity *= 2;
        v->data = (float *)realloc(v->data, v->capacity * sizeof(float));
        printf(ANSI_COLOR_YELLOW "  [EXPAND]: Capacity -> %d" ANSI_COLOR_RESET "\n", v->capacity);
    }
    else if (v->size > 0 && v->size <= v->capacity / 4 && v->capacity > 2)
    {
        v->capacity /= 2;
        v->data = (float *)realloc(v->data, v->capacity * sizeof(float));
        printf(ANSI_COLOR_BLUE "  [SHRINK]: Capacity -> %d" ANSI_COLOR_RESET "\n", v->capacity);
    }
}

void push_back(AdaptiveVector *v, float value)
{
    resize(v);
    v->data[v->size++] = value;
}

void send_to_server(AdaptiveVector *v)
{
    printf(ANSI_COLOR_CYAN "\n  [SERVER] Receiving %d packets...\n" ANSI_COLOR_RESET, v->size);
    printf("  +-------+----------+\n");
    printf("  | Index |  Value   |\n");
    printf("  +-------+----------+\n");

    for (int i = 0; i < v->size; i++)
    {
        printf("  | %-5d | %8.2f |\n", i, v->data[i]);
    }
    printf("  +-------+----------+\n");
    printf(ANSI_COLOR_GREEN "  [SUCCESS] Data uploaded successfully!" ANSI_COLOR_RESET "\n");
}

void clear_vector(AdaptiveVector *v)
{
    v->size = 0;
    v->capacity = 2;
    v->data = (float *)realloc(v->data, v->capacity * sizeof(float));
    printf(ANSI_COLOR_RED "  [CLEAR]: Buffer reset to default." ANSI_COLOR_RESET "\n");
}

int main()
{
    AdaptiveVector sensorLog;
    init_vector(&sensorLog);
    srand(time(NULL));

    printf(ANSI_COLOR_CYAN "==============================================\n");
    printf("   IOT ADAPTIVE BUFFER SIMULATION SYSTEM\n");
    printf("==============================================\n" ANSI_COLOR_RESET);

    for (int lap = 1; lap <= 5; lap++)
    {
        int num_samples = rand() % 15 + 1; // demo tối đa gửi 15 dữ liệu lên server.
        printf("\n" ANSI_COLOR_GREEN "[Vong %d]: Phat hien %d du lieu moi." ANSI_COLOR_RESET "\n", lap, num_samples);

        for (int i = 0; i < num_samples; i++)
        {
            float val = 20.0 + (float)(rand() % 150) / 10.0;
            push_back(&sensorLog, val);
        }

        printf("  => Status: Size = %d | Capacity = %d\n", sensorLog.size, sensorLog.capacity);

        send_to_server(&sensorLog);

        clear_vector(&sensorLog);
        printf("----------------------------------------------\n");
    }

    free(sensorLog.data);
    printf(ANSI_COLOR_CYAN "\n=== SIMULATION TERMINATED ===\n" ANSI_COLOR_RESET);
    return 0;
}
