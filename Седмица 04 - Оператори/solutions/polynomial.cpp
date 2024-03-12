#include "polynomial.hpp"
#include <cmath>
#include <cstddef>
#include <optional>

Polynomial::Polynomial(double* coefficients, std::size_t size)
  : coefficients(new double[size]{}),
    degree(size - 1),
    capacity(size) {
  for(std::size_t i = 0; i < size; ++i) {
    this->coefficients[i] = coefficients[i];
  }
}

Polynomial::Polynomial(const Polynomial& other)
  : coefficients(new double[other.capacity]{}),
    degree(other.degree),
    capacity(other.capacity) {
  for(std::size_t i = 0; i < other.degree + 1; ++i) {
    coefficients[i] = other.coefficients[i];
  }
}

Polynomial::~Polynomial() {
  delete[] coefficients; 
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
  Polynomial copy(other);
  swap(copy);

  return *this;
}

void Polynomial::swap(Polynomial& other) {
  using std::swap;

  swap(coefficients, other.coefficients);
  swap(degree, other.degree);
  swap(capacity, other.capacity);
}

Polynomial& Polynomial::add_coefficient(double coefficient) {
  if(degree + 1 == capacity) {
    resize();
  }

  coefficients[++degree] = coefficient;

  return *this;
}

Polynomial& Polynomial::remove_coefficient(std::size_t position) {
  for(std::size_t i = position; i < degree; ++i) {
    coefficients[i] = coefficients[i + 1];
  }

  return *this;
}

double Polynomial::operator()(double x) const {
  unsigned n = 0;

  return reduce_iter([x, &n](double result, double element){
    return result + element * std::pow(x, n++);
  }, 0, coefficients, degree + 1);
}

double Polynomial::operator[](std::size_t) const {

}

double& Polynomial::operator[](std::size_t) {

}

std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial) {
  for(int i = polynomial.degree; i >= 1; --i) {
    os << polynomial.coefficients[i] << " * x^" << i << " + ";
  }
  os << polynomial.coefficients[0] << '\n';

  return os;
}

void Polynomial::resize() {
  if(capacity == 0) {
    capacity = 1;
  }

  double* new_coefficients = new double[capacity * 2]{};
  for(std::size_t i = 0; i < degree + 1; ++i) {
    new_coefficients[i] = coefficients[i];
  }

  delete[] coefficients;
  coefficients = new_coefficients;
  capacity *= 2;
}
