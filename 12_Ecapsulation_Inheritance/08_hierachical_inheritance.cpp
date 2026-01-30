#include <iostream>
using namespace std;

// Lớp cha
class Shape {
protected:
    double area;

public:
    Shape() : area(0) {}

    void showArea() const {
        cout << "Dien tich: " << area << endl;
    }
};

// Lớp con thứ nhất
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) {
        width = w;
        height = h;
        area = width * height;
    }
};

// Lớp con thứ hai
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) {
        radius = r;
        area = 3.14159 * radius * radius;
    }
};

int main() {
    Rectangle rect(5, 4);
    Circle cir(3);

    cout << "=== Rectangle ===" << endl;
    rect.showArea();

    cout << "\n=== Circle ===" << endl;
    cir.showArea();

    return 0;
}

