#ifndef S21_CONTAINERS_SRC_S21_QUEUE_H_
#define S21_CONTAINERS_SRC_S21_QUEUE_H_

#include <iostream>

#include "s21_list.h"

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() : container_() {}

  queue(std::initializer_list<value_type> const &items) : container_(items) {}

  queue(const queue &q) : container_(q.container_) {}

  queue(queue &&q) noexcept : container_(std::move(q)) {}

  ~queue() { container_.clear(); }

  queue &operator=(queue &&q) noexcept {
    container_ = std::move(q.container_);
    return *this;
  }

  queue &operator=(const queue &q) {
    container_ = q.container_;
    return *this;
  }

  const_reference front() const { return container_.front(); }

  const_reference back() const { return container_.back(); }

  bool empty() const { return container_.empty(); }

  size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_back(); }

  void swap(queue &other) { container_.swap(other.container_); }

 private:
  s21::list<value_type> container_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_QUEUE_H_
