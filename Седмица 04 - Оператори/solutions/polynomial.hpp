#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <cstddef>
#include <ostream>

class Polynomial {
public:
  Polynomial(double * = nullptr, std::size_t = 0);
  Polynomial(const Polynomial &);
  ~Polynomial();
  Polynomial &operator=(const Polynomial &);

  void swap(Polynomial &);

  Polynomial &add_coefficient(double);
  Polynomial &remove_coefficient(std::size_t);

  double operator()(double) const;
  double operator[](std::size_t) const;
  double &operator[](std::size_t);

  Polynomial operator+(const Polynomial &) const;
  Polynomial operator-(const Polynomial &) const;
  Polynomial &operator+=(const Polynomial &);
  Polynomial &operator-=(const Polynomial &);

  Polynomial operator*(double) const;
  Polynomial operator/(double) const;
  Polynomial &operator*=(double);
  Polynomial &operator/=(double);

  bool operator==(const Polynomial &) const;
  bool operator!=(const Polynomial &) const;

  friend std::ostream &operator<<(std::ostream &, const Polynomial &);

private:
  double *coefficients;
  std::size_t degree, capacity;

  void resize();
};

template <typename T, typename U, typename BinaryOperation>
U reduce_iter(BinaryOperation acc, U nv, const T *arr, std::size_t n) {
  for (size_t i = 0; i < n; i++) {
    nv = acc(nv, arr[i]);
  }

  return nv;
}

template <typename T, typename U = double, typename UnaryOperation>
U* map(T* arr, std::size_t size, UnaryOperation op)
{
    U* result = new U[size];
    for (size_t i = 0; i < size; i++)
    {
        result[i] = op(arr[i]);
    }
    
    return result;
}

#endif