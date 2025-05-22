
#include <iostream>
#include <vector>
#include <map>
#include <string>

int auto_(void) {
    // Using auto with basic types
    auto x = 10;           // x is an int
    auto y = 3.14;         // y is a double
    auto z = "Hello";      // z is a const char*
    
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
    std::cout << "z: " << z << "\n";
    
    // Using auto with containers
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Using auto with structured bindings (C++17 and later)
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << "\n";
    }
    
    // Using auto with functions
    auto sum = [](auto a, auto b) {
        return a + b;
    };
    
    std::cout << "Sum of 5 and 3.5: " << sum(5, 3.5) << "\n";
    std::cout << "Sum of 2 and 3: " << sum(2, 3) << "\n";

    // Using auto with complex types
    std::pair<int, std::string> myPair = {1, "example"};
    auto [number, text] = myPair;
    std::cout << "number: " << number << ", text: " << text << "\n";

    return 0;
}

