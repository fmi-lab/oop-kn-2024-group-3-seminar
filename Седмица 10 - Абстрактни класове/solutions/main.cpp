#include <iostream>

class Base {
public:
  virtual void print() const = 0;
};

class FirstDerived : public Base {
public:
  void print() const final {
    std::cout << "FirstDerived::print()\n";
  }
};

class SecondDerived : public Base {
public:
  void print() const final {
    std::cout << "SecondDerived::print()\n";
  }
};

int main() {
  // Base base; // -> compile time error
  FirstDerived fd;
  SecondDerived sd;

  fd.print(); // -> FirstDerived::print()
  sd.print(); // -> SecondDerived::print()
  return 0;
}