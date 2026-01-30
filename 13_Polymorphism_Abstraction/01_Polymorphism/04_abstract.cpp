#include <iostream>
#include <string>

// 1. Định nghĩa Interface (Lớp trừu tượng thuần túy)
class ISensor {
public:
    // Các hàm ảo thuần túy (pure virtual functions)
    virtual const char* getStatus() const = 0;
    virtual float readValue() const = 0;
    virtual const char* getUnits() const = 0;

    // Virtual destructor là bắt buộc khi dùng đa hình để giải phóng bộ nhớ đúng cách
    virtual ~ISensor() = default;
};

// 2. Lớp TemperatureSensor thực thi ISensor
class TemperatureSensor : public ISensor {
public:
    const char* getStatus() const override {
        return "OK";
    }

    float readValue() const override {
        // Giả lập đọc dữ liệu qua giao thức SPI
        std::cout << "[SPI Read] ";
        return 24.5f;
    }

    const char* getUnits() const override {
        return "Celsius";
    }
};

// 3. Lớp PressureSensor thực thi ISensor
class PressureSensor : public ISensor {
public:
    const char* getStatus() const override {
        return "OK";
    }

    float readValue() const override {
        // Giả lập đọc dữ liệu qua giao thức I2C
        std::cout << "[I2C Read] ";
        return 1013.25f;
    }

    const char* getUnits() const override {
        return "hPa"; // hectopascals
    }
};

// 4. Lớp HumiditySensor thực thi ISensor
class HumiditySensor : public ISensor {
public:
    const char* getStatus() const override {
        return "ERROR";
    }

    float readValue() const override {
        // Giả lập đọc dữ liệu qua giao thức UART
        std::cout << "[UART Read] ";
        return -1.0f;
    }

    const char* getUnits() const override {
        return "% RH"; // Relative Humidity
    }
};

// 5. Hàm main để chạy Demo
int main() {
    const int SENSOR_COUNT = 3;
    
    // Mảng các con trỏ kiểu base class (ISensor) trỏ tới các object lớp con
    ISensor* sensor_list[SENSOR_COUNT];

    sensor_list[0] = new TemperatureSensor();
    sensor_list[1] = new PressureSensor();
    sensor_list[2] = new HumiditySensor();

    std::cout << "--- Polling all sensors in the system ---" << std::endl;

    for (int i = 0; i < SENSOR_COUNT; ++i) {
        // Gọi hàm thông qua con trỏ interface (Tính đa hình)
        const char* status = sensor_list[i]->getStatus();
        float value = sensor_list[i]->readValue();
        const char* units = sensor_list[i]->getUnits();

        std::cout << "-> Sensor Report | "
                  << "Status: " << status << ", "
                  << "Value: " << value << " " << units
                  << std::endl;
    }

    std::cout << "\n--- Cleaning up memory ---" << std::endl;
    for (int i = 0; i < SENSOR_COUNT; ++i) {
        delete sensor_list[i]; // Giải phóng bộ nhớ heap
    }

    return 0;
}
