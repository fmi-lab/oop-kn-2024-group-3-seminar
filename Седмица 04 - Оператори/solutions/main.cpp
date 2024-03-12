#include <iostream>
#include "polynomial.hpp"

int main() {
  double arr[]{};
  Polynomial polynomial(arr, 3);

  // polynomial
  //   .add_coefficient(2)
  //   .add_coefficient(3)
  //   .add_coefficient(1);

  std::cout << polynomial << " == " << polynomial(3) << '\n';


  return 0;
}