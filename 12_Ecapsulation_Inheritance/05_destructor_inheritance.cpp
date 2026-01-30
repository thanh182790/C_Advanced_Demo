#include <iostream>

// --- Base Class ---
class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
    
    // Base destructor
    ~Base() {
        std::cout << "2. Base destructor called" << std::endl;
    }
};

// --- Derived Class ---
class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor" << std::endl; }
    
    // Derived destructor
    ~Derived() {
        std::cout << "1. Derived destructor called" << std::endl;
    }
};

int main() {
    std::cout << "--- Creating a Derived object ---" << std::endl;
    
    Derived d;
    
    std::cout << "--- Deleting the object as it goes out of scope ---" << std::endl;
    
    return 0;
}
