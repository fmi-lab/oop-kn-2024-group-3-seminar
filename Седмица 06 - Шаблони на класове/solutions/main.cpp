#include "sorted.hpp"
#include <iostream>
#include <ostream>

int main() {
  int arr[] = {7, 3, 11, 38, 9, 6};
  Sorted<int> vector(arr, 6);

  for(std::size_t i = 0; i < vector.length(); ++i) {
    std::cout << vector[i] << ' ';
  }

  std::cout << '\n';
  return 0;
}