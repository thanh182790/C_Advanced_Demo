#include <iostream>
#include <string>
using namespace std;

// Lớp gốc (Base class)
class Person {
protected:
    string name;
    int age;

public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    void showPersonInfo() const {
        cout << "Ten: " << name << endl;
        cout << "Tuoi: " << age << endl;
    }
};

// Lớp kế thừa cấp 1
class Employee : public Person {
protected:
    double salary;

public:
    Employee(string name, int age, double salary)
        : Person(name, age) {
        this->salary = salary;
    }

    void showEmployeeInfo() const {
        showPersonInfo();
        cout << "Luong: " << salary << endl;
    }
};

// Lớp kế thừa cấp 2 (đa cấp)
class Manager : public Employee {
private:
    string department;

public:
    Manager(string name, int age, double salary, string dept)
        : Employee(name, age, salary) {
        department = dept;
    }

    void showManagerInfo() const {
        showEmployeeInfo();
        cout << "Phong ban: " << department << endl;
    }
};

int main() {
    Manager m("Nguyen Van A", 35, 2000, "IT");

    cout << "=== Thong tin Manager ===" << endl;
    m.showManagerInfo();

    return 0;
}

