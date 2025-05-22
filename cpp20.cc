#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <concepts>

// Concepts to constrain types
template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

// A function template constrained to integral types
template <Integral T>
T add(T a, T b) {
    return a + b;
}

// A function template constrained to floating-point types
template <FloatingPoint T>
T multiply(T a, T b) {
    return a * b;
}

// Spaceship operator for a custom struct
struct Point {
    int x, y;

    // Defaulting the spaceship operator
    auto operator<=>(const Point&) const = default;
};

int cpp20() {
    // Using concepts
    int intResult = add(3, 4);
    double floatResult = multiply(3.5, 2.0);

    std::cout << "intResult: " << intResult << "\n";
    std::cout << "floatResult: " << floatResult << "\n";

    // Using ranges
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::ranges::for_each(vec, [](int& n) { n *= 2; });

    for (const auto& n : vec) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // Using the spaceship operator
    Point p1 = {1, 2};
    Point p2 = {2, 3};

    if (p1 < p2) {
        std::cout << "p1 is less than p2\n";
    } else {
        std::cout << "p1 is not less than p2\n";
    }

    return 0;
}

