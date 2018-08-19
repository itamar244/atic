#pragma once

#include <cassert>
#include <utility>

namespace atic {

template<typename T>
struct Node {
  T value;
  Node* next;

  Node(T value, Node* next = nullptr) : value(value), next(next) {}
};

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

} // namespace atic
