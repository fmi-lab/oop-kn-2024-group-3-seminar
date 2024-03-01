#include "rational.hpp"
#include <algorithm>
#include <iostream>
#include <type_traits>

Rational::Rational(int numerator, int denominator)
    : numerator(numerator), denominator(1) {
  setDenominator(denominator);
  simplify();
}

int Rational::getNumerator() const { return numerator; }

int Rational::getDenominator() const { return denominator; }

void Rational::setNumerator(int n) { 
  numerator = n; 
  simplify();
}

void Rational::setDenominator(int n) {
  if (n != 0) {
    denominator = n;
    simplify();
  }
}

void Rational::simplify() {
  int gcd = find_gcd();

  numerator /= gcd;
  denominator /= gcd;
}

int Rational::find_gcd() const {
  int max = std::max(numerator, denominator);
  int min = std::min(numerator, denominator);

  while (max % min != 0) {
    max %= min;
    std::swap(max, min);
  }

  return min;
}