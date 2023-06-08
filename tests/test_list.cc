#include "test.h"

using int_list = s21::list<int>;
using iterator = int_list::iterator;

TEST(ListConstructorTest, DefaultEmpty) {
  int_list lst = int_list();
  EXPECT_EQ(lst.size(), 0);
}

TEST(ListConstructorTest, DefaultSized) {
  int_list lst = int_list(10);
  EXPECT_EQ(lst.size(), 10);
  auto it = lst.begin();
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(ListConstructorTest, ListInitializer) {
  int arr[] = {1, 2, 3, 4, 5, 6};
  int_list lst = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(lst.size(), 6);
  int i = 0;
  auto it = lst.begin();
  while (it != lst.end()) {
    EXPECT_EQ(*it, arr[i]);
    ++it;
    i++;
  }
}

TEST(ListConstructorTest, Copy) {
  int_list lst = {1, 2, 3, 4, 5, 6};
  int_list copy = lst;
  EXPECT_EQ(copy.size(), lst.size());
  auto it = lst.begin();
  auto copy_it = copy.begin();
  while (it != lst.end()) {
    EXPECT_EQ(*it, *copy_it);
    ++it;
    ++copy_it;
  }
}

TEST(ListConstructorTest, CopyAssignmentOperator) {
  int_list lst1 = {1, 2, 3, 4, 5, 6};
  int_list lst2 = {1, 1, 1, 1, 1, 1};
  lst2 = lst1;
  EXPECT_EQ(lst1.size(), lst2.size());
  auto it1 = lst1.begin();
  auto it2 = lst2.begin();
  while (it1 != lst1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListConstructorTest, Move) {
  int arr[] = {1, 2, 3, 4, 5, 6};
  int_list lst = {1, 2, 3, 4, 5, 6};
  int_list moved;
  moved = std::move(lst);
  EXPECT_EQ(moved.size(), 6);
  EXPECT_EQ(lst.size(), 0);
  auto it = moved.begin();
  int i = 0;
  while (it != moved.end()) {
    EXPECT_EQ(*it, arr[i]);
    ++it;
    ++i;
  }
}

TEST(ListEraseTest, BeginPos) {
  int_list result = {1, 2, 3, 4};
  int_list expected = {2, 3, 4};

  result.erase(result.begin());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  EXPECT_EQ(result.size(), expected.size());
  while (it1 != result.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListEraseTest, MiddlePos) {
  int_list result = {1, 3, 4};
  int_list expected = {1, 4};

  result.erase(++result.begin());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  EXPECT_EQ(result.size(), expected.size());
  while (it1 != result.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListClearTest, Full) {
  int_list lst = {1, 2, 3, 4};
  lst.clear();

  EXPECT_EQ(lst.size(), 0);
  EXPECT_EQ(lst.begin(), lst.end());
}

TEST(ListClearTest, Empty) {
  int_list lst;
  lst.clear();

  EXPECT_EQ(lst.size(), 0);
  EXPECT_EQ(lst.begin(), lst.end());
}

TEST(ListInsertTest, Middle) {
  int_list lst = {1, 2, 3, 4};
  auto pos = lst.begin();
  std::advance(pos, 2);

  lst.insert(pos, 11);

  auto new_elem = --pos;

  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(*new_elem, 11);
}

TEST(ListPushBackTest, EmptyList) {
  int_list lst;

  lst.push_back(2);

  EXPECT_EQ(lst.size(), 1);
  EXPECT_EQ(*(--lst.end()), 2);
}

TEST(ListPushBackTest, NonEmpyList) {
  int_list result = {5, 2, 23, 1};

  result.push_back(2);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(*(--result.end()), 2);
}

TEST(ListPushFrontTest, EmptyList) {
  int_list lst;

  lst.push_front(2);

  EXPECT_EQ(lst.size(), 1);
  EXPECT_EQ(*(lst.begin()), 2);
}

TEST(ListPushFrontTest, NonEmpyList) {
  int_list result = {5, 2, 23, 1};

  result.push_front(2);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(*(result.begin()), 2);
}

TEST(ListPopBackTest, NonEmpyList) {
  int_list result = {5, 2, 23, 1};

  result.pop_back();

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(*(--result.end()), 23);
}

TEST(ListPopFrontTest, NonEmpyList) {
  int_list result = {5, 2, 23, 1};

  result.pop_front();

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(*(result.begin()), 2);
}

TEST(ListSwap, Common) {
  int_list lst1 = {1, 2, 3};
  int_list lst1_swaped = {6, 34, 0, 23};
  int_list lst2 = {6, 34, 0, 23};
  int_list lst2_swaped = {1, 2, 3};

  lst1.swap(lst2);

  EXPECT_EQ(lst1.size(), lst1_swaped.size());
  EXPECT_EQ(lst2.size(), lst2_swaped.size());

  auto lst1_it = lst1.begin();
  auto lst1_swaped_it = lst1_swaped.begin();
  while (lst1_swaped_it != lst1_swaped.end()) {
    EXPECT_EQ(*lst1_it, *lst1_swaped_it);
    ++lst1_it;
    ++lst1_swaped_it;
  }

  auto lst2_it = lst2.begin();
  auto lst2_swaped_it = lst2_swaped.begin();
  while (lst2_swaped_it != lst2_swaped.end()) {
    EXPECT_EQ(*lst2_it, *lst2_swaped_it);
    ++lst2_it;
    ++lst2_swaped_it;
  }
}

TEST(ListSplice, Begin) {
  int_list result = {1, 2, 3};
  int_list spliced = {4, 5, 6};
  int_list expected = {4, 5, 6, 1, 2, 3};

  result.splice(result.begin(), spliced);

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it1 != result.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListSplice, Middle) {
  int_list result = {1, 2, 3, 4};
  int_list spliced = {5, 6};
  int_list expected = {1, 2, 5, 6, 3, 4};
  auto it = result.begin();
  std::advance(it, 2);

  result.splice(it, spliced);

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it1 != result.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListSplice, End) {
  int_list result = {1, 2, 3, 4};
  int_list spliced = {5, 6};
  int_list expected = {1, 2, 3, 4, 5, 6};

  result.splice(result.end(), spliced);

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it1 != result.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListReverse, Empty) {
  int_list result;
  int_list expected;

  result.reverse();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListReverse, NonEmpty) {
  int_list result = {1, 2, 3, 4, 5};
  int_list expected = {5, 4, 3, 2, 1};

  result.reverse();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListUnique, NoRepeats) {
  int_list result = {1, 2, 3, 4, 5, 6};
  int_list expected = {1, 2, 3, 4, 5, 6};

  result.unique();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListUnique, WithRepeats) {
  int_list result = {1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6};
  int_list expected = {1, 2, 3, 4, 5, 6};

  result.unique();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListUnique, WithIntermittentRepeatsRepeats) {
  int_list result = {1, 2, 2, 1, 1, 2, 2, 4, 4, 5, 5};
  int_list expected = {1, 2, 1, 2, 4, 5};

  result.unique();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListUnique, WithTheSameElements) {
  int_list result = {1, 1, 1, 1, 1};
  int_list expected = {1};

  result.unique();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListMerge, Full) {
  int_list result = {1, 3, 6, 10};
  int_list merged = {2, 7, 8, 12};
  int_list expected = {1, 2, 3, 6, 7, 8, 10, 12};

  result.merge(merged);

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListMerge, EqualLists) {
  int_list result = {1, 1, 1, 1};
  int_list merged = {1, 1, 1, 1};
  int_list expected = {1, 1, 1, 1, 1, 1, 1, 1};

  result.merge(merged);

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListSort, Common) {
  int_list result = {8, 1, 5, 2, 10, 6};
  int_list expected = {1, 2, 5, 6, 8, 10};

  result.sort();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListSort, WithEquals) {
  int_list result = {8, 1, 2, 2, 10, 6};
  int_list expected = {1, 2, 2, 6, 8, 10};

  result.sort();

  EXPECT_EQ(result.size(), expected.size());

  auto it1 = result.begin();
  auto it2 = expected.begin();
  while (it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}
