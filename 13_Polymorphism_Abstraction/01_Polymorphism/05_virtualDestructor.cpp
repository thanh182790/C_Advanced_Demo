#include <iostream>

class ISensor {
public:
    // Constructor của lớp cha
    ISensor() { 
        std::cout << "ISensor created.\n"; 
    }

    // Destructor ảo (Virtual Destructor)
    // Phải có từ khóa 'virtual' ở đây để lớp con được hủy đúng cách
     ~ISensor() { 
        std::cout << "ISensor destroyed.\n"; 
    }

    // Hàm ảo đọc giá trị
    virtual float readValue() const { 
        return 0.0f; 
    }
};

class TemperatureSensor : public ISensor {
private:
    int _adc_channel; // Biến lưu kênh ADC

public:
    // Constructor lớp con, khởi tạo kênh ADC
    TemperatureSensor(int ch) : _adc_channel(ch) {
        std::cout << " -> TemperatureSensor created (ADC " << _adc_channel << ")\n";
    }

    // Destructor lớp con
    ~TemperatureSensor() {
        std::cout << " -> TemperatureSensor destroyed (ADC " << _adc_channel << " freed)\n";
    }

    // Ghi đè hàm đọc giá trị
    float readValue() const override { 
        return 25.7f; 
    }
};

int main() {
    // Tạo đối tượng lớp con nhưng dùng con trỏ lớp cha
    ISensor* s = new TemperatureSensor(1);

    std::cout << "\nDeleting sensor...\n";
    
    // Nếu destructor ở lớp ISensor không có 'virtual', 
    // dòng delete này sẽ chỉ gọi destructor của ISensor mà bỏ qua TemperatureSensor
    delete s; 

    return 0;
}
