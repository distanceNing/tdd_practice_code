//
// Created by ninggyang on 2022/6/10.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

class Collection {
 public:
  Collection() : size_(0) {}
  bool isEmpty() const {
    return size() == 0;
  }
  size_t size() const {
    return size_;
  }
  void add(int i) {
    size_++;
  }
 private:
  size_t size_;
};
class CollectionTest : public ::testing::Test {
 protected:
  Collection c;
};

TEST_F(CollectionTest, isEmptyWhenSizeIsZero) {
  ASSERT_TRUE(c.isEmpty());
  ASSERT_THAT(c.size(), Eq(0));
}

TEST_F(CollectionTest, isNotEmptyAfterAdd) {
  c.add(1);
  ASSERT_FALSE(c.isEmpty());
  ASSERT_GT(c.size(), 0);
}

TEST_F(CollectionTest, SizeIncreaseAfterAdd) {
  c.add(1);
  ASSERT_EQ(c.size(), 1);
  c.add(1);
  ASSERT_EQ(c.size(), 2);
}