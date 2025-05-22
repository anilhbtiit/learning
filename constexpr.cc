#include <iostream>
#include <chrono>
#include <thread>

#if 0
constexpr 
int square(int x) {
    for(int i=0; i<262144; i++);
    return x * x;
}



int main() {
    {

      auto start = std::chrono::high_resolution_clock::now();    
      constexpr
        int value = 5;
      constexpr
        int result = square(value); // Evaluated at compile time

      auto end = std::chrono::high_resolution_clock::now();

      // Calculate the duration in milliseconds
      std::chrono::duration<double, std::milli> duration = end - start;
      std::cout << "\n " << duration.count() << "milli seconds taken";
    }
  
    #if 0
    static_assert(result==25);
    std::cout << "Square of " << value << " is " << result << std::endl;

    #endif
    
    return 0;
}
#endif

class Circle {
public:
    //constexpr 
      Circle(double r) : radius(r) {}

    //constexpr 
      double getArea() const {
        return pi * radius * radius;
    }

    //constexpr 
      double getRadius() const {
      return radius;
    }
private:
    static constexpr double pi = 3.14159265358979323846;
    double radius;
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();    
    double totalArea = 0;
    //constexpr 
      double baseRadius = 5.0;
    double radius = 0;
    for(int i=0; i<5000; i++) {
      radius = (baseRadius);
      //constexpr 
        Circle c(baseRadius); // Compile-time instantiation of Circle object
      //constexpr 
        double area = c.getArea();
      totalArea += area;
    }
    auto end = std::chrono::high_resolution_clock::now();    
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Total area of circle with base radius to last radius " << radius << " is " << totalArea << "\nExecution time: " << duration.count() << " ms" << std::endl;

    return 0;
}
