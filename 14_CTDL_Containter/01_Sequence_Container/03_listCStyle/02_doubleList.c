#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Màu sắc Terminal
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define PURPLE "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

typedef enum
{
    NORMAL,
    ALARM,
    OFFLINE
} NodeStatus;

typedef struct D_Node
{
    uint16_t id;
    float battery;
    float smoke_density;
    uint32_t last_seen;
    NodeStatus status;
    struct D_Node *next;
    struct D_Node *prev;
} MeshNode;

MeshNode *head = NULL;
uint16_t next_id = 100;

// 1. Join Network (Thêm vào đầu - O(1))
void join_network(uint16_t id, uint32_t current_time)
{
    MeshNode *n = (MeshNode *)malloc(sizeof(MeshNode));
    n->id = id;
    n->battery = 100.0;
    n->smoke_density = 0.0;
    n->last_seen = current_time;
    n->status = NORMAL;

    n->next = head;
    n->prev = NULL; // Node mới là đầu, nên không có prev

    if (head != NULL)
    {
        head->prev = n; // Node cũ trỏ ngược lại node mới
    }
    head = n;

    printf(GREEN "    [JOIN] Node %d gia nhap (Double Linked)." RESET "\n", id);
}

// 2. Update Sensor Data (Tìm kiếm)
void update_sensor_data(uint16_t id, float smoke, float battery, uint32_t current_time)
{
    MeshNode *t = head;
    while (t)
    {
        if (t->id == id)
        {
            t->smoke_density = smoke;
            t->battery = (battery < 0) ? 0 : (battery > 100 ? 100 : battery);
            t->last_seen = current_time;
            if (smoke > 70.0)
                t->status = ALARM;
            else if (t->status != OFFLINE)
                t->status = NORMAL;
            return;
        }
        t = t->next;
    }
}

// 3. Health Check
void check_system_health(uint32_t current_time)
{
    MeshNode *t = head;
    while (t)
    {
        if (current_time - t->last_seen > 10)
            t->status = OFFLINE;
        if (t->battery < 20.0 && t->status != OFFLINE)
            printf(YELLOW "    [LOW BATT] Node %d: %.1f%%" RESET "\n", t->id, t->battery);
        t = t->next;
    }
}

// 4. Fire Alarm
void trigger_fire_alarm()
{
    MeshNode *t = head;
    int alarm = 0;
    while (t)
    {
        if (t->status == ALARM)
        {
            printf(RED "    [!!!] CHAY TAI NODE %d (Khoi: %.1f%%)" RESET "\n", t->id, t->smoke_density);
            alarm = 1;
        }
        t = t->next;
    }
    if (alarm)
        printf(RED "    => LENH: Kich hoat he thong cuu hoa khan cap!\n" RESET);
}

// 5. Remove Offline Nodes (ƯU ĐIỂM CỦA DOUBLE LINKED LIST)
void remove_offline_nodes()
{
    MeshNode *curr = head;
    while (curr)
    {
        MeshNode *next_node = curr->next; // Lưu lại node tiếp theo trước khi xóa

        if (curr->status == OFFLINE)
        {
            printf(PURPLE "    [CLEAN] Dang giai phong Node %d (DLL logic)." RESET "\n", curr->id);

            // TỰ NỐI DÂY: Không cần dùng biến 'prev' chạy song song
            if (curr->prev != NULL)
            {
                curr->prev->next = curr->next;
            }
            else
            {
                head = curr->next; // Nếu là node đầu
            }

            if (curr->next != NULL)
            {
                curr->next->prev = curr->prev;
            }

            free(curr);
        }
        curr = next_node;
    }
}

void random_join(uint32_t time)
{
    int num = rand() % 5 + 1;
    printf(CYAN "\n[*] Mo phong %d node moi gia nhap..." RESET "\n", num);
    for (int i = 0; i < num; i++)
        join_network(next_id++, time);
}

void random_update(uint32_t time, int force_alarm)
{
    MeshNode *t = head;
    printf(CYAN "\n[*] Cac node gui tin hieu Heartbeat..." RESET "\n");
    while (t)
    {
        if (t->status != OFFLINE && (rand() % 100 < 80))
        {
            float smoke = (float)(rand() % 40);
            if (force_alarm && (rand() % 100 < 30))
                smoke = 75.0 + (rand() % 25);
            update_sensor_data(t->id, smoke, t->battery - (float)(rand() % 5), time);
        }
        t = t->next;
    }
}

void display(uint32_t t)
{
    printf("\n" CYAN "╔══════════════════════════════════════════════════════╗" RESET);
    printf("\n" CYAN "║ DLL STATUS REPORT - TIME: %-3d                        ║" RESET, t);
    printf("\n" CYAN "╠══════╦══════════╦══════════╦═════════════════════════╣" RESET);
    printf("\n" CYAN "║  ID  ║ BATTERY  ║  SMOKE   ║        STATUS           ║" RESET);
    printf("\n" CYAN "╠══════╬══════════╬══════════╬═════════════════════════╣" RESET);

    MeshNode *curr = head;
    if (!curr)
        printf("\n" CYAN "║" RESET "      (Mang hien dang trong)                          " CYAN "║" RESET);
    while (curr)
    {
        char *st_color = (curr->status == ALARM) ? RED : (curr->status == OFFLINE ? YELLOW : GREEN);
        char *st_text = (curr->status == ALARM) ? "ALARM  " : (curr->status == OFFLINE ? "OFFLINE" : "OK     ");
        printf("\n" CYAN "║" RESET " %-4d " CYAN "║" RESET "  %5.1f%%  " CYAN "║" RESET "  %5.1f%%  " CYAN "║" RESET "        %s%s" RESET "        " CYAN "  ║" RESET,
               curr->id, curr->battery, curr->smoke_density, st_color, st_text);
        curr = curr->next;
    }
    printf("\n" CYAN "╚══════╩══════════╩══════════╩═════════════════════════╝" RESET "\n");
}

int main()
{
    srand(time(NULL));
    uint32_t T = 0;

    T = 1;
    random_join(T);
    display(T);

    T = 5;
    random_update(T, 0);
    check_system_health(T);
    display(T);

    T = 12;
    printf(RED "\n[!] CANH BAO: Phat hien rui ro tai T=12" RESET "\n");
    random_update(T, 1);
    check_system_health(T);
    trigger_fire_alarm();
    display(T);

    T = 15;
    printf(PURPLE "\n[*] SYSTEM MAINTENANCE (DLL Mode)..." RESET "\n");
    remove_offline_nodes();
    display(T);

    return 0;
}
