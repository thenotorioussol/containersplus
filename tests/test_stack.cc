#include "test.h"

using namespace s21;

TEST(Stack, ConstuctorEmpty) {
  stack<int> numbers;
  EXPECT_EQ(numbers.size(), 0);
  EXPECT_TRUE(numbers.empty());
}

TEST(Stack, ConstuctorInitList) {
  stack<int> numbers = {15, 2, 5, 4, 76};
  EXPECT_EQ(numbers.size(), 5);
  EXPECT_EQ(numbers.top(), 76);
}

TEST(Stack, ConstuctorCopy) {
  stack<int> numbers;
  numbers.push(5);
  stack<int> numbers_copy(numbers);
  EXPECT_EQ(numbers_copy.top(), 5);
  numbers_copy.pop();
  EXPECT_TRUE(numbers_copy.empty());
  EXPECT_FALSE(numbers.empty());
}

TEST(Stack, ConstuctorMove) {
  stack<int> numbers;
  numbers.push(5);
  stack<int> numbers_move;
  numbers_move = std::move(numbers);
  EXPECT_EQ(numbers_move.top(), 5);
  EXPECT_TRUE(numbers.empty());
}

TEST(Stack, Modifiers) {
  stack<int> numbers1, numbers2;
  numbers1.push(10);
  numbers1.push(20);
  numbers1.push(30);
  numbers2.push(50);

  EXPECT_EQ(numbers1.top(), 30);
  EXPECT_EQ(numbers1.size(), 3);
  numbers1.pop();

  EXPECT_EQ(numbers1.top(), 20);
  EXPECT_EQ(numbers1.size(), 2);
  numbers1.pop();

  EXPECT_EQ(numbers1.top(), 10);
  EXPECT_EQ(numbers1.size(), 1);

  numbers1.swap(numbers2);
  EXPECT_EQ(numbers1.top(), 50);
  EXPECT_EQ(numbers2.top(), 10);
}

TEST(Stack, Capacity) {
  stack<char> letters;
  EXPECT_TRUE(letters.empty());
  EXPECT_EQ(letters.size(), 0);

  letters.push('a');
  letters.push('b');
  letters.push('c');

  EXPECT_FALSE(letters.empty());
  EXPECT_EQ(letters.size(), 3);
}
