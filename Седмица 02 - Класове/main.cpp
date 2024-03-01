#include <iostream>
#include "rational.hpp"

int main() {
  Rational rational1(8, 2);
  Rational rational2(8, 6);
  // Rational rational1 = Rational(5, 2);

  rational1.setDenominator(4);

  std::cout << rational1.getNumerator() << ' ' << rational1.getDenominator() << '\n';
  std::cout << rational2.getNumerator() << ' ' << rational2.getDenominator() << '\n';
  return 0;
}