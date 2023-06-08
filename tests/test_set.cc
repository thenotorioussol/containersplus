#include "test.h"

TEST(test, ConstructorsList) {
  s21::set<int> new_set;

  std::initializer_list<int> items{2, 1, 3, 4};
  s21::set<int> my_set2(items);
  std::set<int> std_set2(items);
  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, ConstructorsList2) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::set<int> my_set2(items);
  std::set<int> std_set2(items);
  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, ConstructorsCopy) {
  s21::set<int> new_set;

  std::initializer_list<int> items{2, 1, 3, 4};
  s21::set<int> my_set2(items);
  std::set<int> std_set2(items);

  s21::set<int> my_set3(my_set2);
  std::set<int> std_set3(std_set2);
  auto my_iter = my_set3.begin();
  auto std_iter = std_set3.begin();
  while (my_iter != my_set3.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, ConstructorsMove) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2 = std::move(my_set);
  std::set<int> std_set2 = std::move(std_set);

  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, ConstructorsMove2) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2 = my_set;
  std::set<int> std_set2 = std_set;

  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, IteratorTest) {
  std::initializer_list<int> items{1, 2, 3};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, IteratorTestSolo) {
  std::initializer_list<int> items{2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, IteratorTestDoubleInc) {
  std::initializer_list<int> items{1, 2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, IteratorTestDoubleDec) {
  std::initializer_list<int> items{2, 1};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, MinusIterator) {
  std::initializer_list<int> items{2, 1, 3, 34, 234, 231};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(test, MinusIteratorSolo) {
  std::initializer_list<int> items{2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(test, MinusIteratorDuo1) {
  std::initializer_list<int> items{1, 2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(test, MinusIteratorDuo2) {
  std::initializer_list<int> items{2, 1};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(test, Insert) {
  // std::initializer_list<int> items{1,5,3,2,};
  s21::set<int> my_set;
  std::set<int> std_set;
  my_set.insert(1);
  std_set.insert(1);
  my_set.insert(-1);
  std_set.insert(-1);
  my_set.insert(45);
  std_set.insert(45);
  my_set.insert(-24);
  std_set.insert(-24);
  my_set.insert(-24);
  std_set.insert(-24);
  my_set.insert(-24);
  std_set.insert(-24);
  my_set.insert(24);
  std_set.insert(24);
  my_set.insert(-24000);
  std_set.insert(-24000);
  my_set.insert(-2400);
  std_set.insert(-2400);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase1) {
  std::initializer_list<int> items{1, 5, 3, 2};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase2) {
  std::initializer_list<int> items{1, 5, 3, 4};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase3) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase4) {
  std::initializer_list<int> items{1, 5, 7, 8};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase5) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase6) {
  std::initializer_list<int> items{5, 1, 7, 6};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Erase7) {
  std::initializer_list<int> items{5};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Clear) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  my_set.clear();
  std_set.clear();
  ASSERT_TRUE(my_set.size() == 0);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Clear2) {
  s21::set<int> my_set;
  std::set<int> std_set;
  my_set.clear();
  std_set.clear();
  ASSERT_TRUE(my_set.size() == 0);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Swap) {
  std::initializer_list<int> items{1, 5, 7, 6};
  std::initializer_list<int> items2{17, 25, 57, 66, 34, 12, 5};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.swap(my_set2);
  std_set.swap(std_set2);

  ASSERT_TRUE(my_set.size() == std_set.size());
  ASSERT_TRUE(my_set2.size() == std_set2.size());

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  auto my_iter2 = my_set2.begin();
  auto std_iter2 = std_set2.begin();
  while (std_iter2 != std_set2.end()) {
    ASSERT_TRUE(*my_iter2 == *std_iter2);
    ++my_iter2;
    ++std_iter2;
  }
}

TEST(test, Find) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.find(66);
  auto std_iter = std_set.find(66);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(17);
  std_iter = std_set.find(17);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(25);
  std_iter = std_set.find(25);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(57);
  std_iter = std_set.find(57);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(34);
  std_iter = std_set.find(34);
  ASSERT_TRUE(*my_iter == *std_iter);
}

TEST(test, Contains) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  bool my_cont = my_set.contains(17);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(18);
  ASSERT_TRUE(my_cont == false);
  my_cont = my_set.contains(25);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(57);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(5);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(13457);
  ASSERT_TRUE(my_cont == false);
  my_cont = my_set.contains(0);
  ASSERT_TRUE(my_cont == false);
}

TEST(test, Merge) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{4, 5, 6};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  my_iter = my_set2.begin();
  std_iter = std_set2.begin();
  while (std_iter != std_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Merge2) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{1, 2, 3};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  my_iter = my_set2.begin();
  std_iter = std_set2.begin();
  while (std_iter != std_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Merge3) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{2, 3, 543};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  my_iter = my_set2.begin();
  std_iter = std_set2.begin();
  while (std_iter != std_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(test, Merge4) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{44, 5, 6};
  s21::set<int> my_set(items);
  std::set<int> std_set(items);
  s21::set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }

  my_iter = my_set2.begin();
  std_iter = std_set2.begin();
  while (std_iter != std_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}
