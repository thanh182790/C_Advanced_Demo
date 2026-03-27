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

class Shallow {
public:
    int* data;
    Shallow(int val) { data = new int(val); }
    ~Shallow() { delete data; }
};

class Deep {
public:
    int* data;
    Deep(int val) { data = new int(val); }
    
    // Deep copy constructor
    Deep(const Deep& other) {
        data = new int(*other.data);
    }
    
    ~Deep() { delete data; }
};

void shallow_demo() {
    Shallow a(10);
    Shallow b = a; // Shallow copy: cả a và b đều trỏ cùng data
    // Khi ra khỏi hàm, destructor của b chạy xóa data, 
    // sau đó destructor của a chạy lại xóa lần nữa -> gây crash/double free
}

void deep_demo() {
    Deep a(10);
    Deep b = a; // Deep copy: b.data là vùng nhớ mới
    std::cout << "a.data = " << *a.data << ", b.data = " << *b.data << std::endl;
}

int main() {
    // shallow_demo(); // Sẽ gây crash chương trình
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

#include <iostream>
#include <vector>
#include <utility> // Thư viện chứa std::move

class Buffer {
public:
    int* data;
    size_t size;

    // 1. Constructor khởi tạo tài nguyên
    Buffer(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Constructor: Cap phat " << size << " phan tu.\n";
    }

    // 2. Copy Constructor (Deep Copy) - "Xây nhà mới, chép đồ sang"
    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        std::cout << "Copy Constructor: Deep Copy tai nguyen.\n";
    }

    // 3. Move Constructor - "Chuyen quyen so huu chia khoa"
    Buffer(Buffer&& other) no_base_check : data(nullptr), size(0) {
        // "Lay" tai nguyen tu doi tuong cu
        data = other.data;
        size = other.size;

        // "Xoa dau vet" o doi tuong cu (de destructor cua no khong delete nham)
        other.data = nullptr;
        other.size = 0;
        
        std::cout << "Move Constructor: Chuyen quyen so huu (Owner Transfer).\n";
    }

    ~Buffer() {
        delete[] data;
        std::cout << "Destructor: Giai phong bo nho.\n";
    }
};

int main() {
    std::cout << "--- Khoi tao b1 ---\n";
    Buffer b1(1000000); // Gia su mang rat lon

    std::cout << "\n--- Thuc hien Copy (b2 = b1) ---\n";
    Buffer b2 = b1; // Goi Copy Constructor -> Ton thoi gian copy mang lon

    std::cout << "\n--- Thuc hien Move (b3 = move(b1)) ---\n";
    // std::move ép b1 thành rvalue để kích hoạt Move Constructor
    Buffer b3 = std::move(b1); 

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

class Resource {
public:
    Resource(const std::string& name) : name_(name) {
        std::cout << "Resource " << name_ << " created." << std::endl;
    }
    ~Resource() {
        std::cout << "Resource " << name_ << " destroyed." << std::endl;
    }
    void doSomething() {
        std::cout << "Using resource " << name_ << std::endl;
    }
private:
    std::string name_;
};

void processUniqueResource(std::unique_ptr<Resource> resource) {
    resource->doSomething();
    // Khi hàm kết thúc, resource tự động bị hủy
}

int main() {
    // Tạo unique_ptr bằng std::make_unique (an toàn)
    std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>("unique_resource_1");

    // Lỗi: unique_ptr không thể sao chép
    // std::unique_ptr<Resource> ptr2 = ptr1;

    // Di chuyển quyền sở hữu từ ptr1 sang ptr2
    std::unique_ptr<Resource> ptr2 = std::move(ptr1);

    if (ptr1 == nullptr) {
        std::cout << "ptr1 no longer owns the resource." << std::endl;
    }
    ptr2->doSomething();

    // Truyền unique_ptr vào hàm bằng cách di chuyển
    processUniqueResource(std::move(ptr2));

    // Sau khi hàm kết thúc, ptr2 cũng không còn sở hữu tài nguyên
    if (ptr2 == nullptr) {
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

class SharedResource {
public:
    SharedResource(const std::string& name) : name_(name) {
        std::cout << "Line " << __LINE__ << " SharedResource " << name_ << " created." << std::endl;
    }
    ~SharedResource() {
        std::cout << "Line " << __LINE__ << " SharedResource " << name_ << " destroyed." << std::endl;
    }
private:
    std::string name_;
};

int main() {
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

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    A() { std::cout << "A created." << std::endl; }
    ~A() { std::cout << "A destroyed." << std::endl; }
};

class B {
public:
    // Sử dụng weak_ptr để tránh vòng lặp sở hữu
    std::weak_ptr<A> a_ptr;
    B() { std::cout << "B created." << std::endl; }
    ~B() { std::cout << "B destroyed." << std::endl; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    // Thiết lập vòng lặp sở hữu
    a->b_ptr = b;
    b->a_ptr = a;

    // Nếu b_ptr là shared_ptr, a và b sẽ không bao giờ bị hủy
    // vì mỗi đối tượng giữ một shared_ptr đến đối tượng kia.

    // Với weak_ptr, a và b sẽ được hủy một cách chính xác
    return 0;
}
#endif