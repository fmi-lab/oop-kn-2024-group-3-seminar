#include <iostream>

template <typename T>
class UniquePointer {
public:
  UniquePointer(T* pointer)
    : pointer(pointer) {}
  UniquePointer(const UniquePointer&) = delete;
  UniquePointer(UniquePointer&& other)
    : pointer(other.pointer) {
    other.pointer = nullptr;
  }
  UniquePointer<T>& operator=(const UniquePointer&) = delete;
  UniquePointer<T>& operator=(UniquePointer&& other) {
    UniquePointer<T> copy(std::move(other));
    std::swap(pointer, copy.pointer);
    return *this;
  }
  ~UniquePointer() { delete pointer; }

  T& operator*() {
    return *pointer;
  }

  const T& operator*() const {
    return *pointer;
  }

  T* operator->() {
    return pointer;
  }

  const T* operator->() const {
    return pointer;
  }

private:
  T* pointer;
};

int main() {
  UniquePointer<std::string> p(new std::string("Hello"));
  std::cout << *p << '\n';
  std::cout << p->at(0) << '\n';

  UniquePointer<std::string> q = std::move(p);

  return 0;
}