#include "test.h"

using namespace s21;

TEST(Queue, ConstuctorEmpty) {
  queue<int> numbers;
  EXPECT_EQ(numbers.size(), 0);
  EXPECT_TRUE(numbers.empty());
}

TEST(Queue, ConstuctorInitList) {
  queue<int> numbers = {15, 2, 5, 4, 76};
  EXPECT_EQ(numbers.size(), 5);
  EXPECT_EQ(numbers.front(), 15);
  EXPECT_EQ(numbers.back(), 76);
}

TEST(Queue, ConstuctorCopy) {
  queue<int> numbers;
  numbers.push(5);
  queue<int> numbers_copy(numbers);
  EXPECT_EQ(numbers_copy.back(), 5);
  numbers_copy.pop();
  EXPECT_TRUE(numbers_copy.empty());
  EXPECT_FALSE(numbers.empty());
}

TEST(Queue, ConstuctorMove) {
  queue<int> numbers;
  numbers.push(5);
  queue<int> numbers_move;
  numbers_move = std::move(numbers);
  EXPECT_EQ(numbers_move.back(), 5);
  EXPECT_TRUE(numbers.empty());
}

TEST(Queue, Accessors) {
  queue<int> numbers;
  numbers.push(1);
  numbers.push(2);
  numbers.push(3);
  numbers.push(4);

  EXPECT_FALSE(numbers.empty());
  EXPECT_EQ(numbers.size(), 4);

  EXPECT_EQ(numbers.back(), 4);
  EXPECT_EQ(numbers.front(), 1);
}

TEST(Queue, Capacity) {
  queue<int> numbers;

  EXPECT_TRUE(numbers.empty());

  numbers.push(1);
  numbers.push(2);
  numbers.push(3);
  numbers.push(4);

  EXPECT_FALSE(numbers.empty());
  EXPECT_EQ(numbers.size(), 4);
}

TEST(Queue, Modifiers) {
  queue<int> numbers1;
  queue<int> numbers2;

  numbers1.push(1);
  numbers1.push(2);
  numbers1.push(3);
  numbers1.push(4);

  numbers2.push(15);

  numbers1.swap(numbers2);

  EXPECT_EQ(numbers1.size(), 1);
  EXPECT_EQ(numbers2.size(), 4);

  numbers1.pop();
  numbers2.pop();
  EXPECT_EQ(numbers1.size(), 0);
  EXPECT_EQ(numbers2.size(), 3);
}