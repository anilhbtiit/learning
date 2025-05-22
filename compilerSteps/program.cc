#include <iostream>

int inc = 0;

class symbol {
  public:
  symbol() { mVal = 1; }
  ~symbol() {}
  int getInc() { return inc; }
  int getVal() { return mVal; }
  private:
  int mVal;
};


void internal_function() {
    inc++;
    std::cout << "Internal function called\n";
}

void public_function() {
    inc++;
    std::cout << "Public function called\n";
}

static void static_function() {
    inc++;
    std::cout << "Static function called\n";
}

int
main() {
  int val = 0;
  static int ret = 0;
  internal_function();
  public_function();
  static_function();
  inc++;
  std::cout << "inc: " << inc;
  symbol sym;
  std::cout << "symbol::mVal = " << sym.getVal();
}

