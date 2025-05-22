#include <iostream>
#include <type_traits>

// Define a concept that checks if a type is an arithmetic type
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// Function template constrained with the Arithmetic concept
template<Arithmetic T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << "Addition of integers: " << add(2, 3) << std::endl;          // 5
    std::cout << "Addition of floating point numbers: " << add(2.5, 3.5) << std::endl;  // 6.0

    // Uncommenting the following line will result in a compile-time error
    // std::cout << "Addition of strings: " << add(std::string("hello"), std::string("world")) << std::endl;

    return 0;
}

