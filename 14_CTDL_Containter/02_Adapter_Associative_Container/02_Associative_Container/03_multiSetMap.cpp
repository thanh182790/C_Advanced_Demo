/*******************************************************************************
 * COMPARISON: MULTI-CONTAINERS VS. STANDARD CONTAINERS
 * -----------------------------------------------------------------------------
 * TIÊU CHÍ          |  std::set / std::map          | std::multiset / std::multimap
 * ------------------|-------------------------------|--------------------------
 * Tính duy nhất     |  Key là DUY NHẤT (Unique)     | Key có thể TRÙNG LẶP
 * Cơ chế Insert     |  Reject nếu Key đã tồn tại    | Luôn chấp nhận và tạo Node mới
 * Toán tử [ ]       |  chỉ có ở std::map            | KHÔNG hỗ trợ (Do key ko duy nhất)
 * Cấu trúc nền      |  Red-Black Tree               | Red-Black Tree
 *
 * 1. std::multiset:
 *     - Lưu tập hợp các giá trị có thứ tự, cho phép các giá trị giống nhau.
 *     - Ứng dụng: Lưu lịch sử điện áp pin, lịch sử nhiệt độ (25, 25, 26, 25...).
 *
 * 2. std::multimap:
 *     - Lưu cặp Key-Value, cho phép một Key ánh xạ tới nhiều Value khác nhau.
 *     - Ứng dụng: Một Node ID gửi về nhiều loại lỗi/cảnh báo khác nhau.
 *
 * * LƯU Ý VỀ BỘ NHỚ:
 *     - Do cho phép trùng lặp, số lượng Node có thể tăng rất nhanh trên Heap.
 *     - KHÔNG có toán tử truy cập nhanh `[]`, phải dùng `find` hoặc `equal_range`.
 *******************************************************************************/
/*******************************************************************************
 * CÁC HÀM QUAN TRỌNG TRONG MULTISET & MULTIMAP
 * -----------------------------------------------------------------------------
 * 1. NHÓM CHÈN VÀ XÓA (MODIFIERS):
 *     - insert(val/pair) : Chèn phần tử. Luôn thành công và không bị Reject.
 *     - erase(val)       : Xóa TẤT CẢ các phần tử có giá trị/khóa bằng 'val'.
 *     - erase(it)        : Chỉ xóa duy nhất 1 phần tử tại vị trí con trỏ 'it'.
 *     - clear()          : Xóa sạch toàn bộ container.
 *
 * 2. NHÓM TRA CỨU (LOOKUP) - CỰC KỲ QUAN TRỌNG:
 *     - count(key)       : Trả về SỐ LƯỢNG thực tế các phần tử có cùng Key.
 *                          (Trong set/map thường hàm này chỉ trả về 0 hoặc 1).
 *     - find(key)        : Trả về iterator đến phần tử ĐẦU TIÊN được tìm thấy.
 *     - equal_range(key) : Trả về một `pair` chứa 2 iterator (begin và end)
 *                          bao quanh tất cả các phần tử có cùng Key.
 *     - lower_bound(key) : Trả về iterator đến phần tử đầu tiên >= Key.
 *     - upper_bound(key) : Trả về iterator đến phần tử đầu tiên > Key.
 *
 * 3. NHÓM DUNG LƯỢNG (CAPACITY):
 *     - size()           : Tổng số lượng phần tử (bao gồm cả các phần tử trùng).
 *     - empty()          : Kiểm tra container có trống hay không.
 *
 * 4. ĐIỂM KHÁC BIỆT LỚN:
 *     - KHÔNG hỗ trợ toán tử [ ] và hàm .at(): Do một Key có nhiều Value, 
 *     trình biên dịch không biết lấy cái nào nên các hàm này bị loại bỏ.
 *******************************************************************************/
#include <iostream>
#include <set>
#include <map>
#include <string>

#define RESET   "\x1b[0m"
#define CYAN    "\x1b[36m"
#define YELLOW  "\x1b[33m"
#define MAGENTA "\x1b[35m"
#define BOLD    "\x1b[1m"

int main() {
    // --- [1] DEMO MULTISET: Lịch sử điện áp Pin (Battery History) ---
    std::multiset<float> batteryLogs;
    
    batteryLogs.insert(3.7);
    batteryLogs.insert(3.8);
    batteryLogs.insert(3.7); // Chấp nhận giá trị trùng lặp
    batteryLogs.insert(3.9);
    batteryLogs.insert(3.7);

    std::cout << BOLD << CYAN << "=== [1] MULTISET: BATTERY VOLTAGE LOGS ===" << RESET << std::endl;
    std::cout << "Lich su dien ap: ";
    for(float v : batteryLogs) std::cout << v << "V  ";
    
    std::cout << "\nSo lan muc 3.7V xuat hien: " << batteryLogs.count(3.7) << std::endl;

    // --- [2] DEMO MULTIMAP: (Error Logs) ---
    // Key: ID thiết bị (int), Message: Nội dung lỗi (string)
    std::multimap<int, std::string> errorJournal;

    errorJournal.insert({101, "Mat ket noi cam bien"});
    errorJournal.insert({105, "Pin yeu < 10%"});
    errorJournal.insert({101, "Gia tri nhiet do bat thuong"}); // ID 101 co loi thu hai
    errorJournal.insert({110, "Loi Checksum UART"});
    errorJournal.insert({101, "Nhiet do tro ve binh thuong"});
    std::cout << "\n" << BOLD << MAGENTA << "=== [2] MULTIMAP: SYSTEM ERROR JOURNAL ===" << RESET << std::endl;
    
    // Không dùng được errorJournal[101]! 
    // Phải duyệt để xem tất cả các cặp Key-Value
    for(auto const& [id, msg] : errorJournal) {
        std::cout << "Node [" << id << "] -> Error: " << msg << std::endl;
    }

    // Cách tra cứu TẤT CẢ các lỗi của một ID cụ thể (Dùng equal_range)
    int targetID = 101;
    std::cout << YELLOW << "\nTra cuu rieng cac loi cua Node " << targetID << ":" << RESET << std::endl;
    
    // equal_range trả về một cặp iterator: [bắt đầu vùng trùng, kết thúc vùng trùng)
    auto range = errorJournal.equal_range(targetID);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << "  => [RECORD]: " << it->second << std::endl;
    }

    std::cout << CYAN << "==========================================" << RESET << std::endl;

    return 0;
}
