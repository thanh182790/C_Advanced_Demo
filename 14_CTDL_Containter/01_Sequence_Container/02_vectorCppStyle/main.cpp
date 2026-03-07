/******************************************************************************
 * std::vector
 * * - Giới thiệu:
 * + Một mảng động có kích thước linh hoạt.
 * + Dữ liệu được lưu trữ trong một vùng bộ nhớ liên tục.
 * + Khai báo: `std::vector<type> name;`
 * * - Ưu điểm:
 * + Truy cập ngẫu nhiên cực nhanh (Random Access).
 * + Thêm vào cuối (push_back) hiệu quả trung bình.
 * * - Nhược điểm:
 * + Chèn/xóa ở giữa hoặc đầu rất tốn kém vì phải di chuyển tất cả các phần tử phía sau.
 * * - Iterators:
 * + Hỗ trợ **Random Access Iterator**. Có thể di chuyển tùy ý: `it + n`, `it - n`.
 * * - Các phương thức chính:
 * + push_back(value): Thêm một phần tử vào cuối vector.
 * + pop_back(): Xóa phần tử cuối cùng của vector.
 * + at(i): Truy cập phần tử tại vị trí i. Phương thức này kiểm tra chỉ số hợp lệ và ném ra ngoại lệ
 * std::out_of_range nếu chỉ số không hợp lệ.
 * + operator[]: Truy cập phần tử tại vị trí i. Nhanh hơn at() nhưng không kiểm tra chỉ số,
 * có thể gây lỗi undefined behavior.
 * + front(): Truy cập phần tử đầu tiên.
 * + back(): Truy cập phần tử cuối cùng.
 * + insert(iterator, value): Chèn value vào vị trí được chỉ định bởi iterator.
 * + erase(iterator): Xóa phần tử tại vị trí iterator.
 * + size(): Trả về số lượng phần tử hiện có trong vector.
 * + empty(): Kiểm tra xem vector có rỗng không (trả về true nếu rỗng, false nếu không).
 * ******************************************************************************/
#include <iostream>
#include <vector>
#include <iomanip>   
#include <ctime>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

using namespace std;

void sendToServer(const vector<float>& logs) {
    cout << CYAN << "\n  [SERVER] Receiving " << logs.size() << " packets..." << RESET << endl;
    cout << "  +-------+----------+" << endl;
    cout << "  | Index |  Value   |" << endl;
    cout << "  +-------+----------+" << endl;

    for (size_t i = 0; i < logs.size(); ++i) {
        cout << "  | " << left << setw(5) << i 
             << " | " << right << setw(8) << fixed << setprecision(2) << logs[i] << " |" << endl;
    }
    cout << "  +-------+----------+" << endl;
    cout << GREEN << "  [SUCCESS] Data uploaded successfully!" << RESET << endl;
}

int main() {
    vector<float> sensorLog; 
    srand(time(0));

    cout << CYAN << "==============================================" << endl;
    cout << "   CPP STL VECTOR IOT SIMULATION" << endl;
    cout << "==============================================" << RESET << endl;

    for (int lap = 1; lap <= 5; ++lap) {
        int num_samples = rand() % 15 + 1;
        cout << "\n" << GREEN << "[Vong " << lap << "]: Phat hien " << num_samples << " du lieu moi." << RESET << endl;

        for (int i = 0; i < num_samples; ++i) {
            float val = 20.0f + static_cast<float>(rand() % 150) / 10.0f;
            
            //THÊM PHẦN TỬ: Tự động resize, tự động quản lý capacity
            sensorLog.push_back(val);
        }

        // Kiểm tra trạng thái bộ nhớ của Vector
        cout << "  => Status: Size = " << sensorLog.size() 
             << " | Capacity = " << sensorLog.capacity() << endl;

        sendToServer(sensorLog);

        // XÓA DỮ LIỆU: Chuẩn bị cho chu kỳ sau
        sensorLog.clear();
        
        // C++ Vector mặc định không giảm capacity sau khi clear() để tối ưu tốc độ.
        // Nếu muốn tiết kiệm RAM tuyệt đối trong hệ thống nhúng:
        sensorLog.shrink_to_fit(); 
        
        cout << RED << "  [CLEAR]: Buffer reset and memory shrunk." << RESET << endl;
        cout << "----------------------------------------------" << endl;
    }

    // GIẢI PHÓNG: Không cần free(), vector tự hủy khi kết thúc hàm main
    return 0;
}
