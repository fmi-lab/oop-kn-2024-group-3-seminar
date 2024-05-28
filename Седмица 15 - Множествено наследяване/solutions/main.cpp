#include <exception>
#include <iostream>
#include <stdexcept>

class NegativeNumberException : public std::invalid_argument {
public:
  NegativeNumberException(const std::string& message) 
  : std::invalid_argument(message) {}

  const char* what() const noexcept final {
    return message.c_str();
  }

private:
  std::string message;
};

int main() {
  int a, b;
  std::cin >> a >> b;

  try {
    int* p = new int(7);

    if(a < 0 || b < 0) {
      delete p;
      throw NegativeNumberException("numbers cannot be negative");
    }

    std::cout << a / b << '\n';  
  } catch (int a) {
    std::cout << "I threw " << a << '\n';
  } catch (const std::exception& e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}