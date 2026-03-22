/*******************************************************************************
 * COMPARISON: UNORDERED CONTAINERS VS. ORDERED CONTAINERS
 * -----------------------------------------------------------------------------
 * TIÊU CHÍ          |  std::set / std::map          | std::unordered_set / map
 * ------------------|-------------------------------|--------------------------
 * Cấu trúc nền      |  Red-Black Tree (Cây)         | Hash Table (Bảng băm)
 * Thứ tự phần tử    |  Luôn sắp xếp (Ordered)       | Không thứ tự (Unordered)
 * Tốc độ tìm kiếm   |  O(log N)                     | O(1) - Trung bình lý tưởng
 * Khả năng tra cứu  |  Chậm hơn nhưng ổn định       | Cực nhanh cho tập dữ liệu lớn
 * Yêu cầu bộ nhớ    |  Thấp hơn                     | Cao hơn (do cần các Bucket)
 *
 * 1. CƠ CHẾ BẢNG BĂM (HASH TABLE):
 * - Hash Function: Biến Key thành một con số (Index) để tìm vị trí lưu trữ.
 * - Buckets (Ô chứa): Dữ liệu được chia vào các ô. Key có mã băm giống nhau
 * sẽ rơi vào cùng một Bucket (Collision - Xung đột).
 * - Load Factor: Tỉ lệ giữa số phần tử / số lượng Bucket.
 *
 * 2. ỨNG DỤNG TRONG NHÚNG:
 * - Dùng Unordered khi cần tra cứu địa chỉ MAC hoặc ID cực nhanh mà không
 * quan tâm đến việc danh sách có được sắp xếp hay không.
 *******************************************************************************/

/*******************************************************************************
 * CÁC HÀM CỐT LÕI CỦA UNORDERED_SET & UNORDERED_MAP
 * -----------------------------------------------------------------------------
 * 1. NHÓM ĐẶC THÙ BẢNG BĂM (HASH INFO):
 *     - bucket_count()  : Trả về số lượng ô chứa (Buckets) hiện có.
 *     - bucket(key)     : Trả về chỉ số của Bucket mà Key đang nằm trong đó.
 *     - load_factor()   : Trả về hệ số tải hiện tại (Size / Bucket_count).
 *     - rehash(n)       : Thiết lập lại số lượng Bucket (Tối thiểu n).
 *
 * 2. NHÓM THAO TÁC (TƯƠNG TỰ MAP/SET NHƯNG TỐC ĐỘ O(1)):
 *     - insert(), erase(), find(), count()
 *     - Toán tử [ ]     : Chỉ có ở unordered_map (Truy cập/Ghi đè giá trị).
 *
 * * LƯU Ý: Không dùng được các hàm liên quan đến thứ tự như lower_bound,
 * upper_bound vì dữ liệu trong bảng băm nằm lộn xộn.
 *******************************************************************************/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define BOLD "\x1b[1m"

struct DeviceInfo
{
    std::string model;
    int firmware_v;
};

void printActiveNodes(const std::unordered_map<int, DeviceInfo> &sessions)
{
    std::cout << YELLOW << "\n--- CURRENT ACTIVE SESSIONS ---" << RESET << std::endl;
    std::cout << std::left << std::setw(10) << "Node ID" << " | " << "Firmware Version" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    for (const auto &[id, info] : sessions)
    {
        std::cout << std::left << std::setw(10) << id << " | " << info.model << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}

template <typename T>
void analyzeHashTable(const T &container, std::string label)
{
    std::cout << CYAN << "\n=== [ANALYSIS] " << label << " ===" << RESET << std::endl;
    std::cout << "Phan tu hien co : " << container.size() << std::endl;
    std::cout << "So luong Bucket : " << container.bucket_count() << std::endl;
    std::cout << "He so tai (LF)  : " << std::fixed << std::setprecision(2) << container.load_factor() << std::endl;
    std::cout << "Max Load Factor : " << container.max_load_factor() << std::endl;

    int collisions = 0;
    for (size_t i = 0; i < container.bucket_count(); ++i)
    {
        size_t b_size = container.bucket_size(i);
        if (b_size > 1)
        {
            collisions++;
            // chi tiết từng bucket bị xung đột
            std::cout << "  - Bucket [" << i << "] dang bi xung dot (" << b_size << " phan tu)\n";
        }
    }
    std::cout << YELLOW << "So luong bucket bi xung dot: " << collisions << RESET << std::endl;
}

int main()
{
    std::unordered_set<int> whiteList;
    std::unordered_map<int, DeviceInfo> activeSessions;

    // --- GIAI ĐOẠN 1: KHỞI TẠO 10 NODES ---
    for (int i = 100; i < 110; ++i)
    {
        whiteList.insert(i);
        activeSessions[i] = {"v1.0." + std::to_string(i), i % 5};
    }

    std::cout << BOLD << "=== KHOI TAO GATEWAY: 50 NODES ===" << RESET << std::endl;

    // 1. In danh sách dữ liệu thực tế sau khi khởi tạo
    printActiveNodes(activeSessions);

    // 2. Phân tích cấu trúc bảng băm
    analyzeHashTable(whiteList, "WHITE-LIST (SET)");
    analyzeHashTable(activeSessions, "SESSION (MAP)");

    // --- GIAI ĐOẠN 2: ÉP HỆ THỐNG PHẢI REHASH ---
    std::cout << RED << "\n[ACTION] Dang nap them 100 phan tu de kich hoat REHASH..." << RESET << std::endl;
    for (int i = 200; i < 300; ++i)
    {
        whiteList.insert(i);
    }

    // Xem kết quả sau khi Rehash (Số lượng Bucket sẽ tăng vọt)
    analyzeHashTable(whiteList, "WHITE-LIST (AFTER REHASH)");

    // --- GIAI ĐOẠN 3: TRA CỨU NHANH O(1) ---
    int testID = 125;
    std::cout << "\n[TEST] Tra cuu Node ID " << testID << ": ";
    if (whiteList.count(testID))
    {
        std::cout << GREEN << "Hop le! Firmware: " << activeSessions[testID].model << RESET << std::endl;
    }

    // --- GIAI ĐOẠN 4: SOI VỊ TRÍ TRONG RAM ---
    std::cout << "\n[INFO] Chi tiet vi tri luu tru trong RAM (Bucket Index):" << std::endl;
    std::vector<int> sample = {100, 125, 149};
    for (int id : sample)
    {
        std::cout << " - ID " << id << " nam o Bucket so: " << whiteList.bucket(id) << std::endl;
    }

    return 0;
}