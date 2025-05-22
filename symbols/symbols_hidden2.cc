#include <iostream>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#define HIDE __declspec(dllimport)
#else
#define EXPORT __attribute__((visibility("default")))
#define HIDE __attribute__((visibility("hidden")))
#endif

int inc = 0;
int open = 0;

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

//__attribute__((visibility("hidden"))) void public_function() {
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

