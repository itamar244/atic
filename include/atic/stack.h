#pragma once

#include <cassert>
#include <utility>
#include "atic/node.h"

namespace atic {

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

  Stack(const Stack& stack) : head_(CopyNode(stack.head_)->first) {}

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

  inline void push(T value) {
    head_ = new Node<T>(value, head_);
  }

private:
  Node<T>* head_;
};

} // namespace atic
