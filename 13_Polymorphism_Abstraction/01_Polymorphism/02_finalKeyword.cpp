#include <iostream>

// --- Base Class ---
class ISensor {
public:
    virtual const char* getProtocol() {
        return "Generic/Analog";
    }
    virtual ~ISensor() = default;
};

// --- Derived Class (Sử dụng 'final' cho phương thức) ---
class DigitalSensor : public ISensor {
public:
    // Đây là triển khai CUỐI CÙNG của getProtocol cho nhánh cảm biến này.
    // Không lớp nào kế thừa từ DigitalSensor có thể ghi đè hàm này nữa.
    const char* getProtocol() override final {
        return "Standard I2C Protocol";
    }
};

// --- Sub-derived Class (Sẽ gây lỗi biên dịch nếu cố gắng ghi đè) ---
class AdvancedDigitalSensor : public DigitalSensor {
public:
    // Compiler error!
    // Trình biên dịch sẽ dừng lại vì getProtocol() đã được đánh dấu 'final' ở lớp DigitalSensor.
    
    /* const char* getProtocol() override { 
        return "Custom High-Speed I2C"; 
    } 
    */
};

// -- Ngăn chặn kế thừa lớp ---
class Base final { 
    // Lớp này không thể bị kế thừa vì có từ khóa 'final'
    // tức là lớp này là lớp triển khai đầy đủ hoàn chỉnh rồi không cần có thằng nào kế thừa để triển khai nữa
};

/*
class Derived : public Base { // LỖI BIÊN DỊCH: cannot derive from 'final' base
};
*/

int main() {
    DigitalSensor genericDigital;
    std::cout << "Generic Digital Sensor uses protocol: " 
              << genericDigital.getProtocol() << std::endl;

    // AdvancedDigitalSensor vẫn có thể sử dụng hàm của lớp cha,
    // nhưng không thể định nghĩa lại nó.
    AdvancedDigitalSensor advancedSensor;
    std::cout << "Advanced Digital Sensor uses protocol: " 
              << advancedSensor.getProtocol() << std::endl;

    return 0;
}
