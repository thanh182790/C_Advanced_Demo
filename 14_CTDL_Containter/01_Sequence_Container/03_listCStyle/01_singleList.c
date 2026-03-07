/**
 * PROJECT: IOT MESH NETWORK MONITORING SYSTEM (FIRE ALARM GATEWAY)
 * -------------------------------------------------------------------------
 * BỐI CẢNH:
 * Lập trình cho một Gateway quản lý mạng lưới cảm biến khói (Mesh Network).
 * Các Node cảm biến hoạt động bằng pin và có thể gia nhập hoặc rời mạng bất kỳ lúc nào.
 * * YÊU CẦU TÍNH NĂNG:
 * * 1. QUẢN LÝ NODE GIA NHẬP (Join Network):
 * - Hàm: join_network(uint16_t id)
 * - Cấp phát bộ nhớ cho Node mới và thêm vào đầu danh sách (O(1)).
 * - Mặc định: battery = 100%, smoke_density = 0%, status = NORMAL.
 * * 2. CẬP NHẬT DỮ LIỆU CẢM BIẾN (Update Data):
 * - Hàm: update_sensor_data(uint16_t id, float smoke, float battery)
 * - Tìm Node theo ID. Nếu nồng độ khói (smoke) > 70%, tự động chuyển status sang ALARM.
 * - Cập nhật thời gian nhận tin cuối cùng (last_seen) bằng một biến đếm vòng lặp.
 * * 3. GIÁM SÁT SỨC KHỎE HỆ THỐNG (Health Monitor):
 * - Hàm: check_system_health(uint32_t current_time)
 * - Duyệt danh sách:
 *  + Nếu (current_time - last_seen > 10): Chuyển status sang OFFLINE.
 *  + Nếu battery < 20%: In cảnh báo "Low Battery" kèm ID của Node.
 * * 4. PHẢN ỨNG KHẨN CẤP (Emergency Broadcast):
 * - Hàm: trigger_fire_alarm()
 * - Duyệt danh sách, nếu phát hiện bất kỳ Node nào có status == ALARM,
 * in ra lệnh: "!!! EMERGENCY: BROADCAST SIREN TO ALL NODES !!!"
 * * 5. DỌN DẸP HỆ THỐNG (Remove Inactive Nodes):
 * - Hàm: remove_offline_nodes()
 * - Tự động xóa khỏi bộ nhớ tất cả các Node có status == OFFLINE.
 * - Đây là phần quan trọng nhất để so sánh hiệu năng giữa SLL (phải tìm prev)
 * và DLL (xóa trực tiếp).
 * * 6. HIỂN THỊ (Display):
 * - Hàm: display_network_status()
 * - In danh sách các Node kèm trạng thái màu sắc (nếu có thể) để theo dõi.
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Màu sắc Terminal mới
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define PURPLE "\x1b[35m" // Thay Blue bằng Purple/Magenta
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

typedef enum
{
    NORMAL,
    ALARM,
    OFFLINE
} NodeStatus;

typedef struct S_Node
{
    uint16_t id;
    float battery;
    float smoke_density;
    uint32_t last_seen;
    NodeStatus status;
    struct S_Node *next;
} MeshNode;

MeshNode *head = NULL;
uint16_t next_id = 100;

void join_network(uint16_t id, uint32_t current_time)
{
    MeshNode *n = (MeshNode *)malloc(sizeof(MeshNode));
    n->id = id;
    n->battery = 100.0;
    n->smoke_density = 0.0;
    n->last_seen = current_time;
    n->status = NORMAL;
    n->next = head;
    head = n;
    printf(GREEN "    [JOIN] Node %d vao mang." RESET "\n", id);
}

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

void random_join(uint32_t time)
{
    int num = rand() % 15 + 1;
    printf(CYAN "\n[*] Dang co %d node moi xin gia nhap..." RESET "\n", num);
    for (int i = 0; i < num; i++)
    {
        join_network(next_id++, time);
    }
}

void random_update(uint32_t time, int force_alarm)
{
    MeshNode *t = head;
    printf(CYAN "\n[*] Cac node dang gui tin hieu ve Gateway..." RESET "\n");
    while (t)
    {
        if (t->status != OFFLINE)
        {
            if (rand() % 100 < 80)
            { // 80% thanh cong
                float smoke = (float)(rand() % 40);
                if (force_alarm && (rand() % 100 < 30))
                    smoke = 75.0 + (rand() % 25);
                float bat_drop = (float)(rand() % 5);
                update_sensor_data(t->id, smoke, t->battery - bat_drop, time);
            }
        }
        t = t->next;
    }
}

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
        printf(RED "    => LENH: Kich hoat he thong cuu hoa toan khu vuc!\n" RESET);
}

void remove_offline_nodes()
{
    MeshNode *curr = head, *prev = NULL;
    while (curr)
    {
        if (curr->status == OFFLINE)
        {
            MeshNode *del = curr;
            if (prev == NULL)
            {
                head = curr->next;
                curr = head;
            }
            else
            {
                prev->next = curr->next;
                curr = curr->next;
            }
            printf(PURPLE "    [CLEAN] Da giai phong Node %d (OFFLINE)." RESET "\n", del->id);
            free(del);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

void display(uint32_t t)
{
    printf("\n" CYAN "╔══════════════════════════════════════════════════════╗" RESET);
    printf("\n" CYAN "║ STATUS REPORT - TIME: %-3d                            ║" RESET, t);
    printf("\n" CYAN "╠══════╦══════════╦══════════╦═════════════════════════╣" RESET);
    printf("\n" CYAN "║  ID  ║ BATTERY  ║  SMOKE   ║        STATUS           ║" RESET);
    printf("\n" CYAN "╠══════╬══════════╬══════════╬═════════════════════════╣" RESET);

    MeshNode *curr = head;
    if (!curr)
    {
        printf("\n" CYAN "║" RESET "      (Mang hien dang trong)                          " CYAN "║" RESET);
    }
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

    // T=1: Join ngau nhien
    T = 1;
    random_join(T);
    display(T);

    // T=5: Update ngau nhien
    T = 5;
    random_update(T, 0);
    check_system_health(T);
    display(T);

    // T=12: Ngau nhien canh bao
    T = 12;
    printf(RED "\n[!] CANH BAO: Phat hien bat thuong tai thoi diem T=12" RESET "\n");
    random_update(T, 1);
    check_system_health(T);
    trigger_fire_alarm();
    display(T);

    // T=15: Bao tri
    T = 15;
    printf(PURPLE "\n[*] SYSTEM MAINTENANCE..." RESET "\n");
    remove_offline_nodes();
    display(T);

    return 0;
}