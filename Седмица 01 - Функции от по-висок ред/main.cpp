#include <cstddef>
#include <iostream>

template <typename T, typename U> using UnaryOperation = U (*)(T);

template <typename T>
using UnaryPredicate = bool(*)(T);

template <typename T, typename U, typename S>
using BinaryOperation = S(*)(T, U);

template <typename T> bool is_fixed_point(UnaryOperation<T, T> f, T x) {
  return f(x) == x;
}

template <typename T, typename U, typename S>
auto composition(UnaryOperation<T, U> f, UnaryOperation<U, S> g) {
  return [f, g](T x) { return g(f(x)); };
}

template <typename T> auto derivative(UnaryOperation<T, T> f) {
  constexpr T EPSILON = 1e-6; // 0.000001
  return [f, EPSILON](T x) { return (f(x) - f(x + EPSILON)) / -EPSILON; };
}

template <typename T> void print(T arr[], std::size_t n) {
  for (std::size_t i = 0; i < n; ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';
}

template <typename T, typename U>
U *map(UnaryOperation<T, U> f, const T *arr, std::size_t n) {
  U *result = new U[n];

  for (std::size_t i = 0; i < n; ++i) {
    result[i] = f(arr[i]);
  }

  return result;
}

template <typename T>
T* filter(UnaryPredicate<T> pred, const T* arr, std::size_t n) {
  T* result = new T[n];

  std::size_t index = 0;
  for(std::size_t i = 0; i < n; ++i) {
    if(pred(arr[i])) {
      result[index++] = arr[i];
    }
  }

  return result;
}

template <typename T, typename U>
U reduce(BinaryOperation<T, U, U> acc, U nv, const T* arr, std::size_t n) {
  if(n == 0) {
    return acc(arr[n], nv);
  }

  --n;
  return acc(arr[n], reduce(acc, nv, arr, n));
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  std::cout << reduce<int, int>([](int curr, int res){
      return res * curr;
  }, 1, arr, 5) << '\n'; // -> 120
  return 0;
}