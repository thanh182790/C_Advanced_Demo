/*******************************************************************************
 * std::set (Ordered Associative Container)
 * -----------------------------------------------------------------------------
 * 1. GIỚI THIỆU:
 * - Là một tập hợp lưu trữ các phần tử DUY NHẤT (Unique).
 * - Tự động sắp xếp phần tử ngay khi chèn (Mặc định: Tăng dần).
 * - Cấu trúc dữ liệu bên dưới: Red-Black Tree (Cây nhị phân cân bằng).
 *
 * 2. CƠ CHẾ HOẠT ĐỘNG:
 * - Key và Value là MỘT: Giá trị bạn truyền vào chính là khóa để sắp xếp.
 * - Set không dùng toán tử `==` để kiểm tra trùng lặp.
 * - Nó coi hai phần tử A và B là trùng nhau nếu: `!(A < B) && !(B < A)`.
 * - Quy tắc chèn (Insert):
 * + Nếu giá trị CHƯA tồn tại: Cây tạo Node mới, sắp xếp lại -> Thành công.
 * + Nếu giá trị ĐÃ tồn tại: Cây từ chối (Reject), không chèn thêm -> Thất bại.
 * - Tính chất: Phần tử trong set là Read-only (không thể sửa trực tiếp).
 *
 * 3. ĐẶC ĐIỂM KỸ THUẬT:
 * - Ưu điểm:
 * + Tìm kiếm cực nhanh: O(log N).
 * + Luôn đảm bảo dữ liệu có thứ tự (Không cần hàm sort).
 * + Tự động lọc trùng (Lý tưởng để làm danh sách chặn/cho phép).
 * - Nhược điểm:
 * + Không thể truy cập qua chỉ số [i] (Phải dùng Iterator).
 * + Tốn RAM hơn vector do cần lưu các liên kết Trái/Phải/Cha của cây.
 *
 * 4. CÁC PHƯƠNG THỨC QUAN TRỌNG:
 * - s.insert(val) : Chèn phần tử (Trả về cặp <iterator, bool>).
 * - s.erase(val)  : Xóa phần tử theo giá trị.
 * - s.find(val)   : Tìm kiếm (Trả về s.end() nếu không thấy).
 * - s.count(val)  : Trả về 1 (nếu có) hoặc 0 (nếu không).
 * - s.size()      : Số lượng phần tử thực tế hiện có.
 *
 * 5. NOTE:
 * - Chỉ nên so sánh các trường (fields) mang tính định danh (như ID, MAC Address).
 * - Các trường dữ liệu khác (như Name, Value) không nên đưa vào toán tử `<`
 *   trừ khi muốn phân biệt dựa trên cả tên.
 *******************************************************************************/
#if 0
#include <iostream>
#include <set>
#include <string>

using namespace std;

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int main()
{
    set<int> activeNodes;

    cout << YELLOW << "=== DEMO STD::SET ===" << RESET << endl;

    // 1. insert(val): Thêm phần tử
    activeNodes.insert(101);
    activeNodes.insert(105);
    activeNodes.insert(120);
    activeNodes.insert(101); // Thử thêm trùng -> Set sẽ tự động bỏ qua (Reject)

    // 2. size(): Kiểm tra số lượng phần tử hiện có
    cout << "[1] So luong Node hien tai: " << activeNodes.size() << endl;

    // 3. Duyệt Set bằng Range-based for (Dữ liệu luôn được sắp xếp tăng dần)
    cout << "[2] Danh sach Node (tu dong sap xep): ";
    for (int id : activeNodes)
    {
        cout << id << " ";
    }
    cout << endl;

    // 4. find(val): Tìm kiếm một phần tử
    int searchID = 105;
    auto it = activeNodes.find(searchID);

    if (it != activeNodes.end())
    {
        cout << GREEN << "[3] Tim thay Node " << searchID << " dang Online." << RESET << endl;
    }
    else
    {
        cout << RED << "[3] Khong tim thay Node " << searchID << RESET << endl;
    }

    // 5. count(val): Kiểm tra sự tồn tại nhanh (Trả về 1 nếu có, 0 nếu không)
    if (activeNodes.count(120))
    {
        cout << "[4] Node 120 co trong danh sach." << endl;
    }

    // 6. erase(val): Xóa một phần tử theo giá trị
    activeNodes.erase(105);
    cout << "[5] Da xoa Node 105. Kich thuoc moi: " << activeNodes.size() << endl;

    // 7. empty(): Kiểm tra set có rỗng không
    if (!activeNodes.empty())
    {
        cout << "[6] Set van con du lieu." << endl;
    }

    // 8. clear(): Xóa sạch toàn bộ phần tử
    activeNodes.clear();
    cout << "[7] Da xoa sach (Clear). Size: " << activeNodes.size() << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <set>
#include <string>
#include <iomanip>

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define BOLD "\x1b[1m"

struct NodeInfo
{
    int id;
    std::string type;
    float last_value;

    // Toán tử < để set sắp xếp và kiểm tra trùng
    bool operator<(const NodeInfo &other) const
    {
        return id < other.id;
    }
};

int main()
{
    std::set<NodeInfo> networkNodes;

    std::cout << BOLD << CYAN << "============================================" << RESET << std::endl;
    std::cout << BOLD << CYAN << "       IOT NETWORK NODE MANAGER v1.0        " << RESET << std::endl;
    std::cout << BOLD << CYAN << "============================================" << RESET << std::endl;

    // 1. Thêm các Node
    networkNodes.insert({10, "DHT11", 25.5});
    networkNodes.insert({5, "MQ135", 120.0});
    networkNodes.insert({20, "DS18B20", 30.2});
    std::cout << YELLOW << "[SYSTEM] Da nap 3 Node vao database..." << RESET << std::endl;

    // 2. Thêm trùng ID
    NodeInfo duplicateNode = {10, "UNKNOWN", 0.0};
    auto result = networkNodes.insert(duplicateNode);

    if (!result.second)
    {
        std::cout << RED << "[ERROR] Reject: Node ID " << duplicateNode.id
                  << " da ton tai! (Duplicate ID)" << RESET << std::endl;
    }

    // 3. Hiển thị danh sách dạng bảng (Dùng std::set sẽ tự sắp xếp ID 5 -> 10 -> 20)
    std::cout << "\n"
              << BOLD << "DANH SACH CAC NODE DANG HOAT DONG:" << RESET << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(15) << "Loai"
              << "Gia tri" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    for (const auto &node : networkNodes)
    {
        std::cout << std::left << std::setw(10) << node.id
                  << std::setw(15) << node.type
                  << GREEN << std::fixed << std::setprecision(1) << node.last_value << RESET << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;

    // 4. Tìm kiếm Node
    int searchTarget = 5;
    std::cout << "\n[SEARCH] Dang kiem tra Node " << searchTarget << "..." << std::endl;

    auto it = networkNodes.find({searchTarget, "", 0});

    if (it != networkNodes.end())
    {
        std::cout << GREEN << BOLD << ">>> SUCCESS: " << RESET
                  << GREEN << "Tim thay Node " << searchTarget
                  << " [Type: " << it->type << "]" << RESET << std::endl;
    }
    else
    {
        std::cout << RED << ">>> FAILED: Node " << searchTarget << " khong online." << RESET << std::endl;
    }

    std::cout << CYAN << "\n============================================" << RESET << std::endl;

    return 0;
}
#endif