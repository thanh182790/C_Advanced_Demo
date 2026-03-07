/*******************************************************************************
 * std::priority_queue (Adapter Container)
 * * - Giới thiệu:
 * + Một dạng hàng đợi đặc biệt, nơi phần tử có "độ ưu tiên" cao nhất luôn ở đầu.
 * + Mặc định sử dụng phép so sánh `std::less`, tức là phần tử lớn nhất nằm ở đỉnh.
 * + Khai báo: `std::priority_queue<type> name;`
 * * - Container nền (Sequence Container):
 * + Mặc định: **std::vector**.
 * + Có thể thay thế bằng: **std::deque**.
 * + Lưu ý: KHÔNG dùng được `std::list` (vì cần hỗ trợ truy cập ngẫu nhiên để tạo Heap).
 * * - Ưu điểm:
 * + Tự động sắp xếp dữ liệu mỗi khi push/pop (độ phức tạp O(log N)).
 * + Cực kỳ hữu ích cho lập trình hệ thống (Lập lịch tác vụ - Task Scheduling).
 * * - Nhược điểm:
 * + Chi phí tính toán cao hơn queue thông thường do phải duy trì cấu trúc Heap.
 * + Chỉ truy cập được phần tử ở đỉnh (top), không có front() hay back().
 * * - Các phương thức chính:
 * + push(value): Thêm phần tử và tự động sắp xếp lại vị trí theo độ ưu tiên.
 * + pop(): Loại bỏ phần tử có độ ưu tiên cao nhất (ở đỉnh).
 * + top(): Truy cập phần tử ở đỉnh (phần tử lớn nhất/ưu tiên nhất).
 * + size(): Trả về số lượng phần tử.
 * + empty(): Kiểm tra hàng đợi rỗng.
 *******************************************************************************/


 #include <iostream>
#include <queue>
#include <string>
#include <vector>

// mức độ ưu tiên: Số càng nhỏ, ưu tiên càng cao
enum Priority {
    CRITICAL = 1,  // Báo cháy, rò rỉ khí gas
    WARNING  = 2,  // Pin yếu, mất kết nối node
    INFO     = 3   // Dữ liệu cảm biến định kỳ
};

struct Event {
    Priority priority;
    std::string description;

    // Cần nạp chồng toán tử < để priority_queue biết cách so sánh.
    // Lưu ý: Mặc định priority_queue lấy phần tử LỚN nhất, 
    // nên để số nhỏ (1) là ưu tiên cao
    bool operator<(const Event& other) const {
        return priority > other.priority; 
    }
};

int main() {
    // Khai báo Priority Queue
    std::priority_queue<Event> eventLog;

    std::cout << "--- IOT GATEWAY PRIORITY DISPATCHER ---" << std::endl;

    // Giả lập các sự kiện đến theo thời gian
    eventLog.push({INFO, "Nhiệt độ phòng: 25.5C"});
    eventLog.push({INFO, "Độ ẩm: 60%"});
    eventLog.push({CRITICAL, "PHÁT HIỆN KHÓI TẠI KHO A!"}); // Sự kiện này đến sau nhưng ưu tiên cao nhất
    eventLog.push({WARNING, "Node 105 sắp hết Pin"});

    std::cout << "[SYSTEM] Đang có " << eventLog.size() << " sự kiện trong hàng đợi.\n" << std::endl;

    // Xử lý sự kiện theo độ ưu tiên
    while (!eventLog.empty()) {
        Event current = eventLog.top(); // Lấy thằng ưu tiên nhất
        
        if (current.priority == CRITICAL) std::cout << "\x1b[31m";
        
        std::cout << "[PROCESSING] Level " << current.priority 
                  << ": " << current.description << "\x1b[0m" << std::endl;
        
        eventLog.pop(); // Xóa khỏi hàng đợi
    }

    return 0;
}