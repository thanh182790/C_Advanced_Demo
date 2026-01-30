/*
 * Quan hệ IS-IMPLEMENTED-IN-TERMS-OF
 *  - Class GPIO mô tả phàn cứng bên dưới
 *  - LedController sử dụng GPIO để điều khiển led
 * Dùng khi:
 *  - Base class chỉ là chi tiết cài đặt
 *  - Không muốn user biết hoặc dùng base
 * User KHÔNG BIẾT GPIO tồn tại
 * GPIO là chi tiết ẩn */

#include <iostream>
using namespace std;

/*
 * Low-level GPIO driver
 */
class Gpio {
public:
    void initPin() {
        cout << "[Gpio] initPin(): Configure GPIO pin" << endl;
    }

protected:
    void writePin(bool value) {
        cout << "[Gpio] writePin(): value = " << value << endl;
    }

private:
    int pinNumber = 13;
};

/*
 * LedController is IMPLEMENTED IN TERMS OF Gpio
 */
class LedController : private Gpio {
public:
    void init() {
        cout << "[LedController] init()" << endl;
        initPin();   // allowed (was public, now private inside)
    }

    void turnOn() {
        cout << "[LedController] turnOn()" << endl;
        writePin(true);
    }

    void turnOff() {
        cout << "[LedController] turnOff()" << endl;
        writePin(false);
    }

private:
    bool ledState = false;
};

int main() {
    LedController led;
    led.init();
    led.turnOn();
    led.turnOff();

    // led.initPin();   // not accessible
}

