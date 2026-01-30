/* Dùng khi:
 *  - Base class chỉ cho đội dev driver/ framework kế thừa
 *  - Không cho phía dev App sử dụng trực tiếp các API core vi có thể sai hệ thống.
 *
 * Internal framework base class
 */

#include <iostream>
using namespace std;

class DeviceCore {
public:
    void commonInit() {
        cout << "[DeviceCore] commonInit(): Shared initialization logic" << endl;
    }

protected:
    void powerOn() {
        cout << "[DeviceCore] powerOn(): Powering on device" << endl;
    }

private:
    void internalLog() {
        cout << "[DeviceCore] internalLog()" << endl;
    }
};

/*
 * Sensor built on top of DeviceCore
 */
class PressureSensor : protected DeviceCore {
public:
    void start() {
        cout << "[PressureSensor] start()" << endl;
        commonInit();  // public -> protected
        powerOn();     // protected -> protected
    }

    void readPressure() {
        cout << "[PressureSensor] readPressure(): Reading pressure value" << endl;
    }

private:
    int pressureValue = 0;
};

int main() {
    PressureSensor sensor;
    sensor.start();
    sensor.readPressure();

    // sensor.commonInit();  // not accessible
}

