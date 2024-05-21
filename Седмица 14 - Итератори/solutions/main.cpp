#include "list.hpp"
#include "sorted.hpp"
#include <iostream>
#include <iterator>

int main() {
  int arr[] = {7, 3, 11, 38, 9, 6};
  Sorted<int> vector(arr, 6);

  for (int x : vector) {
    std::cout << x << '\n';
  }

  std::cout << '\n';

  auto begin = std::rbegin(vector);
  auto end = std::rend(vector);
  for (; begin != end; ++begin) {
    int x = *begin;
    std::cout << x << ' ';
  }

  std::cout << '\n';

  LinkedList<int> list;
  list.insert_first(1);
  list.insert_first(4);
  list.insert_first(3);
  list.insert_first(5);

  auto list_begin = std::begin(list);
  for (int i = 0; i < 1; ++i) {
    ++list_begin;
  }

  list.remove_at(list_begin);

  list.print();

  return 0;
}