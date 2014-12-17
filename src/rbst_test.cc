#include "gtest/gtest.h"
#include "rbst.cc"

#include <set>

TEST(RBST, Small)
{
  RBST<int> rbst;
  EXPECT_EQ(0, rbst.count(0));
  EXPECT_EQ(0, rbst.count(1));
  rbst.insert(0);
  EXPECT_EQ(1, rbst.count(0));
  EXPECT_EQ(0, rbst.count(1));
  rbst.insert(0);
  EXPECT_EQ(2, rbst.count(0));
  EXPECT_EQ(0, rbst.count(1));
  rbst.insert(1);
  EXPECT_EQ(2, rbst.count(0));
  EXPECT_EQ(1, rbst.count(1));
  rbst.erase(0);
  EXPECT_EQ(0, rbst.count(0));
  EXPECT_EQ(1, rbst.count(1));
}

TEST(RBST, Large)
{
  RBST<int> rbst;
  for (int i = 0; i < 1e3; i++) {
    rbst.insert(i);
  }
  for (int i = 0; i < 1e3; i++) {
    EXPECT_EQ(1, rbst.count(i));
  }
}
