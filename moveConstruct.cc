#include <iostream>
#include <utility>

class MyClass {
private:
    int* data;

public:
    // Default constructor
    MyClass() : data(nullptr) {
        std::cout << "Default constructor called" << std::endl;
    }

    // Parameterized constructor
    MyClass(int value) : data(new int(value)) {
        std::cout << "Parameterized constructor called" << std::endl;
    }

    // Copy constructor
    MyClass(const MyClass& other) : data(new int(*other.data)) {
        std::cout << "Copy constructor called" << std::endl;
    }

    // Move constructor
    MyClass(MyClass&& other) noexcept : data(other.data) {
        std::cout << "Move constructor called" << std::endl;
        other.data = nullptr; // leave the other object in a valid state
    }

    // Destructor
    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
        delete data;
    }

    // Print function
    void print() const {
        if (data) {
            std::cout << "Data: " << *data << std::endl;
        } else {
            std::cout << "Data is null" << std::endl;
        }
    }
};

int main() {
    MyClass obj1(10);
    obj1.print();

    MyClass obj2(std::move(obj1)); // Move constructor is called
    obj2.print();
    obj1.print(); // obj1 is in a valid but unspecified state

    return 0;
}

