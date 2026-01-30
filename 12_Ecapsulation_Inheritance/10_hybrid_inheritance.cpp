#include <iostream>
#include <string>
using namespace std;

// Lớp gốc
class Person {
protected:
    string name;

public:
    Person(string name) : name(name) {
        cout << "[Person ctor]" << endl;
    }

    void showName() const {
        cout << "Ten: " << name << endl;
    }
};

// Kế thừa phân cấp + virtual (quan trọng)
class Employee : virtual public Person {  //Nếu bỏ virtual đi thì sẽ lỗi biên dịch
protected:
    double salary;

public:
    Employee(string name, double salary)
        : Person(name), salary(salary) {
        cout << "[Employee ctor]" << endl;
    }
};

class Student : virtual public Person {  // Nếu bỏ virtual đi thì sẽ lỗi biên dịch 
protected:
    double gpa;

public:
    Student(string name, double gpa)
        : Person(name), gpa(gpa) {
        cout << "[Student ctor]" << endl;
    }
};

// Đa kế thừa → Hybrid
class WorkingStudent : public Employee, public Student {
public:
    WorkingStudent(string name, double salary, double gpa)
        : Person(name),        //  chỉ lớp cuối cùng khởi tạo Person
          Employee(name, salary),
          Student(name, gpa) {
        cout << "[WorkingStudent ctor]" << endl;
    }

    void showInfo() const {
        showName();   // không mơ hồ
        cout << "Luong: " << salary << endl;
        cout << "GPA: " << gpa << endl;
    }
};

int main() {
    WorkingStudent ws("Nguyen Van A", 1500, 3.6);

    cout << "\n=== Thong tin WorkingStudent ===" << endl;
    ws.showInfo();

    return 0;
}

