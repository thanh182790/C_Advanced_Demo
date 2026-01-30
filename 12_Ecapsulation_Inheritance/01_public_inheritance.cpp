/*
 * Quan hệ Is-A
 * “TemperatureSensor là một Device
 * Dùng khi:
 *  - Lớp dẫn xuất thực sự là một dạng của lớp cha
 *  - Lớp con có thể thay thế lớp cha về mặt ngữ nghĩa
 *   + Ở mọi nơi mà người ta nói về Device,
 *     thì việc dùng TemperatureSensor vẫn không làm sai ý nghĩa của hệ thống.
 **/

#include <iostream>
using namespace std;

/*
 * Base class representing a generic hardware device
 */
class Device {
public:
    void init() {
        cout << "[Device] init(): Initialize common device resources" << endl;
    }

    void reset() {
        cout << "[Device] reset(): Reset device hardware" << endl;
    }

protected:
    int deviceId = 0;

    void setId(int id) {
        deviceId = id;
        cout << "[Device] setId(): deviceId = " << deviceId << endl;
    }

private:
    void lowLevelCheck() {
        cout << "[Device] lowLevelCheck(): Internal hardware check" << endl;
    }
};

/*
 * Derived class: TemperatureSensor IS-A Device
 */
class TemperatureSensor : public Device {
public:
    void start() {
        cout << "[TemperatureSensor] start()" << endl;
        init();          // public from base
        setId(1001);     // protected from base
    }

    void readTemperature() {
        cout << "[TemperatureSensor] readTemperature(): Reading temperature value" << endl;
    }

private:
    int lastTemperature = 0;
};

int main() {
    TemperatureSensor sensor;
    sensor.start();
    sensor.reset();              // inherited public API
    sensor.readTemperature();
}

