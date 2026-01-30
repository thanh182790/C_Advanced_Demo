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

/* Constructor :
    -(Hàm khởi tạo):
        + Là một phương thức đặc biệt của lớp, có cùng tên với lớp.
        + Nó được gọi tự động khi một đối tượng được tạo.
        + Mục đích chính là để khởi tạo các thuộc tính của đối tượng.
        + Constructor mặc định: không có tham số.
        + Constructor có tham số: cho phép khởi tạo đối tượng với các giá trị ban đầu ngay lập tức.
*/

#if 0
#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    std::string name;
    int age;
    std::string studentID;
    int x;

public:
    /*
     * =================================================
     * STEP 1: Default constructor (user-defined)
     * =================================================
     * Được gọi khi tạo 1 đối tượng không có tham số
     */
    Student() {
        name = "Unknow";
        age = 0;
        studentID = "N/A";
        x = 0;
        cout << "[Default constructor] Student created" << endl;
    }

    /*
     * =================================================
     * STEP 2: Parameterized constructor
     * =================================================
     * khởi tạo tất cả dữ liệu của các thuộc tính
     */
    Student(const string& newName, int newAge, const string& newID)
        : name(newName), age(newAge), studentID(newID), x(0)
    {
        cout << "[Parameterized constructor] Student created" << endl;
    }

    /*
     * =================================================
     * STEP 3: Compiler-generated default constructor
     * =================================================
     * Khi mà đã tự định nghĩa bất khì hàm khởi tạo nào thì compiler sẽ
     * không tự sinh ra constructor mặc định nữa.
     * Từ khoá default để báo cho compiler hãy tạo hàm tạo mặc định cho classe này
     */
    // Student() = default;

    /*
     * =================================================
     * STEP 4: Forbid default construction
     * =================================================
     * Từ khoá delete sẽ chủ động cấm constructor mặc định.
     */
    // Student() = delete;

    void printInfo() const {
        cout << "Student { name=" << name
             << ", age=" << age
             << ", studentID=" << studentID
             << " }" << endl;
    }
};


int main()
{
    cout << "\n--- Case 1: Default constructor ---" << endl;
    Student student1; // Hàm khởi tạo mặc định
    student1.printInfo();

    cout << "\n--- Case 2: Parameterized constructor ---" << endl;
    Student student2("Nguyen Van A", 20, "SV001");
    student2.printInfo();

    return 0;
}
#endif

/* Destructor:
    - Destructor (Hàm hủy):
        + Là một phương thức đặc biệt, có tên là ~ClassName().
        + Nó được gọi tự động khi một đối tượng bị hủy (ví dụ: khi đối tượng ra khỏi phạm vi).
        + Mục đích là để giải phóng các tài nguyên mà đối tượng đã sử dụng, như bộ nhớ cấp phát động.
*/

#if 0
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;

public:
    // Constructor
    Student(const std::string& name, int age)
        : name(name), age(age) {
        std::cout << "[CTOR] Student created: " << name << std::endl;
    }

    // Default constructor
    Student() : name("Unknown"), age(0) {
        std::cout << "[CTOR] Default Student created" << std::endl;
    }

    // Destructor
    ~Student() {
        std::cout << "[DTOR] Student destroyed: " << name << std::endl;
    }
};

/* --------- Đối tượng toàn cục --------- */
Student globalStudent("Global Student", 99);

/* --------- stack --------- */
void demoStack() {
    std::cout << ">> Enter demoStack()" << std::endl;
    Student s("Stack Student", 20);
    std::cout << "<< Exit demoStack()" << std::endl;
}

/* --------- heap --------- */
void demoHeap() {
    std::cout << ">> Enter demoHeap()" << std::endl;
    Student* s = new Student("Heap Student", 21);
    std::cout << ">> About to delete heap object" << std::endl;
    delete s;   // destructor được gọi ở đây
    std::cout << "<< Exit demoHeap()" << std::endl;
}

/* --------- Đối tượng static --------- */
void demoStatic() {
    static Student staticStudent("Static Student", 30);
    std::cout << "Inside demoStatic()" << std::endl;
}

int main() {
    std::cout << "=== Program start ===" << std::endl;

    demoStack();
    std::cout << "---------------------" << std::endl;

    demoHeap();
    std::cout << "---------------------" << std::endl;

    demoStatic();
    std::cout << "Calling demoStatic() again" << std::endl;
    demoStatic();

    std::cout << "=== Program end ===" << std::endl;
    return 0;
}

#endif

