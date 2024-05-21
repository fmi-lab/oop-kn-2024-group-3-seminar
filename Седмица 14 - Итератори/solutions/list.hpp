#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

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
    for(const T& element : *this) {
      std::cout << element << ' ';
    }

    std::cout << '\n';
  }

private:
  struct Node {
    Node(const T &data, Node *next) : data(data), next(next) {}

    T data;
    Node *next;
  };

public:
  class Iterator {
    public:
      Iterator(Node* element) : element(element) {}

      Iterator& operator++() {
        return *this = Iterator(element->next);
      }

      bool operator!=(const Iterator& other) const {
        return element != other.element;
      }

      bool operator==(const Iterator& other) const {
        return element == other.element;
      }

      T& operator*() {
        return element->data;
      }

      const T& operator*() const {
        return element->data;
      }

      Node* node() {
        return element;
      }
    private:
      Node* element;
  };

  Iterator begin() const {
    return Iterator(first);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }

  Iterator before(const Iterator& position) const {
    Iterator begin = this->begin(), prev = Iterator(nullptr);

    while (begin != position) {
      prev = begin;
      ++begin;
    }

    return prev;
  }

  void insert_after(const T& element, const Iterator& position) {
    if(position == nullptr) {
      insert_first(element);
      return; 
    }

    Iterator iter = position, prev = iter;
    ++iter;

    prev.node()->next = new Node(element, iter.node());
  }

  void remove_at(const Iterator& position) {
    if(position == end()) {
      return;
    }

    if(position == begin()) {
      remove_first();
      return;
    }

    Iterator prev = before(position), 
             current = Iterator(position),
             next = ++current;

    prev.node()->next = next.node();
    delete Iterator(position).node();
  }

private:
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

#endif