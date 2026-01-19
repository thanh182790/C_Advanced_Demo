/* Constructor :
    -(Hàm khởi tạo sao chép ):
        + Là hàm khởi tạo đặc biệt dùng để tạo một đối tượng mới từ một đối tượng đã tồn tại cùng lớp.
        + ClassName(const ClassName& other);
        + Copy constructor được gọi tự động khi 
            - Khởi tạo object từ object khác
            - Truyền object vào hàm bằng giá trị (pass-by-value)
            - Trả về object từ hàm bằng giá trị (return-by-value)
        + Nếu KHÔNG tự viết, compiler sẽ sinh ra copy constructor mặc định: ---> shallow Copy
            - Copy từng biến thành viên (member-wise copy)
            - Với kiểu cơ bản (int, double, bool…) → an toàn
            - Với con trỏ → chỉ copy địa chỉ
            ----> KHÔNG ĐƯỢC dùng copy constructor mặc định cho class có con trỏ quản lý tài nguyên
        + Hàm khởi tạo sao chép sâu là hàm mà người dùng tự định nghĩa để quản lý tài nguyên hợp lí
            - Tự cấp phát vùng nhớ
            - sao chép nội dùng thay vì địa chỉ
*/

/* Demo hàm khởi tạo sao chép mặc định */
#if 0
#include <iostream>
#include <cstring>

class Student {
private:
    char* name;      // heap memory
    int age;

public:
    // Constructor có tham số
    Student(const char* n, int a) : age(a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        std::cout << "Constructor called for " << name << std::endl;
    }

    // Destructor
    ~Student() {
        std::cout << "Destructor called for " 
                  << (name ? name : "null") << std::endl;
        delete[] name;
    }

    void print() const {
        std::cout << "Name: " << name 
                  << ", Age: " << age
                  << ", name addr: " << static_cast<void*>(name)
                  << std::endl;
    }
};

int main() {
    Student s1("Nguyen Van A", 20);
    Student s2 = s1;   // COPY CONSTRUCTOR (mặc định)

    s1.print();
    std::cout << "Thong tin cua studen s2 la\n";
    s2.print();

    return 0;
}

#endif


/* Dmeo hàm khởi tạo sao chép sâu */
#if 0 
#include <iostream>
#include <cstring>

class Student {
private:
    char* name;
    int age;

public:
    // Constructor
    Student(const char* n, int a) : age(a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        std::cout << "Constructor called for " << name << std::endl;
    }

    // COPY CONSTRUCTOR (Deep Copy)
    Student(const Student& other) : age(other.age) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        std::cout << "Copy constructor called for " <<this->name << std::endl;
    }

    // Destructor
    ~Student() {
        std::cout << "Destructor called for "
                  << (name ? name : "null") << std::endl;
        delete[] name;
    }

    void print() const {
        std::cout << "Name: " << name
                  << ", Age: " << age
                  << ", name addr: " << static_cast<void*>(name)
                  << std::endl;
    }
};

int main() {
    Student s1("Nguyen Van A", 20);
    Student s2 = s1;   // Deep copy

    s1.print();
    s2.print();

    return 0;
}
#endif
