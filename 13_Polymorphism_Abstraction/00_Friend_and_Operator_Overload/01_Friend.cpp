/**************************************************************
 *  Class và friends
 **************************************************************
 * - Friend function: Hàm được quyền truy cập vào private, protected member của class.
 * - Friend class: Mọi hàm thành viên của class đó đều là friend (toàn quyền truy cập).
 * - Ứng dụng: Khi cần truy cập dữ liệu riêng tư mà không muốn public getter/setter.
 * - Lưu ý:
 *  - Lạm dụng friend phá vỡ tính đóng gói (encapsulation).
 *  - Nên dùng khi thực sự cần thiết (ví dụ: operator overload, debug, I/O).
 * * Quiz:
 * 1. Khác biệt giữa friend function và public function là gì?
 * 2. Lạm dụng friend sẽ gây ra vấn đề gì?
 **************************************************************/

#if 0
// Friend function và truy cập private
#include <iostream>
class Box {
    int width;
    int height;
    friend void printBox(const Box&); // Khai báo friend function
public:
    Box(int w, int h) : width(w), height(h) {}
};

void printBox(const Box& b) {
    std::cout << "Box: " << b.width << " x " << b.height << "\n";
}

int main() {
    Box b(3, 5);
    std::cout << "Hien thi Box bằng hàm bạn: \n";
    printBox(b);
    return 0;
}
#endif

#if 0
// Friend class (class Debug có thể truy cập mọi private member của Box)
#include <iostream>
class Box;
class Debug {
public:
    void print(const Box&);
    void hack(Box&, int);
};

class Box {
    int secret = 999;
    friend class Debug;
public:
    int value = 123;
};

void Debug::print(const Box& b) {
    std::cout << "\tBox.value = " << b.value << ", secret = " << b.secret << "\n";
}

void Debug::hack(Box& b, int x) {
    b.secret = x;
}

int main() {
    Box b;
    Debug d;
    std::cout << "Debug info:\n";
    d.print(b);
    std::cout << "Infor after hacking:\n";
    d.hack(b, 111);
    d.print(b);
    return 0;
}
#endif

#if 0
// So sánh dùng friend với getter/setter (practice)
#include <iostream>
class Student {
    int score;
    friend int getScore(const Student&); // Friend function
public:
    Student(int s): score(s) {}
    int getScoreByMethod() const { return score; }
};

int getScore(const Student& s) { return s.score; }

int main() {
    Student a(9);
    std::cout << "Friend: " << getScore(a) << ", Getter: " << a.getScoreByMethod() << "\n";
    return 0;
}
#endif


