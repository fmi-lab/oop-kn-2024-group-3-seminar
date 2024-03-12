#include <iostream>
#include "polynomial.hpp"

int main() {
  Polynomial polynomial;

  polynomial
    .add_coefficient(2)
    .add_coefficient(3)
    .add_coefficient(1);

  std::cout << polynomial << " == " << polynomial(3) << '\n';


  return 0;
}