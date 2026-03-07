/*******************************************************************************
 * std::queue (Adapter Container)
 * * - Giới thiệu:
 * + Hoạt động theo cơ chế "Vào trước - Ra trước" (FIFO).
 * + Là một bộ chuyển đổi (Adapter), mặc định dựa trên `std::deque`.
 * + Khai báo: `std::queue<type> name;` hoặc `std::queue<type, container> name;`
 * * - Container nền (Sequence Container):
 * + Mặc định: **std::deque**.
 * + Có thể thay thế bằng: **std::list**.
 * + Lưu ý: KHÔNG dùng được `std::vector` (vì thiếu phương thức pop_front).
 * * - Ưu điểm:
 * + Phù hợp cho các hệ thống hàng đợi, xử lý luồng dữ liệu (buffer, in ấn).
 * + Đảm bảo tính công bằng: phần tử đến trước được xử lý trước.
 * * - Nhược điểm:
 * + KHÔNG hỗ trợ truy cập ngẫu nhiên.
 * + KHÔNG hỗ trợ Iterators.
 * * - Các phương thức chính:
 * + push(value): Thêm phần tử vào cuối hàng đợi.
 * + pop(): Loại bỏ phần tử ở đầu hàng đợi.
 * + front(): Truy cập phần tử ở đầu hàng đợi.
 * + back(): Truy cập phần tử ở cuối hàng đợi.
 * + size(): Trả về số lượng phần tử hiện có.
 * + empty(): Kiểm tra hàng đợi có rỗng hay không.
 *******************************************************************************/

#include <iostream>
#include <queue>
#include <string>

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

struct SensorMsg
{
    int node_id;
    std::string type;
    float value;
};

const size_t MAX_QUEUE_SIZE = 10;

int main()
{
    std::queue<SensorMsg> msgQueue;

    std::cout << "--- C++ QUEUE MESSAGE DISPATCHER ---" << std::endl;

    // Giả lập nhận 15 tin nhắn (Vượt ngưỡng 10)
    for (int i = 1; i <= 15; ++i)
    {
        SensorMsg newMsg = {100 + i, "TEMP", 25.0f + i};

        // Phải chủ động giơi hạn size
        if (msgQueue.size() < MAX_QUEUE_SIZE)
        {
            msgQueue.push(newMsg);
            std::cout << "[RECV] Node " << newMsg.node_id << " vào hàng đợi. (Size: " << msgQueue.size() << ")" << std::endl;
        }
        else
        {
            std::cout << RED " [DROP] Node " << newMsg.node_id << " bị từ chối! (Queue Full)" RESET << std::endl;
        }
    }

    std::cout << "\n[*] Đang xử lý tin nhắn trong hàng đợi..." << std::endl;
    while (!msgQueue.empty())
    {
        SensorMsg current = msgQueue.front();
        std::cout << "  [DISPATCH] Đang gửi Node " << current.node_id << " -> Done." << std::endl;

        msgQueue.pop(); // Giải phóng Block dữ liệu cũ tự động
    }

    return 0;
}
