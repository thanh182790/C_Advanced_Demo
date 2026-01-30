#include <iostream>
#include <string>

// --- Base Class ---
class Base {
protected:
    std::string base_name;
public:
    // Base constructor default
//    Base() {
//        std::cout << "0. Base constructore called.\n";
//    }
    // Base() = default;
    // Base constructor
    Base(std::string name) : base_name(name) {
        std::cout << "1. Base constructor called for: " << base_name << std::endl;
    }
};

// --- Derived Class ---
class Derived : public Base {
private:
    std::string derived_name;
public:
    // Derived constructor calls the Base constructor using the initializer list
    // Compile error when delete Base(b_name)
    // Beacause missing constructor no parameter.
    Derived(std::string b_name, std::string d_name) 
        : Base(b_name), derived_name(d_name) { // <-- This is the key part   --->Base()
        std::cout << "2. Derived constructor called for: " << derived_name << std::endl;
    }
};

int main() {
    std::cout << "--- Creating a Derived object ---" << std::endl;
    
    Derived d("Foundation", "House");
    
    std::cout << "--- Object created ---" << std::endl;
    
    return 0;
}
