/*
 * Khởi tạo uỷ quyền là một tính năng cho phép một hàm khởi tạo có thể gọi một hàm khởi tạo khác trong cùng một lớp
 */

#include <iostream>
#include <cstring>

class Student
{
private:
    char *name;
    int age;

public:
    // Constructor mặc định -> ỦY QUYỀN
    Student();
    // Constructor trung tâm
    Student(const char *n, int a) : age(a)
    {
        if (n)
        {
            name = new char[strlen(n) + 1];
            strcpy(name, n);
        }
        else
        {
            name = nullptr;
        }
        std::cout << "Main constructor called" << std::endl;
    }

    // Constructor 1 tham số -> ỦY QUYỀN
    Student(const char *n) : Student(n, 0)
    {
        std::cout << "Single-arg constructor delegated" << std::endl;
    }

    ~Student()
    {
        delete[] name;
    }

    void print() const
    {
        std::cout << "Name: "
                  << (name ? name : "null")
                  << ", Age: " << age << std::endl;
    }
};
Student::Student()
    : Student::Student(nullptr, 0)
{
    std::cout << "Default constructor delegated" << std::endl;
}
int main()
{
    Student s1;
    Student s2("Nguyen Van B");
    Student s3("Nguyen Van C", 22);

    s1.print();
    s2.print();
    s3.print();

    return 0;
}
