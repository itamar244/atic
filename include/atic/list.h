#pragma once

#include <cstdlib>
#include "atic/node.h"

namespace atic {

template<typename T>
class List {
  using Node = Node<T>;
public:
  using value_type = T;
  using iterator = NodeIterator<T>;
  using const_iterator = NodeConstIterator<T>;

  List() {}

  List(const List& list) : size_(list.size_) {
    auto pair = CopyNode(list.first_);
    first_ = pair.first;
    last_ = pair.second;
  }

  List(List&& list)
      : size_(list.size_), first_(list.first_), last_(list.last_) {
    list.size_ = 0;
    list.first_ = list.last_ = nullptr;
  }

  ~List() {
    DeleteNode(first_);
  }

  inline std::size_t size() const { return size_; }
  inline iterator begin() { return {first_}; }
  inline iterator end() { return {nullptr}; }
  inline const_iterator begin() const { return {first_}; }
  inline const_iterator end() const { return {nullptr}; }

  void push_back(T value) {
    if (!first_) {
      first_ = last_ = new Node(value);
    } else {
      last_ = last_->next = new Node(value);
    }
    ++size_;
  }

protected:
  std::size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;
};

} // namespace atic
