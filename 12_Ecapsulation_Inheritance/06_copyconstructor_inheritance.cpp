/*
* 
* - Đối với class kế thừa:
*   + Object của class dẫn xuất LUÔN chứa object của class cơ sở
* 
* - Khi copy object của class dẫn xuất:
*   + Base part được copy TRƯỚC
*   + Sau đó mới copy phần riêng của Derived
* 
* - Nếu KHÔNG tự viết copy constructor cho Derived:
*   + Compiler tự sinh
*   + Tự động gọi copy constructor của Base
* 
* - Nếu TỰ VIẾT copy constructor cho Derived:
*   + BẮT BUỘC phải gọi copy constructor của Base
*   + Gọi thông qua initializer list
* - Cú pháp bắt buộc:
*   Derived(const Derived& other)
*       : Base(other)
*   {
*   }
* 
* - Nếu KHÔNG gọi Base(other):
*   + Base bị copy bằng default constructor
*   + Dữ liệu Base bị mất / sai
*   + Dễ gây bug nghiêm trọng
* 
* - Đặc biệt nguy hiểm khi:
*   + Base quản lý tài nguyên (pointer, buffer, handle, register)
*   + Có thể gây shallow copy / double free
* 
* - Thứ tự copy:
*   + Base → Derived (KHÔNG đổi được)
*/

#if 0
/* shallow copy */
#include <iostream>
using namespace std;

class Base {
protected:
    int* data;

public:
    Base(int value = 0) {
        data = new int(value);
        cout << "[Base ctor]   Alloc data at: " << data
             << " value = " << *data << endl;
    }

    // Copy constructor copy nông
    Base(const Base& other) {
        data = other.data;
        cout << "[Base copy]   Copy pointer: " << data << endl;
    }

    ~Base() {
        cout << "[Base dtor]   Delete data at: " << data << endl;
        delete data;
    }
};

class Derived : public Base {
public:
    Derived(int value = 0) : Base(value) {
        cout << "[Derived ctor]" << endl;
    }

    ~Derived() {
        cout << "[Derived dtor]" << endl;
    }
};

int main() {
    cout << "---- Create d1 ----" << endl;
    Derived d1(10);

    cout << "\n---- Copy d2 from d1 ----" << endl;
    Derived d2 = d1;

    cout << "\n---- End main ----" << endl;
    return 0;
}

#endif

#if 1
#include <iostream>
using namespace std;

class Base {
protected:
    int* data;

public:
    Base(int value = 0) {
        data = new int(value);
        cout << "[Base ctor]   Alloc data at: " << data
             << " value = " << *data << endl;
    }

    // Deep copy
    Base(const Base& other) {
        data = new int(*other.data);
        cout << "[Base copy]   Deep copy from "
             << other.data << " to " << data << endl;
    }

    virtual ~Base() {
        cout << "[Base dtor]   Delete data at: " << data << endl;
        delete data;
    }
};

class Derived : public Base {
public:
    Derived(int value = 0) : Base(value) {
        cout << "[Derived ctor]" << endl;
    }

    // Copy constructor cho class kế thừa
    // Derived(const Derived& other)
    //     : Base(other) {   // gọi copy ctor của Base
    //     cout << "[Derived copy]" << endl;
    // }

    ~Derived() {
        cout << "[Derived dtor]" << endl;
    }
};

int main() {
    cout << "---- Create d1 ----" << endl;
    Derived d1(10);

    cout << "\n---- Copy d2 from d1 ----" << endl;
    Derived d2 = d1;

    cout << "\n---- End main ----" << endl;
    return 0;
}

#endif
