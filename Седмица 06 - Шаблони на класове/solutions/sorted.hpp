#ifndef SORTED_HPP
#define SORTED_HPP

#include <cstddef>
#include <functional>

template <typename T>
class Sorted {
public:
  Sorted(const T arr[] = nullptr, std::size_t size = 0);
  Sorted(const Sorted&);
  Sorted<T> operator=(const Sorted&);
  ~Sorted();

  void swap(Sorted&);
  void add(const T&) noexcept;
  void remove(const T&) noexcept;

  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

  std::size_t length() const {
    return size;
  }

  Sorted<T> filter(const std::function<bool(const T&)>&) const;

  template <typename U>
  Sorted<U> map(const std::function<U(const T&)>&) const;

  bool search(const T&) const noexcept;

private:
  T* data;
  std::size_t size, capacity;

  void resize();
};

template <typename T>
Sorted<T>::Sorted(const T arr[], std::size_t size)
  : size(0),
    capacity(size),
    data(new T[size]) {
  for(std::size_t i = 0; i < size; ++i) {
    add(arr[i]);
  }
}

template <typename T>
Sorted<T>::Sorted(const Sorted& other)
  : size(other.size),
    capacity(other.capacity),
    data(new T[other.capacity]) {
  for(std::size_t i = 0; i < other.size; ++i) {
    data[i] = other.data[i];
  }
}

template <typename T>
Sorted<T> Sorted<T>::operator=(const Sorted& other) {
  Sorted<T> copy(other);
  swap(copy);

  return *this;
}

template <typename T>
Sorted<T>::~Sorted() {
  delete[] data;
}

template <typename T>
void Sorted<T>::swap(Sorted& other) {
  using std::swap;

  swap(size, other.size);
  swap(capacity, other.capacity);
  swap(data, other.data);
}

template <typename T>
void Sorted<T>::add(const T& element) noexcept {
  if(size == capacity) {
    resize();
  }

  data[size++] = element;

  for(int i = size - 2; i >= 0 && data[i] > element; --i) {
    std::swap(data[i], data[i+1]);
  }
}

template <typename T>
void Sorted<T>::remove(const T& element) noexcept {
  std::size_t index = 0;

  while(index < size && data[index] != element) {
    ++index;
  }

  for(std::size_t i = index; i < size - 1; ++i) {
    std::swap(data[i], data[i+1]);
  }

  --size;
}

template <typename T>
T& Sorted<T>::operator[](std::size_t index) {
  return data[index];
}

template <typename T>
const T& Sorted<T>::operator[](std::size_t index) const {
  return data[index];
}

template <typename T>
Sorted<T> Sorted<T>::filter(
  const std::function<bool(const T&)>& predicate
) const {
  Sorted<T> result;

  for(std::size_t i = 0; i < size; ++i) {
    if(predicate(data[i])) {
      result.add(data[i]);
    }
  }

  return result;
}

template <typename T>
template <typename U>
Sorted<U> Sorted<T>::map(const std::function<U(const T&)>&) const {

}

template <typename T>
bool Sorted<T>::search(const T&) const noexcept {

}

template <typename T>
void Sorted<T>::resize() {
  if(capacity == 0) {
    capacity += 1;
  }

  T* newData = new T[capacity *= 2];
  for(std::size_t i = 0; i < size; ++i) {
    newData[i] = data[i];
  }

  delete[] data;
  data = newData;
}

#endif