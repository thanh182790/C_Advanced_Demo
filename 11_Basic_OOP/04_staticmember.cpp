/**
 * 2. Static member (Biến/Hàm tĩnh của lớp)
 * ---------------------------------------
 * - Static member variable: Thuộc về class, không thuộc về từng object.
 * Mọi object cùng dùng một biến static duy nhất.
 * - Static member function: Chỉ truy cập được static member, không truy cập non-static.
 * - Ứng dụng:
 *      - Đếm số object được tạo.
 *      - Chia sẻ tài nguyên giữa các object.
 *      - Singleton pattern.
 * - Lưu ý:
 *      - Phải khai báo (định nghĩa) static variable bên ngoài class.
 *      - Static member vẫn tuân thủ access modifier (private, public).
 * * Quiz:
 * 1. Static member có thể truy cập non-static member không? (Trả lời: Không)
 * 2. Static member tồn tại bao lâu trong chương trình? (Trả lời: Suốt thời gian chạy chương trình)
 */

#include <iostream>
#include <string>

class Counter {
private:
    static int count;      // Static member (Biến tĩnh)
    std::string name;      // Non-static member (Biến thông thường - mỗi object một tên khác nhau)

public:
    Counter(std::string n) : name(n) { 
        ++count; 
    }

    ~Counter() { 
        --count; 
    }

    // Static function: CHỈ truy cập được thành viên static
    static int getCount() { 
        return count; // Hợp lệ vì count là static
    }

    // Static function gây lỗi nếu truy cập non-static member
    static void demoStaticFunction() {
        std::cout << "Current count: " << count << "\n"; // ok
        
        // Error
        // std::cout << "Object name: " << name << "\n"; 
        
        /*
           - Hàm static thuộc về Class, nó không biết mình đang được gọi cho Object nào.
           - Biến 'name' thuộc về từng Object cụ thể (a, b, c).
           - Vì không có con trỏ 'this', hàm static không biết lấy 'name' của ai để in ra.
        */
    }

    // 3. Non-static function: Truy cập được CẢ HAI
    void displayInfo() {
        std::cout << "Object [" << name << "] says current total is: " << count << "\n";
    }
};

int Counter::count = 0;

int main() {
    Counter a("Object_A"), b("Object_B");

    // Gọi hàm static thông qua tên lớp
    std::cout << "Total count: " << Counter::getCount() << "\n";
    Counter::demoStaticFunction();

    // Gọi hàm non-static thông qua object
    a.displayInfo();
    b.displayInfo();

    return 0;
}