#include "test.h"

TEST(Vector, ConstructorDefault) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, ConstructorInitialize) {
  s21::vector<int> s21_vector = {3, 3, 1, 2};
  std::vector<int> std_vector = {3, 3, 1, 2};

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
}

TEST(Vector, ConstructorParameterized) {
  s21::vector<double> s21_vector(10);
  std::vector<double> std_vector(10);

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}
TEST(Vector, ConstructorCopy) {
  s21::vector<char> s21_vector_1 = {'q', 'w', 'e', 'r', 't',
                                    'y', 'u', 'i', 'o', 'p'};
  std::vector<char> std_vector_1 = {'q', 'w', 'e', 'r', 't',
                                    'y', 'u', 'i', 'o', 'p'};

  s21::vector<char> s21_vector_2 = s21_vector_1;
  std::vector<char> std_vector_2 = std_vector_1;

  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  EXPECT_EQ(std_vector_1.size(), std_vector_2.size());

  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();

  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(Vector, ConstructorMove) {
  s21::vector<char> s21_vector_1 = {'a', 's', 'd', 'f'};
  std::vector<char> std_vector_1 = {'a', 's', 'd', 'f'};
  s21::vector<char> s21_vector_2 = std::move(s21_vector_1);
  std::vector<char> std_vector_2 = std::move(std_vector_1);

  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());

  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();

  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Vector, ModifierInsert) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_1.begin();
  ++it;
  s21_vector_1.insert(it, 'b');
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();

  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  s21_vector_1.insert(s21_vector_1.end(), '5');
  EXPECT_EQ(s21_vector_1.back(), '5');
}

TEST(Vector, ModifierErase) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_2.begin();
  ++it;
  s21_vector_2.erase(it);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();

  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
}

TEST(Vector, ModifierPush) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.push_back(5);
  std_vector.push_back(5);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());

  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();

  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Vector, ModifierPop) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.pop_back();
  std_vector.pop_back();

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());

  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();

  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Vector, ModifierSwap) {
  s21::vector<char> s21_vector_1 = {'q', 'w', 'e', 'r', 't'};
  s21::vector<char> s21_vector_2 = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  s21::vector<char> s21_vector_3 = {'q', 'w', 'e', 'r', 't'};
  s21::vector<char> s21_vector_4 = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  s21_vector_1.swap(s21_vector_2);

  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  auto it3 = s21_vector_3.begin();
  auto it4 = s21_vector_4.begin();

  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }

  while (it2 != s21_vector_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }

  EXPECT_EQ(s21_vector_1.size(), s21_vector_4.size());
  EXPECT_EQ(s21_vector_2.size(), s21_vector_3.size());
}