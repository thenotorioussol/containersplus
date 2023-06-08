#ifndef S21_CONTAINERS_SRC_S21_VECTOR_H_
#define S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <cstdio>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace s21 {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator [[maybe_unused]] = const T *;
  using size_type = std::size_t;

 private:
  size_type size_;
  size_type capacity_;
  value_type *array_;

 public:
  vector() : size_(0U), capacity_(size_), array_(new value_type[capacity_]) {}

  explicit vector(size_type n)
      : size_(n), capacity_(size_), array_(new value_type[capacity_]) {}

  vector(const vector &v)
      : size_(v.size_), capacity_(size_), array_(new value_type[capacity_]) {
    for (size_type i = 0U; i < v.size_; ++i) {
      array_[i] = v.array_[i];
    }
  }

  vector(std::initializer_list<value_type> const &items)
      : size_(items.size()),
        capacity_(size_),
        array_(new value_type[capacity_]) {
    for (size_type i = 0U; i < items.size(); ++i) {
      array_[i] = items.begin()[i];
    }
  }

  vector(vector &&v) noexcept
      : size_(v.size_), capacity_(size_), array_(v.array_) {
    v.size_ = 0;
    v.capacity_ = 0;
    v.array_ = new value_type[0U];
  }

  vector &operator=(vector &&v) noexcept {
    size_ = v.size_;
    v.size_ = 0;

    capacity_ = v.capacity_;
    v.capacity_ = 0;

    delete[] array_;
    array_ = v.array_;
    v.array_ = new value_type[0U];

    return *this;
  }
  ~vector() { delete[] array_; }

  [[nodiscard]] const_reference front() const noexcept { return array_[0]; }

  [[nodiscard]] const_reference back() const noexcept {
    return array_[size_ - 1U];
  }

  [[nodiscard]] reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Out of array range");
    }

    return array_[pos];
  }

  [[nodiscard]] reference operator[](size_type pos) { return array_[pos]; }

  [[nodiscard]] iterator data() noexcept { return array_; }

  [[nodiscard]] iterator begin() noexcept { return array_; }

  [[nodiscard]] iterator end() noexcept { return array_ + size_; }

  [[nodiscard]] bool empty() const noexcept { return size_ == 0U; }

  [[nodiscard]] size_type size() const noexcept { return size_; }

  [[nodiscard]] size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2U;
  }

  void reserve(size_type size) {
    if (size > capacity_) {
      auto new_array = new value_type[size];
      for (size_type i = 0U; i < size_ && i < size; ++i) {
        new_array[i] = std::move(array_[i]);
      }
      delete[] array_;

      array_ = std::move(new_array);
      capacity_ = size;
    }
  }

  [[nodiscard]] size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (size_ != capacity_) {
      auto new_array = new value_type[size_];
      for (size_type i = 0U; i < size_; ++i) {
        new_array[i] = std::move(array_[i]);
      }
      delete[] array_;

      array_ = std::move(new_array);
      capacity_ = size_;
    }
  }

  void clear() noexcept { size_ = 0U; }

  iterator insert(iterator pos, const_reference value) {
    size_type shift = std::distance(array_, pos);
    auto new_array = create_space(shift, shift + 1U);
    new_array[shift] = value;
    if (new_array != array_) {
      delete[] array_;
      array_ = new_array;
    }
    return array_ + shift;
  }

  void erase(iterator pos) noexcept {
    for (auto i = pos; i != end(); ++i) {
      auto next = i + 1U;

      if (next != end()) {
        *i = std::move(*next);
      }
    }
    if (size_ > 0U) {
      --size_;
    }
  }

  void push_back(const_reference value) {
    auto new_array = create_space(size_, size_ + 1U);
    new_array[size_ - 1U] = value;
    if (array_ != new_array) {
      delete[] array_;
      array_ = new_array;
    }
  }

  void pop_back() noexcept {
    if (size_ > 0U) {
      --size_;
    }
  }

  void swap(vector &other) noexcept {
    std::swap(array_, other.array_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    size_type shift = pos - array_;
    size_type copy_shift = shift;
    auto new_array = create_space(shift, shift + sizeof...(args));
    for (auto &&item : {std::forward<Args>(args)...}) {
      new_array[shift++] = std::move(item);
    }
    if (array_ != new_array) {
      delete[] array_;
      array_ = new_array;
    }
    return array_ + copy_shift;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    emplace(end(), args...);
  }

 private:
  value_type *create_space(size_type pos_a, size_type pos_b) {
    size_type new_size = size_ + pos_b - pos_a;
    auto new_array = array_;
    if (new_size > capacity_) {
      if (capacity_ == 0U) {
        capacity_ = new_size;
        new_array = new value_type[capacity_];
      } else {
        while (new_size > capacity_) {
          capacity_ *= 2U;
        }
        new_array = new value_type[capacity_];
      }

      for (size_type i = 0U; i < pos_a; ++i) {
        new_array[i] = std::move(array_[i]);
      }
    }
    size_ = new_size;

    for (auto i = new_size - 1U; i >= pos_b; --i) {
      new_array[i] = std::move(array_[pos_a + i - pos_b]);
    }

    return new_array;
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_VECTOR_H_