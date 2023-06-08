#ifndef S21_CONTAINERS_SRC_S21_MAP_H_
#define S21_CONTAINERS_SRC_S21_MAP_H_

#include <cstdio>
#include <initializer_list>
#include <utility>

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {

template <class Key, class T>
class map : public tree<std::pair<Key, T>> {
 private:
  using tree<std::pair<Key, T>>::tree;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename tree<value_type>::TreeIterator;
  using const_iterator = typename tree<value_type>::TreeIteratorConst;
  using size_type = std::size_t;

 public:
  map(std::initializer_list<value_type> const& items) : map() {
    for (value_type value : items) {
      insert(value.first, value.second);
    }
  }

  [[nodiscard]] mapped_type& at(const key_type& key) {
    auto sol = find_contains_map(key);
    if (!sol) throw std::out_of_range("There is no such key!");
    return sol->value_.second;
  }

  mapped_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (...) {
      value_type val = value_type(key, mapped_type());
      tree<value_type>::default_insert(val);
      return at(key);
    }
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    if (contains(key))
      return std::make_pair(iterator(this->find_contains_map(key)), false);
    iterator iter = tree<value_type>::default_insert(std::make_pair(key, obj));
    return std::make_pair(iter, true);
  }

  std::pair<iterator, bool> insert(const value_type& value) override {
    return insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    typename tree<value_type>::TreeNode* a = find_contains_map(key);
    if (a) {
      a->value_ = std::make_pair(key, obj);
      return std::make_pair(iterator(a), true);
    }
    iterator iter = tree<value_type>::default_insert(std::make_pair(key, obj));
    return std::make_pair(iter, true);
  }
  void merge(map& other) { merge_map(other, other.ret_root()); }

  [[nodiscard]] bool contains(const key_type& key) noexcept {
    return find_contains_map(key);
  }

 private:
  typename tree<value_type>::TreeNode* find_contains_map(
      const key_type& key) noexcept {
    if (this->empty()) return nullptr;
    auto* current = tree<value_type>::ret_root();
    while (true) {
      if (current == nullptr) {
        return nullptr;
      } else if (current->value_.first == key) {
        return current;
      } else if (current->value_.first > key) {
        current = current->left_elem_;
      } else {
        current = current->right_elem_;
      }
    }
  }

  void merge_map(map& other, typename tree<value_type>::TreeNode* item) {
    if (item->right_elem_) merge_map(other, item->right_elem_);
    if (item->left_elem_) merge_map(other, item->left_elem_);
    auto result = insert(item->value_);
    if (result.second) {
      auto iter = iterator(item);
      other.erase(iter);
    }
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_MAP_H_