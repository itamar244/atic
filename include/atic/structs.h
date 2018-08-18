#pragma once

#include <cassert>

namespace atic {

template<typename Node>
Node* __CopyNode(const Node* node) {
  if (node == nullptr) return nullptr;
  Node* copy = new Node(node->value), cur = copy;

  node = node->next;
  while (node != nullptr) {
    cur = cur->next = new Node(node->value);
    node = node->next;
  }

  return copy;
}

template<typename T>
struct __Node {
  T value;
  __Node* next;

  __Node(T value, __Node* next = nullptr) : value(value), next(next) {}
};

template<typename T>
class Stack {
public:
  Stack() : head_(nullptr) {}

  ~Stack() {
    while (head_ != nullptr) {
      auto* next = head_->next;
      delete head_;
      head_ = next;
    }
  }

  Stack(const Stack& stack) : head_(__CopyNode(stack.head_)) {}

  Stack(Stack&& stack) : head_(stack.head_) {
    stack.head_ = nullptr;
  }

  inline T& head() {
    assert(head_ != nullptr);
    return head_->value;
  }

  inline bool empty() {
    return head_ == nullptr;
  }

  inline T pop() {
    T value = head();
    auto next = head_->next;

    delete head_;
    head_ = next;
    return value;
  }

  inline void push_front(T value) {
    head_ = new __Node<T>(value, head_);
  }

private:
  __Node<T>* head_;
};

} // namespace atic
