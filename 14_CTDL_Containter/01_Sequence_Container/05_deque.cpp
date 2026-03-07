/******************************************************************************
 * 2.2. std::deque (double-ended queue)
 * * - Giới thiệu:
 * + Tương tự vector nhưng được tối ưu hóa cho cả hai đầu.
 * + Dữ liệu không được lưu trữ liên tục.
 * + Khai báo: `std::deque<type> name;`
 * * - Ưu điểm:
 * + Thêm/xóa ở cả hai đầu (front và back).
 * + Truy cập ngẫu nhiên vẫn nhanh.
 * * - Nhược điểm:
 * + Chèn/xóa ở giữa vẫn tốn kém.
 * + Tốc độ truy cập có thể chậm hơn vector một chút.
 * * - Iterators:
 * + Hỗ trợ **Random Access Iterator**, tương tự vector.
 * * - Các phương thức chính:
 * + `push_front()`, `pop_front()`
 * + Các phương thức còn lại tương tự vector.
 ******************************************************************************/

#include <iostream>
#include <deque>
#include <string>

int main() {
    std::cout << "\n--- DEMO DEQUE ---" << std::endl;

    // Sử dụng đơn giản: Thêm vào hai đầu
    std::deque<std::string> messages;
    messages.push_back("End");
    messages.push_front("Start");

    std::cout << "Phan tu dau: " << messages.front() << std::endl;
    std::cout << "Phan tu cuoi: " << messages.back() << std::endl;

    // Sử dụng phức tạp: Chèn/xóa ở giữa
    auto it = messages.begin();
    std::cout << "Iterator ban dau: " << *it << std::endl;
    it++; // Di chuyển đến phần tử "End"
    messages.insert(it, "Middle"); // Chen "Middle" vao giua "Start" va "End"

    std::cout << "Deque sau khi chen: ";
    for (const auto& msg : messages) {
        std::cout << msg << " ";
    }
    std::cout << std::endl;

    // Xoa phan tu o hai dau
    messages.pop_front();
    messages.pop_back();

    std::cout << "Deque sau khi xoa hai dau: ";
    for (const auto& msg : messages) {
        std::cout << msg << " ";
    }
    std::cout << std::endl;

    return 0;
}

