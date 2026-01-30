#include <iostream>

class ISensor {
public:
    int x = 10; // từ khoá const để ngăn chặn ghi đè các member
    virtual float readValue() const {
        std::cout << "ISensor::readValue() called." << std::endl;
        return 0.0;
    }
    virtual ~ISensor() = default;
};

class TemperatureSensor : public ISensor {
public:
    float readValue() const override {
        std::cout << "TemperatureSensor::readValue() called." << std::endl;
        // Simulate reading from an ADC.
        return 25.7f;
    }
};

class PressureSensor : public ISensor {
public:
    float readValue() const override {
        //x = 100;
        std::cout << "PressureSensor::readValue() called." << std::endl;
        // Simulate reading from an I2C device.
        return 1013.25f;
    }
};

int main() {
    ISensor* sensor_list[2];
    sensor_list[0] = new TemperatureSensor();
    sensor_list[1] = new PressureSensor();

    std::cout << "--- Reading all sensors ---" << std::endl;

    for (ISensor* sensor : sensor_list) {
        float value = sensor->readValue();
        std::cout << "Sensor value: " << value << std::endl;
    }

    // QUAN TRỌNG: Giải phóng bộ nhớ thủ công
    std::cout << "\n--- Cleaning up memory ---" << std::endl;
    delete sensor_list[0];
    delete sensor_list[1];

    return 0;
}
