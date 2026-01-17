/* Compile C files
   gcc -o <execution_file_name> <List_Of_C_Files> -I <Include_Path>
*/

/* Compile CPP files
   g++ -o <execution_file_name> <List_Of_CPP_Files> -I <Include_Path>
*/

/* stdio.h for C and iostream for C++
*/

#if 0

#include <iostream>

int main(void)
{
    int a;

    std::cout << "Mời bạn nhập 1 số nguyên bất kỳ: " << std::endl;
    std::cin >> a;
    std::cout << "Số bạn vừa nhập là: " << a << std::endl;
    return 0;
}   
#endif

/* Chuỗi (string)
    - Trong C: sử dụng mảng các ký tự: char str[];
    - Trong C++: có kiểu dữ liệu string.
        + Quản lý bộ nhớ tự động: Không cần phải lo lắng về việc cấp phát hoặc giải phóng bộ nhớ cho chuỗi.
          string sẽ tự động điều chỉnh kích thước khi bạn thêm hoặc xóa ký tự.

        + Nhiều hàm tiện ích: string đi kèm với nhiều hàm hữu ích như size(), length(), find(), substr(),...
          giúp thao tác với chuỗi dễ dàng hơn rất nhiều.
*/

#if 0
#include <iostream>
#include <string>

int main() {
    // Mảng char[], dùng trong C
    char str_c[] = "Viet";

    // string
    std::string str_cpp = "Dev";
    std::cout << "Kich thuoc chuoi: " << str_cpp.length() << std::endl;
    
    str_cpp += " Linux";
    std::cout << "Chuoi sau khi noi: " << str_cpp << std::endl;

    return 0;
}
#endif

/* Từ khóa auto (C++11):
    - Từ khóa auto cho phép trình biên dịch tự động suy ra kiểu dữ liệu của biến dựa trên giá trị khởi tạo của nó.
      Điều này giúp mã nguồn ngắn gọn và dễ đọc hơn, đặc biệt khi làm việc với các kiểu dữ liệu phức tạp.
    - Ví dụ:
        auto x = 10; // trình biên dịch hiểu x là int
        auto pi = 3.14; // trình biên dịch hiểu pi là double
        auto name = "Dev Linux"; // trình biên dịch hiểu name là const char*
*/

/* Hàm nạp chồng (Function Overloading)
    - Hàm nạp chồng là khả năng của C++ cho phép chúng ta định nghĩa nhiều hàm cùng tên nhưng có tham số khác nhau
      (về số lượng, kiểu dữ liệu, hoặc cả hai). Trình biên dịch sẽ tự động chọn hàm phù hợp dựa trên các tham 
      số được truyền vào khi hàm được gọi.
*/

#if 0
#include <iostream>

// Hàm nạp chồng với tham số kiểu int
int add(int a, int b) {
    return a + b;
}

// Hàm nạp chồng với tham số kiểu double
double add(double a, double b) {
    return a + b;
}

// Hàm nạp chồng với 3 tham số: 2 kiểu int, 1 float
float add(int a, int b, float c) {
    return a + b + c;
}

int main() {
    // Gọi hàm add với tham số int, trình biên dịch chọn hàm add(int, int)
    std::cout << "Tong so nguyen: " << add(5, 10) << std::endl;

    // Gọi hàm add với tham số double, trình biên dịch chọn hàm add(double, double)
    std::cout << "Tong so thuc: " << add(5.5, 10.2) << std::endl;

    // Gọi hàm add với 3 tham số, trình biên dịch chọn hàm add(int, int, float)
    std::cout << "Tong so thuc: " << add(1, 2, 5.5) << std::endl;

    return 0;
}
#endif

/* Tham chiếu (References)
    - Tham chiếu là một tên gọi khác (alias) cho một biến đã tồn tại. Một khi tham chiếu được khởi tạo, 
      nó không thể được gán lại để tham chiếu đến một biến khác.
    - So sánh với con trỏ:
        + An toàn hơn: Tham chiếu không thể là NULL (không trỏ tới gì cả), trong khi con trỏ có thể.
          Điều này giúp bạn tránh được các lỗi "dereferencing NULL pointer".
        + Cú pháp đơn giản hơn: Bạn sử dụng tham chiếu như một biến thông thường, không cần dùng các 
          toán tử * và & như khi làm việc với con trỏ.
    - Ứng dụng: Truyền tham số vào hàm bằng tham chiếu:
        + Đây là ứng dụng phổ biến nhất của tham chiếu. Khi bạn truyền một biến vào hàm bằng tham chiếu, 
          hàm sẽ làm việc trực tiếp trên biến gốc chứ không phải bản sao của nó. Điều này giúp thay đổi 
          giá trị của biến gốc từ bên trong hàm và cũng hiệu quả hơn về bộ nhớ khi truyền các đối tượng lớn.
*/

#if 0
#include <iostream>

// Truyền tham số bằng giá trị (tạo ra một bản sao)
void func_by_value(int x) {
    x = x + 10;
}

// Truyền tham số bằng tham chiếu (làm việc trên biến gốc)
void func_by_reference(int &x) {
    x = x + 10;
}

int main() {
    int a = 5;
    int b = 5;

    func_by_value(a);
    std::cout << "Gia tri cua 'a' sau khi truyen bang gia tri: " << a << std::endl; // Vẫn là 5

    func_by_reference(b);
    std::cout << "Gia tri cua 'b' sau khi truyen bang tham chieu: " << b << std::endl; // Là 15

    return 0;
}
#endif

/* Hướng đối tượng (OOP) - Trái tim của C++
    - Lập trình hướng đối tượng (OOP):
        + Lập trình hướng đối tượng là một mô hình lập trình dựa trên khái niệm "đối tượng", 
          chứa cả dữ liệu (thuộc tính) và các hàm (phương thức) để thao tác với dữ liệu đó. 
          Nó giúp mô phỏng thế giới thực vào trong code.
        + Ví dụ: chúng ta muốn tạo ra các đối tượng "Xe hơi".
            * Một đối tượng Xe hơi có các thuộc tính: màu sắc, tốc độ, hãng sản xuất.
            * Nó cũng có các phương thức: tăng tốc, phanh, bấm còi...

        + OOP dựa trên 4 trụ cột chính:
            1. Tính đóng gói (Encapsulation): Gói dữ liệu và phương thức vào trong một lớp (class) duy nhất. 
               Giống như bạn đóng gói các bộ phận của chiếc xe vào bên trong thân xe, người dùng chỉ cần biết 
               cách lái mà không cần biết động cơ hoạt động ra sao.
            2. Tính kế thừa (Inheritance): Cho phép một lớp (lớp con) kế thừa các thuộc tính và phương thức 
               từ một lớp khác (lớp cha). Ví dụ, một chiếc Xe buýt là một loại Xe hơi, nó thừa hưởng các 
               đặc điểm chung của xe hơi nhưng có thêm các đặc điểm riêng (ví dụ: số chỗ ngồi).
            3. Tính đa hình (Polymorphism): Khả năng một đối tượng có thể mang nhiều hình thái khác nhau. 
               Ví dụ, phương thức tăng tốc của một chiếc xe máy và một chiếc xe tải sẽ có cách thực hiện khác nhau.
            4. Tính trừu tượng (Abstraction): Chỉ hiển thị những thông tin cần thiết và ẩn đi những chi tiết 
               phức tạp bên trong. Người lái xe chỉ cần sử dụng bàn đạp ga và phanh, không cần biết 
               cách thức hoạt động của hệ thống nhiên liệu.
*/

/* Lớp (Class) và Đối tượng (Object):
    - Lớp (Class): Là một bản thiết kế, một khuôn mẫu để tạo ra các đối tượng. Lớp định nghĩa các thuộc tính và 
      phương thức mà một đối tượng sẽ có.
    - Đối tượng (Object): Là một thể hiện cụ thể của lớp. Ví dụ, Xe hơi là một lớp, còn chiếc xe màu đỏ mang biển 
      số 12345 là một đối tượng cụ thể của lớp đó.
    - Các chỉ định truy cập (Access Specifiers):
        + public: Các thành viên (thuộc tính/phương thức) có thể được truy cập từ bất kỳ đâu.
        + private: Các thành viên chỉ có thể được truy cập từ bên trong chính lớp đó. Đây là cách để bảo vệ dữ liệu, 
          không cho phép truy cập trực tiếp từ bên ngoài.
        + protected: Giống như private, nhưng các thành viên này có thể được truy cập bởi các lớp con kế thừa.
    - Cách đóng gói dữ liệu và phương thức:
        + Nguyên tắc chung của đóng gói là dữ liệu nên là private và các phương thức để thao tác với dữ liệu đó 
          nên là public. Điều này đảm bảo tính toàn vẹn của dữ liệu.
*/

#if 0
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    std::string studentID;
    int x;

public:
    // Phương thức gán giá trị (setter)
    void setName(std::string newName) {
        name = newName;
    }

    // Phương thức lấy giá trị (getter)
    std::string getName() {
        return name;
    }

    void setAge(int newAge) {
        if (newAge > 0) { // Đảm bảo dữ liệu hợp lệ
            age = newAge;
        }
    }

    int getAge() {
        return age;
    }
};

int main() {
    // Tạo một đối tượng (instance) của lớp Student
    Student student1;

    // Gán giá trị cho thuộc tính thông qua phương thức public
    student1.setName("Nguyen Van A");
    student1.setAge(20);

    // Lấy giá trị và in ra
    std::cout << "Ten hoc sinh: " << student1.getName() << std::endl;
    std::cout << "Tuoi hoc sinh: " << student1.getAge() << std::endl;

    return 0;
}
#endif

/* Constructor và Destructor:
    - Constructor (Hàm khởi tạo):
        + Là một phương thức đặc biệt của lớp, có cùng tên với lớp.
        + Nó được gọi tự động khi một đối tượng được tạo.
        + Mục đích chính là để khởi tạo các thuộc tính của đối tượng.
        + Constructor mặc định: không có tham số.
        + Constructor có tham số: cho phép khởi tạo đối tượng với các giá trị ban đầu ngay lập tức.
*/

#if 0
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;

public:
    // Constructor mặc định
    Student() {
        std::cout << "Da tao mot doi tuong Student." << std::endl;
        name = "Empty";
        age = 0;
    }

    // Constructor có tham số
    Student(std::string newName, int newAge) {
        name = newName;
        age = newAge;
        std::cout << "Da tao mot doi tuong Student voi ten va tuoi." << std::endl;
    }

    void displayInfo() {
        std::cout << "Ten: " << name << ", Tuoi: " << age << std::endl;
    }
};

int main() {
    Student student_a; // Gọi constructor mặc định
    student_a.displayInfo();

    Student student_b("Tran Van B", 22); // Gọi constructor có tham số
    student_b.displayInfo();

    return 0;
}
#endif

/* Constructor và Destructor:
    - Destructor (Hàm hủy):
        + Là một phương thức đặc biệt, có tên là ~ClassName().
        + Nó được gọi tự động khi một đối tượng bị hủy (ví dụ: khi đối tượng ra khỏi phạm vi).
        + Mục đích là để giải phóng các tài nguyên mà đối tượng đã sử dụng, như bộ nhớ cấp phát động.
*/

#if 0
#include <iostream>

class Destructor_Example {
public:
    // Constructor
    Destructor_Example() {
        std::cout << "Constructor da duoc goi." << std::endl;
    }

    // Destructor
    ~Destructor_Example() {
        std::cout << "Destructor da duoc goi." << std::endl;
    }
};

int main() {
    Destructor_Example obj1; // Constructor gọi ở đây

    if (true) {
        Destructor_Example obj2; // Constructor gọi ở đây
        // obj2 bị hủy ở đây (khi thoát khỏi block if), Destructor được gọi
    } 

    std::cout << "Ket thuc ham main." << std::endl;
    return 0;
} // obj1 bị hủy ở đây, Destructor được gọi
#endif

/* Tính kế thừa (Inheritance):
    - Tính kế thừa cho phép một lớp (gọi là lớp con - derived class) thừa hưởng các thuộc tính và 
      phương thức từ một lớp khác (gọi là lớp cha - base class).
    - Lợi ích:
        + Tái sử dụng mã nguồn: Bạn không cần phải viết lại các đoạn mã đã có ở lớp cha.
        + Mở rộng tính năng: Lớp con có thể có thêm các thuộc tính và phương thức riêng của nó.
        + Tạo ra cấu trúc phân cấp: Giúp quản lý các đối tượng có liên quan một cách logic.
    - Cú pháp:
        class ChildClass : accessSpecifier ParentClass {
            // ...
        };
*/

#if 0
#include <iostream>
#include <string>

// Lớp cha (Base Class)
class Person {
protected: // Dùng protected để lớp con có thể truy cập được
    std::string name;
    int age;

public:
    void setInfo(std::string n, int a) {
        name = n;
        age = a;
    }

    void display() {
        std::cout << "Ten: " << name << ", Tuoi: " << age << std::endl;
    }
};

// Lớp con (Derived Class) kế thừa từ Person
class Student : public Person {
private:
    std::string studentID;

public:
    void setID(std::string id) {
        studentID = id;
    }

    void displayStudentInfo() {
        // Có thể truy cập trực tiếp 'name' và 'age' vì chúng là protected ở lớp cha
        display(); 
        std::cout << "MSSV: " << studentID << std::endl;
    }
};

int main() {
    Student s1;
    s1.setInfo("Nguyen Van A", 20); // Dùng phương thức của lớp cha
    s1.setID("SV12345");           // Dùng phương thức của lớp con
    
    s1.displayStudentInfo();

    return 0;
}
#endif

