// Online C++ compiler to run C++ program online
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

int main() {
  Base* ptr = new Derived;
  ptr->whoami();  // Prints "I am Base" (static binding)

  if (typeid(*ptr) == typeid(Derived)) {
    static_cast<Derived*>(ptr)->whoami();  // Prints "I am Derived" (dynamic binding)
  }
  void* p = ptr;
  //Base* p1 = dynamic_cast<Base*>(p);
  Derived* derivedObj = new Derived;
  void* voidPtr = derivedObj;
  Base* basePtr = dynamic_cast<Base*>(voidPtr);
  if (basePtr) {
    // Cast successful, basePtr points to the Derived object
  } else {
    // Cast failed (shouldn't happen here)
  }
  delete derivedObj;
  
  delete ptr;
  return 0;
}
