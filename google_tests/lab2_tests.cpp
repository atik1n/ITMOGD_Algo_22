#include "gtest/gtest.h"
#include "dyn-array.hpp"

#define TEST_STRING_SIZE 32

class DynamicArrayFixture : public ::testing::Test {
protected:
  Array<char>* array;
  Array<std::string>* stringArray;

  virtual void SetUp() {
    array = new Array<char>();
    stringArray = new Array<std::string>();
  }

  virtual void TearDown() {
    delete array;
    delete stringArray;
  }
};

TEST_F(DynamicArrayFixture, BasicInsertRemove) {
  for (char i = 0; i < 64; ++i) {
    array->insert(i);
    stringArray->insert(std::string(TEST_STRING_SIZE, i));
  }

  for (char i = 63; i > -1; --i) {
    EXPECT_EQ((*array)[i], i);
  }

  for (char i = 0; i < 64; ++i) {
    EXPECT_EQ((*array)[0], i);
    EXPECT_EQ(array->size(), 64 - i);
    EXPECT_EQ(stringArray->size(), 64 - i);
    array->remove(0);
    stringArray->remove(0);
  }
}

TEST_F(DynamicArrayFixture, EdgeCases) {
  EXPECT_EQ(array->insert(-1, 1), -1);
  EXPECT_EQ(array->size(), 0);

  EXPECT_EQ(array->insert(10, 1), 0);
  EXPECT_EQ(array->size(), 1);

  array->remove(-1);
  array->remove(10);
  EXPECT_EQ(array->size(), 1);
}

TEST_F(DynamicArrayFixture, InsertInside) {
  for (int i = 0; i < 100; ++i) {
    array->insert(0);
  }
  EXPECT_EQ(array->size(), 100);

  for (int i = 0; i < 10; ++i) {
    array->insert(10 + i, i);
  }
  EXPECT_EQ(array->size(), 110);

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ((*array)[10 + i], i);
  }
}

class PreloadedDynamicArrayFixture : public DynamicArrayFixture {
protected:
  char size = 64;

  virtual void SetUp() {
    array = new Array<char>();
    stringArray = new Array<std::string>();
    for (char i = 0; i < size; ++i) {
      array->insert(i);
      stringArray->insert(std::string(TEST_STRING_SIZE, i));
    }
  }
};

TEST_F(PreloadedDynamicArrayFixture, IteratorsGet) {
  char i = 0;
  for (auto iter = array->iterator(); iter.hasNext(); iter.next()) {
    EXPECT_EQ(iter.get(), i++);
  }

  for (auto iter = array->reverseIterator(); iter.hasNext(); iter.next()) {
    EXPECT_EQ(iter.get(), --i);
  }
}
