/*
TÍNH ĐÓNG GÓI (ENCAPSULATION)

Tính đóng gói là nguyên tắc gói gọn dữ liệu (thuộc tính) và các phương thức
xử lý dữ liệu đó vào trong một đơn vị duy nhất là Lớp.

Mục đích chính của tính đóng gói là:
- Che giấu dữ liệu (Data Hiding): bảo vệ trạng thái nội tại của đối tượng
  khỏi sự truy cập và thay đổi trực tiếp từ bên ngoài.
- Đảm bảo tính toàn vẹn dữ liệu thông qua kiểm soát quyền truy cập.

Tính đóng gói được thực hiện thông qua các access modifiers:
- private: chỉ truy cập được bên trong lớp (khuyến nghị cho thuộc tính).
- protected: truy cập được trong lớp và lớp con.
- public: truy cập được từ mọi nơi.

Để cho phép bên ngoài tương tác một cách có kiểm soát với dữ liệu private,
lớp cung cấp các phương thức public gọi là Getter và Setter.
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    double balance;     // Không cho truy cập trực tiếp

public:
    string ownerName;   // Dữ liệu bị che giấu
    // Constructor
    BankAccount(string name, double initialBalance) {
        ownerName = name;
        if (initialBalance >= 0)
            balance = initialBalance;
        else
            balance = 0;
    }

    // Getter: chỉ đọc dữ liệu
    string getOwnerName() const {
        return ownerName;
    }

    double getBalance() const {
        return balance;
    }

    // Setter: ghi dữ liệu có kiểm soát
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

int main() {
    BankAccount acc("Nguyen Van A", 1000);

    cout << "Chu tai khoan: " << acc.getOwnerName() << acc.ownerName << endl;
    cout << "So du ban dau: " << acc.getBalance() << endl;

    acc.deposit(500);
    cout << "Sau khi nap tien: " << acc.getBalance() << endl;

    acc.withdraw(300);
    cout << "Sau khi rut tien: " << acc.getBalance() << endl;

    // ❌ Không thể truy cập trực tiếp
    // acc.balance = 1000000; // ERROR: 'balance' is private

    return 0;
}

