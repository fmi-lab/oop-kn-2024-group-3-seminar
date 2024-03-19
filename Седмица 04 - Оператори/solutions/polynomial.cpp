#include "polynomial.hpp"
#include <cmath>
#include <cstddef>
#include <optional>

bool are_equal(double a, double b) {
  constexpr double EPSILON = 1e-6;

  return std::fabs(a - b) < EPSILON;
}

Polynomial::Polynomial(double *coefficients, std::size_t size)
    : coefficients(new double[size]{}), degree(size - 1), capacity(size) {
  for (std::size_t i = 0; i < size; ++i) {
    this->coefficients[i] = coefficients[i];
  }
}

Polynomial::Polynomial(const Polynomial &other)
    : coefficients(new double[other.capacity]{}), degree(other.degree),
      capacity(other.capacity) {
  for (std::size_t i = 0; i < other.degree + 1; ++i) {
    coefficients[i] = other.coefficients[i];
  }
}

Polynomial::~Polynomial() { delete[] coefficients; }

Polynomial &Polynomial::operator=(const Polynomial &other) {
  Polynomial copy(other);
  swap(copy);

  return *this;
}

void Polynomial::swap(Polynomial &other) {
  using std::swap;

  swap(coefficients, other.coefficients);
  swap(degree, other.degree);
  swap(capacity, other.capacity);
}

Polynomial &Polynomial::add_coefficient(double coefficient) {
  if (degree + 1 == capacity) {
    resize();
  }

  coefficients[++degree] = coefficient;

  return *this;
}

Polynomial &Polynomial::remove_coefficient(std::size_t position) {
  for (std::size_t i = position; i < degree; ++i) {
    coefficients[i] = coefficients[i + 1];
  }

  return *this;
}

double Polynomial::operator()(double x) const {
  unsigned n = 0;

  return reduce_iter(
      [x, &n](double result, double element) {
        return result + element * std::pow(x, n++);
      },
      0, coefficients, degree + 1);
}

double Polynomial::operator[](std::size_t position) const {
  if (position >= 0 && position <= degree) {
    return coefficients[position];
  }

  return 0;
}

double &Polynomial::operator[](std::size_t position) {
  if (position >= 0 && position <= degree) {
    return coefficients[position];
  }

  return coefficients[0];
}

Polynomial Polynomial::operator+(const Polynomial &other) const {
  Polynomial result;

  std::size_t min_degree = std::min(degree, other.degree);
  std::size_t max_degree = std::max(degree, other.degree);
  double *max_coefficients =
      degree == max_degree ? coefficients : other.coefficients;

  for (int i = 0; i < min_degree + 1; ++i) {
    result.add_coefficient(coefficients[i] + other.coefficients[i]);
  }

  for (int i = min_degree + 1; i < max_degree + 1; ++i) {
    result.add_coefficient(max_coefficients[i]);
  }

  return result;
}

Polynomial Polynomial::operator-(const Polynomial &other) const {
  return (*this) + other * (-1);
}

Polynomial& Polynomial::operator+=(const Polynomial &other) {
  return *this = *this + other;
}

Polynomial &Polynomial::operator-=(const Polynomial &other) {
  return *this += other * (-1);
}

Polynomial Polynomial::operator*(double n) const {
  Polynomial result;

  for (int i = 0; i < degree + 1; ++i) {
    result.add_coefficient(coefficients[i] * n);
  }

  return result;
}

Polynomial Polynomial::operator/(double n) const { return *this * (1 / n); }

Polynomial &Polynomial::operator*=(double n) {
  double *new_coefficients =
      map(coefficients, degree + 1,
          [n](double coefficient) { return coefficient * n; });

  delete[] coefficients;
  coefficients = new_coefficients;

  return *this;
}

Polynomial &Polynomial::operator/=(double n) { return *this *= (1 / n); }

bool Polynomial::operator==(const Polynomial &other) const {
  if (degree != other.degree) {
    return false;
  }

  double difference = coefficients[0] / other.coefficients[0];
  Polynomial polynomial = other * difference;
  for (int i = 0; i < degree + 1; ++i) {
    if (!are_equal(coefficients[i], polynomial.coefficients[i])) {
      return false;
    }
  }

  return true;
}

bool Polynomial::operator!=(const Polynomial &other) const {
  return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
  for (int i = polynomial.degree; i >= 1; --i) {
    os << polynomial.coefficients[i] << " * x^" << i << " + ";
  }
  os << polynomial.coefficients[0] << '\n';

  return os;
}

void Polynomial::resize() {
  if (capacity == 0) {
    capacity = 1;
  }

  double *new_coefficients = new double[capacity * 2]{};
  for (std::size_t i = 0; i < degree + 1; ++i) {
    new_coefficients[i] = coefficients[i];
  }

  delete[] coefficients;
  coefficients = new_coefficients;
  capacity *= 2;
}
