#ifndef S21_CONTAINERS_SRC_S21_LIST_H_
#define S21_CONTAINERS_SRC_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <utility>

namespace s21 {
template <class T>
class list {
 private:
  class ListNode;
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = const ListIterator;
  using size_type = size_t;

  list() {
    size_ = 0;
    begin_ = new ListNode(value_type());
    end_ = begin_;
    begin_->prev = nullptr;
    begin_->next = nullptr;
  }

  explicit list(size_type n) {
    size_ = 0;
    begin_ = new ListNode(value_type());
    end_ = begin_;
    begin_->prev = nullptr;
    begin_->next = nullptr;
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const &items) {
    begin_ = new ListNode(value_type());
    end_ = begin_;
    begin_->prev = nullptr;
    begin_->next = nullptr;
    size_ = 0;
    for (value_type i : items) {
      push_back(i);
    }
  }

  list(const list &other) {
    begin_ = new ListNode(value_type());
    end_ = begin_;
    begin_->prev = nullptr;
    begin_->next = nullptr;
    size_ = 0;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  }

  list(list &&other) {
    size_ = other.size();
    begin_ = std::move(other.begin_);
    end_ = std::move(other.end_);
    begin_ = nullptr;
    end_ = nullptr;
    other.size_ = 0;
  }

  ~list() {
    deleteNodes();
    begin_ = nullptr;
    end_ = nullptr;
    size_ = 0;
  }

  list &operator=(const list &other) {
    deleteNodes();
    begin_ = new ListNode(value_type());
    end_ = begin_;
    begin_->prev = nullptr;
    begin_->next = nullptr;
    size_ = 0;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
    return *this;
  }

  list &operator=(list &&other) {
    deleteNodes();
    begin_ = other.begin_;
    end_ = other.end_;
    size_ = other.size_;
    other.size_ = 0;
    other.begin_ = nullptr;
    other.end_ = nullptr;
    return *this;
  }

  const_reference front() const { return begin_->value; }
  const_reference back() const { return end_->value; }
  iterator begin() const { return ListIterator(begin_); }
  iterator end() const { return ListIterator(end_); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return m_size_; }

  void clear() {
    while (begin_ != end_) {
      ListNode *tmp = begin_->next;
      delete begin_;
      begin_ = tmp;
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    if (size_ != m_size_) {
      ListNode *new_node = new ListNode(value);
      insertBefore(pos.ptr_, new_node);
      size_++;
    }
    return pos;
  }

  iterator erase(iterator pos) {
    ListNode *next = pos.ptr_->next;
    ListNode *prev = pos.ptr_->prev;
    if (pos.ptr_ == begin_) {
      begin_ = next;
    }
    delete pos.ptr_;
    pos.ptr_ = nullptr;
    if (next != nullptr) {
      next->prev = prev;
    }
    if (prev != nullptr) {
      prev->next = next;
    }
    size_--;
    return iterator(next);
  }

  void push_back(const_reference value) {
    if (size_ != m_size_) {
      insert(end(), value);
    }
    end_->value = value;
  }

  void pop_back() { erase(iterator(end_->prev)); }

  void push_front(const_reference value) {
    if (size_ != m_size_) {
      insert(begin(), value);
    }
  }

  void pop_front() { erase(iterator(begin_)); }

  void swap(list &other) {
    size_ = std::exchange(other.size_, size_);
    begin_ = std::exchange(other.begin_, begin_);
    end_ = std::exchange(other.end_, end_);
  }

  void merge(list &other) {
    if (&other != this) {
      iterator it = begin();
      iterator other_it = other.begin();
      while (it != end() && other_it != other.end()) {
        if (*other_it <= *it) {
          auto tmp_it = other_it;
          ++other_it;
          insertBefore(it.ptr_, tmp_it.ptr_);
        } else {
          ++it;
        }
      }
      while (other_it != other.end()) {
        auto tmp_it = other_it;
        ++other_it;
        insertBefore(end_, tmp_it.ptr_);
      }
    }
    size_ += other.size_;
    other.begin_ = other.end_;
  }

  void splice(const_iterator pos, list &other) {
    ListNode *start = pos.ptr_->prev;
    ListNode *end = pos.ptr_;
    if (start != nullptr) {
      start->next = other.begin_;
    } else {
      begin_ = other.begin_;
    }
    end->prev = other.end_->prev;
    other.end_->prev->next = end;
    other.end_->prev = nullptr;

    size_ += other.size_;
    other.begin_ = other.end_;
    other.erase(other.end());
    other.size_ = 0;
  }

  void reverse() {
    if (begin_ != end_) {
      iterator it = begin();
      while (it != end()) {
        ListNode *node = it.ptr_;
        ++it;
        node->prev = std::exchange(node->next, node->prev);
      }
      begin_->next = end_;
      end_->prev = std::exchange(begin_, end_->prev);
    }
  }

  void unique() {
    iterator it = begin();
    iterator end = --(this->end());
    while (it != end) {
      if (it.ptr_->value == it.ptr_->next->value) {
        it = erase(it);
      } else {
        ++it;
      }
    }
  }

  void sort() {
    end_->prev->next = nullptr;
    mergeSort(&begin_);
    ListNode *cur = begin_;
    while (cur->next != nullptr) {
      cur = cur->next;
    }
    cur->next = end_;
    end_->prev = cur;
  }

 private:
  void mergeSort(ListNode **headRef) {
    ListNode *head = *headRef;
    ListNode *start;
    ListNode *mid;

    if (head == nullptr || head->next == nullptr) {
      return;
    }

    frontBackSplit(head, &start, &mid);

    mergeSort(&start);
    mergeSort(&mid);

    *headRef = sortedMerge(start, mid);
  }

  void frontBackSplit(ListNode *source, ListNode **frontRef,
                      ListNode **backRef) {
    ListNode *fast = source->next;
    ListNode *slow = source;

    while (fast != nullptr) {
      fast = fast->next;
      if (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
      }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
  }

  ListNode *sortedMerge(ListNode *node1, ListNode *node2) {
    ListNode *result = nullptr;

    if (node1 == nullptr) {
      return node2;
    } else if (node2 == nullptr) {
      return node1;
    }

    if (node1->value < node2->value) {
      result = node1;
      ListNode *next = sortedMerge(node1->next, node2);
      result->next = next;
      next->prev = result;
    } else {
      result = node2;
      ListNode *next = sortedMerge(node1, node2->next);
      result->next = next;
      next->prev = result;
    }
    return result;
  }

  void deleteNodes() {
    while (begin_ != nullptr) {
      ListNode *tmp = begin_->next;
      delete begin_;
      begin_ = tmp;
    }
  }

  void insertBefore(ListNode *pos, ListNode *node) {
    ListNode *tmp = pos->prev;
    node->prev = std::exchange(pos->prev, node);
    node->next = pos;
    if (tmp != nullptr) {
      tmp->next = node;
    }
    if (pos == begin_) {
      begin_ = node;
    }
  }

  class ListNode {
   public:
    ListNode(T val) { this->value = val; }
    ~ListNode() {
      next = nullptr;
      prev = nullptr;
    }
    T value;
    ListNode *next;
    ListNode *prev;
  };

  class ListIterator {
   public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using const_reference = const T &;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    friend class list;

   private:
    ListNode *ptr_;

   public:
    ListIterator(ListNode *ptr) { ptr_ = ptr; }
    ListIterator(const ListIterator &other) { ptr_ = other.ptr_; }
    ~ListIterator() { ptr_ = nullptr; }
    ListIterator operator++() {
      ptr_ = ptr_->next;
      return *this;
    }
    ListIterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    ListIterator operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }
    reference operator*() { return ptr_->value; }
    friend bool operator==(ListIterator it1, ListIterator it2) {
      return it1.ptr_ == it2.ptr_;
    }
    friend bool operator!=(ListIterator it1, ListIterator it2) {
      return it1.ptr_ != it2.ptr_;
    }
    ListIterator &operator=(const ListIterator &other) {
      ptr_ = other.ptr_;
      return *this;
    }
  };
  size_type size_;
  size_type m_size_ = std::numeric_limits<size_type>::max();
  ListNode *begin_;
  ListNode *end_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_LIST_H_
