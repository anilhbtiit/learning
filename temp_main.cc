#include <iostream>
#include <template.h>

int main() {
    std::cout << "Addition: " << add(2, 3, 4,6) << std::endl;              // 5
    std::cout << "Multiplication: " << multiply(2,4, 3) << std::endl;   // 6
    std::cout << "Subtraction: " << subtract(20, 6, 3, 8) << std::endl;      // -1

    std::cout << "Addition: " << add(2.5, 3.5, 8,9) << std::endl;          // 6.0
    std::cout << "Multiplication: " << multiply(2.5, 3.5, 2, 3, 4, 5) << std::endl; // 8.75
    //std::cout << "Subtraction: " << subtract("2.5", 3.5) << std::endl;  // -1.0

    return 1;
}

