#include <iostream>

class Camera {
public:
    void powerOn() {
        std::cout << "Camera is ON." << std::endl;
    }
};

class MusicPlayer {
public:
    void powerOn() {
        std::cout << "Music Player is ON." << std::endl;
    }
};

// Smartphone kế thừa từ cả Camera và MusicPlayer, tạo ra xung đột tên cho 'powerOn()'
class Smartphone : public Camera, public MusicPlayer {
public:
    // Chúng ta tạo một hàm mới để giải quyết xung đột nội bộ
    void turnOnEverything() {
        std::cout << "Turning on the smartphone..." << std::endl;
        
        // Sử dụng toán tử phân giải phạm vi '::' để chỉ định phiên bản powerOn() nào được gọi
        Camera::powerOn();
        MusicPlayer::powerOn();
    }

    // Hoặc ghi đè chính hàm gây xung đột
//    void powerOn() {
//        std::cout << "Turning on the smartphone..." << std::endl;
//        
//        // Gọi các phiên bản cụ thể
//        Camera::powerOn();
//        MusicPlayer::powerOn();
//    }
};

int main() {
    Smartphone myPhone;

    //  myPhone.powerOn(); // LỖI BIÊN DỊCH: Ambiguous call (Gọi nhập nhằng) nếu không được ghi đè

    // Gọi các phiên bản cụ thể trực tiếp từ main
   std::cout << "--- Calling specific versions ---" << std::endl;
   myPhone.Camera::powerOn();
   myPhone.MusicPlayer::powerOn();

    // Hoặc gọi hàm giải quyết mà chúng ta đã tạo
    std::cout << "\n--- Calling the wrapper function ---" << std::endl;
    myPhone.turnOnEverything();

    return 0;
}
