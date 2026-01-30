#include <iostream>

class Sensor {
public:
    // Hàm không có virtual -> Static Binding
    const char* getStatus() const {
        std::cout << "Sensor::getStatus()" << std::endl;
        return "OK";
    }

    // Hàm có virtual -> Dynamic Binding
    virtual float readValue() const {
        std::cout << "ISensor::readValue() called." << std::endl;
        return 0.0f;
    }

    virtual ~Sensor() = default;
};

class TemperatureSensor : public Sensor {
public:
    // TemperatureSensor kế thừa getStatus() mà không thay đổi logic Dynamic
    const char* getStatus() const {
        std::cout << "TemperatureSensor::getStatus()" << std::endl;
        return "OK";
    }

    float readValue() const override {
        std::cout << "TemperatureSensor::readValue() called." << std::endl;
        return 25.7f;
    }
};

int main() {
    Sensor* p_sensor = new TemperatureSensor();

    std::cout << "--- 1. Testing Static Binding (non-virtual function) ---" << std::endl;
    // Trình biên dịch chỉ thấy p_sensor là kiểu Sensor* nên gọi Sensor::getStatus() lúc Compile Time
    const char* status = p_sensor->getStatus();
    std::cout << "Status: " << status << std::endl;

    std::cout << "\n--- 2. Testing Dynamic Binding (virtual function) ---" << std::endl;
    // Vì readValue() là virtual, chương trình kiểm tra đối tượng thực tế lúc Runtime (là TemperatureSensor)
    float value = p_sensor->readValue();
    std::cout << "Value: " << value << std::endl;

    // Cleanup
    delete p_sensor;
    return 0;
}
