/*
I. Chính sách sao chép tài nguyên (Resource Copy Policy)
-------------------------------------------------------
1. Shallow Copy (Sao chép nông)
   - Copy địa chỉ con trỏ, không copy dữ liệu bên trong (dễ gây double-free).
   - Mặc định copy constructor là shallow copy.

2. Deep Copy (Sao chép sâu)
   - Tạo vùng nhớ mới, copy dữ liệu sang vùng nhớ mới.
   - Tránh các lỗi về bộ nhớ.

3. Move Semantics (Di chuyển tài nguyên)
   - Thay vì copy, chuyển ownership sang đối tượng khác (rất hiệu quả với tài nguyên lớn).
   - Dùng với std::move, move constructor.

-------------------------------------------------------
Demo: Shallow Copy vs Deep Copy
-------------------------------------------------------
*/

#if 0
#include <iostream>

class Shallow
{
public:
    int *data;
    Shallow(int val) { data = new int(val); }
    ~Shallow() { delete data;}
};

class Deep
{
public:
    int *data;
    Deep(int val) { data = new int(val); }

    // Deep copy constructor
    Deep(const Deep &other)
    {
        data = new int(*other.data);
    }

    ~Deep() { delete data; }
};

void shallow_demo()
{
    Shallow a(10);
    Shallow b(a); // Có lỗi gì không ????  ---> b.data = a.data;
}

void deep_demo()
{
    Deep a(10);
    Deep b = a; // Deep copy: b.data là vùng nhớ mới
    std::cout << "a.data = " << *a.data << ", b.data = " << *b.data << std::endl;
}

int main()
{
    // shallow_demo();
    deep_demo();

    return 0;
}
#endif

/*
-------------------------------------------------------
Demo: Move Semantics
-------------------------------------------------------
*/
#if 0

/*
Vấn đề: Khi ta viết Buffer b2 = Buffer(100);
        - Cái Buffer(100) ở bên phải là một rvalue (đối tượng tạm). Nó sẽ bị hủy ngay sau dòng đó.

Cơ hội: Vì nó sắp bị hủy, tại sao ta không "ăn trộm" tài nguyên của nó?

Giải pháp: Ta tạo ra một Constructor chấp nhận rvalue reference (Buffer&& other). 
           Chiếc móc && này sẽ tóm lấy đối tượng tạm đó, cho phép ta lấy con trỏ data của nó trước khi nó tan biến.
*/
#include <iostream>
#include <vector>
#include <utility> // Thư viện chứa std::move

class Buffer
{
public:
    int *data;
    size_t size;

    // 1. Constructor khởi tạo tài nguyên
    Buffer(size_t s) : size(s)
    {
        data = new int[size];
        std::cout << "Constructor: Cap phat " << size << " phan tu.\n";
    }

    // 2. Copy Constructor (Deep Copy) - "Xây nhà mới, chép đồ sang"
    Buffer(const Buffer &other) : size(other.size)
    {
        data = new int[size];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
        std::cout << "Copy Constructor: Deep Copy tai nguyen.\n";
    }

    // 3. Move Constructor - "Chuyen quyen so huu chia khoa"
    Buffer(Buffer &&other) : data(nullptr), size(0)
    {
        // "Lay" tai nguyen tu doi tuong cu
        this -> data = other.data;
        this -> size = other.size;

        // "Xoa dau vet" o doi tuong cu (de destructor cua no khong delete nham)
        other.data = nullptr;
        other.size = 0;

        std::cout << "Move Constructor: Chuyen quyen so huu (Owner Transfer).\n";
    }

    ~Buffer()
    {
        delete[] data;
        std::cout << "Destructor: Giai phong bo nho.\n";
    }
};

int main()
{
    // int y = x +1;

    std::cout << "--- Khoi tao b1 ---\n";
    Buffer b1(1000000); // Gia su mang rat lon

    std::cout << "\n--- Thuc hien Copy (b2 = b1) ---\n";
    Buffer b2 = b1; // Goi Copy Constructor -> Ton thoi gian copy mang lon

    std::cout << "\n--- Thuc hien Move (b3 = move(b1)) ---\n";
    // std::move ép b1 thành rvalue để kích hoạt Move Constructor
    Buffer b3 = std::move(b1); // khi gọi move thì hàm move constructor được gọi

    std::cout << "\n--- Ket thuc chuong trinh ---\n";
    return 0;
}

#endif

/*
III. Smart Pointer
------------------
1. Định nghĩa
    - Là các class quản lý con trỏ tự động (không cần delete thủ công).
    - Giúp tránh memory leak, double free, dangling pointer.

2. Các loại smart pointer chính
    - std::unique_ptr:
        + Sở hữu duy nhất, không thể copy.
        + Có thể chuyển quyền sở hữu (move).
        + Dùng khi rõ ràng chỉ một nơi quản lý tài nguyên.
        + Cú pháp: std::unique_ptr<Type> ptr(new Type(...));
    - std::shared_ptr:
        + Sở hữu chia sẻ, nhiều con trỏ cùng quản lý một tài nguyên.
        + Dùng khi nhiều nơi cần truy cập cùng tài nguyên.
        + Có ref count đếm số con trỏ đang sở hữu tài nguyên.
        + Khi ref count về 0, tài nguyên được giải phóng.
        + Cú pháp: std::shared_ptr<Type> ptr = std::make_shared<Type>(...);
    - std::weak_ptr:
        + Không sở hữu tài nguyên, không tăng ref count.
        + Dùng để tránh vòng tham chiếu với shared_ptr.
        + Cần chuyển sang shared_ptr để truy cập tài nguyên.
        + Cú pháp: std::weak_ptr<Type> wptr = sptr; // từ shared_ptr

3. Cách sử dụng
    - Khai báo và khởi tạo smart pointer.
        + với unique_ptr: std::unique_ptr<int> uptr(new int(10));
        + với shared_ptr: auto sptr = std::make_shared<int>(20);
        + với weak_ptr: std::weak_ptr<int> wptr = sptr;
    - Truy cập thành viên qua operator* và operator->.
    - Chuyển quyền sở hữu với std::move (cho unique_ptr).
    - Kiểm tra ref count với use_count() (cho shared_ptr).
    - Chuyển weak_ptr sang shared_ptr với lock().

4. Lợi ích
    - Tự động quản lý vòng đời tài nguyên.
    - Giảm thiểu lỗi liên quan đến bộ nhớ.
    - Tăng tính an toàn và rõ ràng trong quản lý bộ nhớ.

5. Smart pointer tự động giải phóng bộ nhớ khi ra khỏi scope.

---------------------------------
Demo 8: unique_ptr cơ bản
---------------------------------
*/
#if 0
#include <iostream>
#include <memory>
#include <string>

class Resource
{
public:
    Resource(const std::string &name) : name_(name)
    {
        std::cout << "Resource " << name_ << " created." << std::endl;
    }
    ~Resource()
    {
        std::cout << "Resource " << name_ << " destroyed." << std::endl;
    }
    void doSomething()
    {
        std::cout << "Using resource " << name_ << std::endl;
    }

private:
    std::string name_;
};


void processUniqueResource(std::unique_ptr<Resource> mPtr)
{
    // mPtr = std::move(ptr2);
    mPtr->doSomething();
    // Khi hàm kết thúc, resource tự động bị hủy
}

int main()
{
    // Tạo unique_ptr bằng std::make_unique (an toàn)
    std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>("unique_resource_1");

    // Lỗi: unique_ptr không thể sao chép
    // std::unique_ptr<Resource> ptr2 = ptr1;
    // Di chuyển quyền sở hữu từ ptr1 sang ptr2
    std::unique_ptr<Resource> ptr2 = std::move(ptr1);

    if (ptr1 == nullptr)
    {
        std::cout << "ptr1 no longer owns the resource." << std::endl;
    }
    ptr2->doSomething();

    // Truyền unique_ptr vào hàm bằng cách di chuyển
    processUniqueResource(std::move(ptr2));

    // Sau khi hàm kết thúc, ptr2 cũng không còn sở hữu tài nguyên
    if (ptr2 == nullptr)
    {
        std::cout << "ptr2 no longer owns the resource after moving to function." << std::endl;
    }

    // Khi main() kết thúc, không có memory leak
    return 0;
}
#endif

/*
---------------------------------
Demo : shared_ptr và ref count
---------------------------------
*/
#if 0
#include <iostream>
#include <memory>
#include <string>

class SharedResource
{
public:
    SharedResource(const std::string &name) : name_(name)
    {
        std::cout << "Line " << __LINE__ << " SharedResource " << name_ << " created." << std::endl;
    }
    ~SharedResource()
    {
        std::cout << "Line " << __LINE__ << " SharedResource " << name_ << " destroyed." << std::endl;
    }

private:
    std::string name_;
};

int main()
{
    // Tạo shared_ptr bằng std::make_shared (tối ưu hóa)
    std::shared_ptr<SharedResource> ptr1 = std::make_shared<SharedResource>("shared_resource_1");
    std::cout << "Line " << __LINE__ << " Reference count: " << ptr1.use_count() << std::endl; // Output: 1

    // Tạo bản sao của shared_ptr, bộ đếm tăng lên
    std::shared_ptr<SharedResource> ptr2 = ptr1;
    std::cout << "Line " << __LINE__ << " Reference count: " << ptr1.use_count() << std::endl; // Output: 2

    {
        // Tạo thêm bản sao trong một scope nhỏ hơn
        std::shared_ptr<SharedResource> ptr3 = ptr1;
        std::cout << "Line " << __LINE__ << " Reference count inside block: " << ptr1.use_count() << std::endl; // Output: 3
    } // ptr3 ra khỏi scope, bộ đếm giảm đi 1

    std::cout << "Line " << __LINE__ << " Reference count after ptr3 goes out of scope: " << ptr1.use_count() << std::endl;

    // Khi main() kết thúc, ptr1 và ptr2 ra khỏi scope, bộ đếm về 0, tài nguyên bị giải phóng
    return 0;
}
#endif

/*
-------------------------------------------------------
Demo: weak_ptr tránh memory leak vòng lặp
-------------------------------------------------------
*/
#if 1
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declaration để Employee biết Department tồn tại
class Department;

class Employee
{
public:
    std::string name;
    // Sử dụng weak_ptr để trỏ ngược về Department
    // Điều này giúp tránh vòng lặp tham chiếu (Circular Dependency)
    // std::weak_ptr<Department> dept;
    std::shared_ptr<Department> dept;
    Employee(std::string n) : name(n)
    {
        std::cout << "[Employee] " << name << " gia nhap cong ty.\n";
    }

    ~Employee()
    {
        std::cout << "[Employee] " << name << " da nghi viec (bi huy).\n";
    }

    void showDepartment();
};

class Department
{
public:
    std::string deptName;
    // Department sở hữu các Employee
    std::vector<std::shared_ptr<Employee>> employees;

    Department(std::string n) : deptName(n)
    {
        std::cout << "[Department] Phong " << deptName << " duoc thanh lap.\n";
    }

    ~Department()
    {
        std::cout << "[Department] Phong " << deptName << " bi giai the (bi huy).\n";
    }

    void addEmployee(std::shared_ptr<Employee> e)
    {
        employees.push_back(e);
    }
};

// void Employee::showDepartment()
// {
//     // Để sử dụng weak_ptr, ta PHẢI chuyển nó thành shared_ptr bằng lock()
//     if (std::shared_ptr<Department> s_ptr = dept.lock())
//     {
//         std::cout << "Nhan vien " << name << " dang thuoc phong: " << s_ptr->deptName << "\n";
//     }
//     else
//     {
//         std::cout << "Nhan vien " << name << ": Phong ban nay khong con ton tai!\n";
//     }
// }

int main()
{
    std::cout << "--- KHOI TAO HE THONG ---\n";

    // 1. Tạo phòng ban và nhân viên
    std::shared_ptr<Department> IT_Dept = std::make_shared<Department>("Cong Nghe Thong Tin");
    std::shared_ptr<Employee> emp1 = std::make_shared<Employee>("Nguyen Van A");
     std::cout << "\n--- KHOI TAO BAN DAU  ---\n";
    std::cout << "Ref count cua IT_Dept: " << IT_Dept.use_count() << " (Chi co main giu)\n";
    std::cout << "Ref count cua emp1: " << emp1.use_count() << "\n";

    // 2. Thiết lập mối quan hệ
    IT_Dept->addEmployee(emp1);
    emp1->dept = IT_Dept; // Gán weak_ptr

    std::cout << "\n--- KIEM TRA THONG TIN ---\n";
    std::cout << "Ref count cua IT_Dept: " << IT_Dept.use_count() << " (Chi co main giu)\n";
    std::cout << "Ref count cua emp1: " << emp1.use_count() << "\n";
    // emp1->showDepartment();

    std::cout << "\n--- GIAI THE PHONG BAN ---\n";
    IT_Dept.reset(); // Huỷ phòng ban sớm

    std::cout << "Sau khi reset IT_Dept, Ref count cua emp1: " << emp1.use_count() << "\n\n";

    // 3. Kiểm tra xem nhân viên còn biết phòng ban không
    // emp1->showDepartment();

    std::cout << "\n--- KET THUC CHUONG TRINH ---\n";
    return 0;
}
#endif