/*******************************************************************************
 * std::map (Ordered Associative Container)
 * -----------------------------------------------------------------------------
 * 1. GIỚI THIỆU:
 * - Lưu trữ dữ liệu theo cặp Khóa - Giá trị (Key - Value).
 * - Key là duy nhất (Unique), Value có thể trùng nhau.
 * - Tự động sắp xếp phần tử dựa trên Key (Mặc định: Tăng dần).
 *
 * 2. CƠ CHẾ:
 * - Cấu trúc: Red-Black Tree (Cây nhị phân cân bằng).
 * - Mỗi Node là một `std::pair<const Key, Value>`.
 * - Truy cập phần tử qua toán tử `[]` hoặc hàm `.at()`.
 *
 * 3. ĐẶC ĐIỂM TRONG NHÚNG:
 * - Ưu điểm:
 * + Tìm kiếm, thêm, xóa cực nhanh: O(log N).
 * + Quản lý Profile thiết bị rất trực quan (ID -> Info).
 * - Nhược điểm:
 * + Tốn bộ nhớ hơn `std::set` vì phải lưu thêm vùng cho Value.
 * + Phân mảnh bộ nhớ (Fragmentation) nếu insert/erase liên tục trên Heap.
 *
 * 4. CÁC HÀM HAY DÙNG:
 * - m[key] = val  : Thêm hoặc Cập nhật giá trị.
 * - m.erase(key)  : Xóa phần tử theo Key.
 * - m.find(key)   : Tìm Key (Trả về iterator).
 * - m.count(key)  : Kiểm tra Key có tồn tại không (0 hoặc 1).
 *******************************************************************************/

#include <iostream>
#include <map>
#include <string>

#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

int main()
{
    std::map<int, std::string> deviceStatus;

    // 1. Thêm dữ liệu (Hoặc cập nhật)
    deviceStatus[102] = "Offline";
    deviceStatus[105] = "Low Battery";
    deviceStatus[101] = "Online";

    // 2. Cập nhật dữ liệu cực dễ dàng
    deviceStatus[102] = "Online"; // Ghi đè trạng thái mới cho Node 102
    std::cout << CYAN << "--- DASHBOARD QUAN LY THIET BI ---" << RESET << std::endl;

    // 3. Duyệt Map (theo thứ tự ID: 101 -> 102 -> 105)
    for (auto const &[id, status] : deviceStatus)
    {
        std::cout << "Node ID [" << id << "] -> Status: " << GREEN << status << RESET << std::endl;
    }

    // 4. Kiểm tra một Node cụ thể
    int checkID = 110;
    if (deviceStatus.find(checkID) == deviceStatus.end())
    {
        std::cout << "\n[INFO] Node " << checkID << " chua tung ket noi." << std::endl;
    }

    return 0;
}