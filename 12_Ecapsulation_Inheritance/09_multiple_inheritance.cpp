#include <iostream>
using namespace std;

// Lớp cha thứ nhất
class Flyable {
public:
    void fly() const {
        cout << "Toi co the bay" << endl;
    }
};

// Lớp cha thứ hai
class Swimmable {
public:
    void swim() const {
        cout << "Toi co the boi" << endl;
    }
};

// Lớp con kế thừa từ nhiều lớp
class Duck : public Flyable, public Swimmable {
public:
    void introduce() const {
        cout << "Toi la mot con vit" << endl;
    }
};

int main() {
    Duck d;

    d.introduce();
    d.fly();    // kế thừa từ Flyable
    d.swim();   // kế thừa từ Swimmable

    return 0;
}

