#ifndef S21_CONTAINERS_SRC_S21_SET_H_
#define S21_CONTAINERS_SRC_S21_SET_H_

#include <cstdio>
#include <initializer_list>

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {

template <class Key>
class set : public tree<Key> {
 private:
  using tree<Key>::tree;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree<key_type>::TreeIterator;
  using const_iterator = typename tree<value_type>::TreeIteratorConst;
  using size_type = std::size_t;

 public:
  set(std::initializer_list<value_type> const &items) : set() {
    for (value_type value : items) {
      insert(value);
    }
  }

  std::pair<iterator, bool> insert(const value_type &value) override {
    return tree<key_type>::auto_insert(value, false);
  }

  void merge(set &other) { merge_set(other, other.ret_root()); }

 protected:
  void merge_set(set &other, typename tree<key_type>::TreeNode *item) {
    if (item->right_elem_) merge_set(other, item->right_elem_);
    if (item->left_elem_) merge_set(other, item->left_elem_);
    auto result = insert(item->value_);
    if (result.second) {
      auto iter = iterator(item);
      other.erase(iter);
    }
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_SET_H_