#include "gtest/gtest.h"
#include "rbst.cc"

TEST(RBST, Small)
{
  RBST<int> rbst;
  EXPECT_EQ(0, rbst.size());
  rbst.push_back(1);
  EXPECT_EQ(1, rbst.size());
  EXPECT_EQ(1, rbst.at(0));
  rbst.push_back(2);
  EXPECT_EQ(2, rbst.size());
  EXPECT_EQ(2, rbst.at(1));
}

TEST(RBST, Large)
{
  const int N = 1e6;
  RBST<int> rbst;
  EXPECT_EQ(0, rbst.size());
  for (int i = 0; i < N; i++) {
    rbst.push_back(i);
  }
  EXPECT_EQ(N, rbst.size());
  for (int i = 0; i < N; i++) {
    EXPECT_EQ(i, rbst.at(i));
  }
}
