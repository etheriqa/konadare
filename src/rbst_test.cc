#include "gtest/gtest.h"
#include "rbst.cc"

TEST(RBST, Small)
{
  RBST<int, int> rbst;
  EXPECT_EQ(nullptr, rbst.find(0));
  EXPECT_EQ(nullptr, rbst.find(1));
  EXPECT_EQ(nullptr, rbst.find(2));

  rbst.insert(1, 100);
  EXPECT_EQ(nullptr, rbst.find(0));
  EXPECT_EQ(100, rbst.find(1)->value());
  EXPECT_EQ(nullptr, rbst.find(2));

  rbst.insert(1, 200);
  EXPECT_EQ(nullptr, rbst.find(0));
  EXPECT_EQ(200, rbst.find(1)->value());
  EXPECT_EQ(nullptr, rbst.find(2));

  rbst.insert(2, 400);
  EXPECT_EQ(nullptr, rbst.find(0));
  EXPECT_EQ(200, rbst.find(1)->value());
  EXPECT_EQ(400, rbst.find(2)->value());

  rbst.erase(1);
  EXPECT_EQ(nullptr, rbst.find(0));
  EXPECT_EQ(nullptr, rbst.find(1));
  EXPECT_EQ(400, rbst.find(2)->value());

  rbst.erase(0);
  EXPECT_EQ(nullptr, rbst.find(0));
  EXPECT_EQ(nullptr, rbst.find(1));
  EXPECT_EQ(400, rbst.find(2)->value());
}

TEST(RBST, Large)
{
  const int N = 1e5;
  RBST<int, int> rbst;
  for (int i = 0; i < N; i++) {
    EXPECT_EQ(nullptr, rbst.find(i));
  }
  for (int i = 0; i < N; i++) {
    rbst.insert(i, i);
  }
  for (int i = 0; i < N; i++) {
    EXPECT_EQ(i, rbst.find(i)->value());
  }
  for (int i = 0; i < N; i++) {
    rbst.erase(i);
  }
  for (int i = 0; i < N; i++) {
    EXPECT_EQ(nullptr, rbst.find(i));
  }
}
