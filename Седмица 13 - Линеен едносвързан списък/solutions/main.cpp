#include <cstddef>
#include <iostream>

template <typename T> class LinkedList {
public:
  LinkedList() : first(nullptr), size(0) {}
  LinkedList(const LinkedList &other) : size(other.size) {
    copy(first, other);
  }

  ~LinkedList() {
    if (!first) {
      return;
    }

    Node *next = first->next;
    while (next) {
      delete first;
      first = next;
      next = first->next;
    }
    delete first;
  }

  LinkedList<T> operator=(const LinkedList &other) {
    LinkedList copy(other);
    swap(copy);

    return *this;
  }

  void swap(LinkedList &other) {
    using std::swap;

    swap(size, other.size);
    swap(first, other.first);
  }

  void insert_first(const T &element) {
    if (!first) {
      first = new Node(element, nullptr);
      size++;
      return;
    }

    first = new Node(element, first);
    size++;
  }

  void insert_last(const T &element) {
    if (!first) {
      first = new Node(element, nullptr);
      size++;
      return;
    }

    Node *iter = first;
    while (iter->next) {
      iter = iter->next;
    }

    iter->next = new Node(element, nullptr);
    size++;
  }

  void append(const LinkedList<T> &other) {
    Node *this_iter = first;
    while (this_iter->next) {
      this_iter = this_iter->next;
    }

    copy(this_iter->next, other);
  }

  void remove_first() {
    if(!first) {
      first = nullptr;
      return;
    }

    Node* next = first->next;
    delete first;
    first = next;
    --size;
  }

  void reverse() {
    if(!first) {
      return;
    }

    Node* prev = nullptr, *next;
  
    while (first->next) {
      next = first->next;
      first->next = prev;
      prev = first;
      first = next;
    }

    first->next = prev;
  }

  void print() const {
    Node *iter = first;

    while (iter) {
      std::cout << iter->data << ' ';
      iter = iter->next;
    }
    std::cout << '\n';
  }

private:
  struct Node {
    Node(const T &data, Node *next) : data(data), next(next) {}

    T data;
    Node *next;
  };

  Node *first;
  std::size_t size;

  void copy(Node *&current, const LinkedList& other) {
    if (other.size == 0) {
      current = nullptr;
      return;
    }

    current = new Node(other.first->data, nullptr);

    Node *other_iter = other.first->next, *this_iter = current;
    while (other_iter != nullptr) {
      this_iter->next = new Node(other_iter->data, nullptr);
      this_iter = this_iter->next;
      other_iter = other_iter->next;
    }
  }
};

int main() {
  LinkedList<int> list;
  list.insert_first(1);
  list.remove_first();
  list.insert_first(4);
  list.insert_first(3);
  list.insert_first(5);

  LinkedList<int> list2(list);
  list2.print();

  LinkedList<int> list3;
  list3.insert_last(6);
  list3.insert_last(7);
  list3.insert_last(8);
  list3.print();

  list2.append(list3);
  list2.print();

  list3 = list;

  list3.reverse();
  list3.print();
  return 0;
}