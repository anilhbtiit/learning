#include <iostream>
#include <typeinfo>

class Base {
public:
  virtual void whoami() {
    std::cout << "I am Base\n";
  }
};

class Derived : public Base {
public:
  void whoami() override {
    std::cout << "I am Derived\n";
  }
};

template <typename T>
void printValue(const T& value) {
  if (typeid(value) == typeid(int)) {
    std::cout << "Integer: " << value << std::endl;
  } else if (typeid(value) == typeid(double)) {
    std::cout << "Double: " << value << std::endl;
  } else {
    std::cout << "Unknown type\n";
  }
}

int main() {
  Base* ptr = new Derived;
  ptr->whoami();  // Prints "I am Base" (static binding)

  if (typeid(*ptr) == typeid(Derived)) {
    static_cast<Derived*>(ptr)->whoami();  // Prints "I am Derived" (dynamic binding)
  }

  delete ptr;
  int x = 10;
  double y = 3.14;

  printValue(x);
  printValue(y);

  const char* str = "Hello";
  //const type_info& info = typeid(str);
  // std::cout << info.name() << std::endl;  // Not recommended, implementation-defined

  // Comparing with typeid(const char*) might not work reliably
  if (typeid(str) == typeid(const char*)) {
    std::cout << "It's a const char* (might not be reliable)" << std::endl;
  }

  unsigned long l1 = 55;
  if(typeid(l1) == typeid(unsigned long)) {
    std::cout << "unsigned long type" << std::endl;
  }

  return 0;
}

