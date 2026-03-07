/******************************************************************************
 * std::list (doubly linked list)
 * * - Giới thiệu:
 * + Một danh sách liên kết đôi (doubly linked list).
 * + Các phần tử được lưu trữ tại các vùng bộ nhớ rời rạc, kết nối bằng con trỏ.
 * + Khai báo: `std::list<type> name;`
 * * - Ưu điểm:
 * + Chèn hoặc xóa phần tử ở BẤT KỲ vị trí nào đều rất nhanh (O(1)) nếu đã có iterator.
 * + Không làm thay đổi địa chỉ của các phần tử khác khi chèn/xóa (không gây reallocation).
 * + Hỗ trợ các thao tác đặc thù: `splice()`, `merge()`, `unique()`, `reverse()`.
 * * - Nhược điểm:
 * + KHÔNG hỗ trợ truy cập ngẫu nhiên (không dùng được `operator[]` hay `at()`).
 * + Tốn bộ nhớ hơn vì mỗi phần tử phải lưu thêm 2 con trỏ (next và prev).
 * + Tốc độ duyệt chậm hơn vector/deque do không tận dụng được bộ nhớ đệm (cache).
 * * - Iterators:
 * + Hỗ trợ **Bidirectional Iterator**. Chỉ có thể di chuyển `it++` hoặc `it--`.
 * + KHÔNG thể di chuyển tùy ý kiểu `it + n`.
 * * - Các phương thức chính:
 * + push_front(value) / pop_front(): Thêm/xóa ở đầu danh sách (O(1)).
 * + push_back(value) / pop_back(): Thêm/xóa ở cuối danh sách (O(1)).
 * + insert(iterator, value): Chèn vào vị trí bất kỳ với hiệu năng cực cao (O(1)).
 * + erase(iterator): Xóa phần tử tại vị trí iterator (O(1)).
 * + remove(value): Xóa tất cả các phần tử có giá trị bằng value.
 * + remove_if(predicate): Xóa các phần tử thỏa mãn điều kiện (Lambda function).
 * + sort(): Hàm sắp xếp riêng của list (do không dùng được std::sort của algorithm).
 * ******************************************************************************/
#include <iostream>
#include <list>      
#include <algorithm>
#include <string>
#include <ctime>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define PURPLE "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

enum NodeStatus
{
    NORMAL,
    ALARM,
    OFFLINE
};

struct MeshNode
{
    uint16_t id;
    float battery;
    float smoke_density;
    uint32_t last_seen;
    NodeStatus status;

    MeshNode(uint16_t _id, uint32_t _time)
        : id(_id), battery(100.0), smoke_density(0.0),
          last_seen(_time), status(NORMAL) {}
};

std::list<MeshNode> meshNetwork;
uint16_t next_id = 100;

// 1. Join Network
void join_network(uint32_t current_time)
{
    meshNetwork.emplace_front(next_id++, current_time);
    printf(GREEN "    [JOIN] Node %d gia nhap mang C++ List." RESET "\n", meshNetwork.front().id);
}

// 2. Update Data - Sử dụng Iterator để duyệt
void update_sensor_data(uint16_t id, float smoke, float battery, uint32_t current_time)
{
    for (auto &node : meshNetwork)
    {
        if (node.id == id)
        {
            node.smoke_density = smoke;
            node.battery = std::max(0.0f, std::min(100.0f, battery));
            node.last_seen = current_time;
            node.status = (smoke > 70.0) ? ALARM : (node.status == OFFLINE ? OFFLINE : NORMAL);
            return;
        }
    }
}

// 3. Health Monitor
void check_system_health(uint32_t current_time)
{
    for (auto &node : meshNetwork)
    {
        if (current_time - node.last_seen > 10)
            node.status = OFFLINE;
        if (node.battery < 20.0 && node.status != OFFLINE)
            printf(YELLOW "    [LOW BATT] Node %d: %.1f%%" RESET "\n", node.id, node.battery);
    }
}

// 4. Remove Offline Nodes
void remove_offline_nodes()
{
    // 1 dòng code để xóa toàn bộ Node thỏa mãn điều kiện
    size_t old_size = meshNetwork.size();

    meshNetwork.remove_if([](const MeshNode &n)
                          {
        if (n.status == OFFLINE) {
            printf(PURPLE "    [CLEAN] C++ xoa Node %d tu dong." RESET "\n", n.id);
            return true;
        }
        return false; });

    if (meshNetwork.size() < old_size)
    {
        printf(CYAN "    => Da giai phong %zu Node khoi bo nho." RESET "\n", old_size - meshNetwork.size());
    }
}

// 5. Display
void display(uint32_t t)
{
    printf("\n" CYAN "╔══════════════════════════════════════════════════════╗" RESET);
    printf("\n" CYAN "║ C++ LIST STATUS - TIME: %-3d                          ║" RESET, t);
    printf("\n" CYAN "╠══════╦══════════╦══════════╦═════════════════════════╣" RESET);
    printf("\n" CYAN "║  ID  ║ BATTERY  ║  SMOKE   ║        STATUS           ║" RESET);
    printf("\n" CYAN "╠══════╬══════════╬══════════╬═════════════════════════╣" RESET);

    for (const auto &n : meshNetwork)
    {
        const char *st_color = (n.status == ALARM) ? RED : (n.status == OFFLINE ? YELLOW : GREEN);
        const char *st_text = (n.status == ALARM) ? "ALARM  " : (n.status == OFFLINE ? "OFFLINE" : "OK     ");
        printf("\n" CYAN "║" RESET " %-4d " CYAN "║" RESET "  %5.1f%%  " CYAN "║" RESET "  %5.1f%%  " CYAN "║" RESET "        %s%s" RESET "        " CYAN "  ║" RESET,
               n.id, n.battery, n.smoke_density, st_color, st_text);
    }
    printf("\n" CYAN "╚══════╩══════════╩══════════╩═════════════════════════╝" RESET "\n");
}

int main()
{
    srand(time(NULL));
    uint32_t T = 0;

    T = 1;
    for (int i = 0; i < 5; i++)
        join_network(T);
    display(T);

    T = 12;
    printf(RED "\n[!] MO PHONG SU CO TAI T=12" RESET "\n");
    // Gia lap node 104 báo cháy, node 100 im lặng
    update_sensor_data(104, 88.0, 90.0, T);
    update_sensor_data(101, 10.0, 15.0, T);
    // Node 100 không được cập nhật từ T=1

    check_system_health(T);
    display(T);

    T = 15;
    printf(PURPLE "\n[*] C++ CONTAINER AUTO MAINTENANCE..." RESET "\n");
    remove_offline_nodes();
    display(T);

    return 0;
}
