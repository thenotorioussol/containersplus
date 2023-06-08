#ifndef S21_CONTAINERS_SRC_S21_STACK_H_
#define S21_CONTAINERS_SRC_S21_STACK_H_

#include <iostream>

#include "s21_vector.h"

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() : container_() {}

  stack(std::initializer_list<value_type> const &items) : container_(items) {}

  stack(const stack &s) : container_(s.container_) {}

  stack(stack &&s) noexcept : container_(std::move(s)) {}

  ~stack() { container_.clear(); }

  stack &operator=(stack &&s) noexcept {
    container_ = std::move(s.container_);
    return *this;
  }

  stack &operator=(const stack &s) {
    container_ = s.container_;
    return *this;
  }

  const_reference top() const { return container_.back(); }

  bool empty() const { return container_.empty(); }

  size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_back(); }

  void swap(stack &other) { container_.swap(other.container_); }

 private:
  s21::vector<value_type> container_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_STACK_H_
