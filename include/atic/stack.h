#pragma once

#include <cassert>
#include <utility>
#include "atic/node.h"

namespace atic {

template<typename Node>
std::pair<Node*, Node*> CopyNode(const Node* node) {
  if (node == nullptr) return {nullptr, nullptr};
  Node* copy = new Node(node->value);
  Node* cur = copy;

  node = node->next;
  while (node != nullptr) {
    cur = cur->next = new Node(node->value);
    node = node->next;
  }

  return {copy, cur};
}

template<typename Node>
inline void DeleteNode(Node* node) {
  while (node) {
    auto next = node->next;
    delete node;
    node = next;
  }
}

template<typename T>
struct Node {
  T value;
  Node* next;

  Node(T value, Node* next = nullptr) : value(value), next(next) {}
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

  inline void push_front(T value) {
    head_ = new Node<T>(value, head_);
  }

private:
  Node<T>* head_;
};

} // namespace atic
