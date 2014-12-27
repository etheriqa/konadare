#include <set>
#include "gtest/gtest.h"
#include "union_find.cc"

TEST(UnionFind, Small)
{
  UnionFind<int> uf;
  for (int i = 0; i < 10; i++) {
    uf.insert(i);
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == j) { EXPECT_TRUE(uf.isSame(i, j)); }
      else        { EXPECT_FALSE(uf.isSame(i, j)); }
    }
  }

  uf.merge(0, 1);
  std::set<int> s0({0, 1});
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if      (i == j)                     { EXPECT_TRUE(uf.isSame(i, j)); }
      else if (s0.count(i) && s0.count(j)) { EXPECT_TRUE(uf.isSame(i, j)); }
      else                                 { EXPECT_FALSE(uf.isSame(i, j)); }
    }
  }

  uf.merge(1, 0);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if      (i == j)                     { EXPECT_TRUE(uf.isSame(i, j)); }
      else if (s0.count(i) && s0.count(j)) { EXPECT_TRUE(uf.isSame(i, j)); }
      else                                 { EXPECT_FALSE(uf.isSame(i, j)); }
    }
  }

  uf.merge(2, 3);
  std::set<int> s1({2, 3});
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if      (i == j)                     { EXPECT_TRUE(uf.isSame(i, j)); }
      else if (s0.count(i) && s0.count(j)) { EXPECT_TRUE(uf.isSame(i, j)); }
      else if (s1.count(i) && s1.count(j)) { EXPECT_TRUE(uf.isSame(i, j)); }
      else                                 { EXPECT_FALSE(uf.isSame(i, j)); }
    }
  }

  uf.merge(3, 1);
  std::set<int> s2({0, 1, 2, 3});
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if      (i == j)                     { EXPECT_TRUE(uf.isSame(i, j)); }
      else if (s2.count(i) && s2.count(j)) { EXPECT_TRUE(uf.isSame(i, j)); }
      else                                 { EXPECT_FALSE(uf.isSame(i, j)); }
    }
  }

  for (int i = 0; i < 10; i++) {
    uf.merge(0, i);
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      EXPECT_TRUE(uf.isSame(i, j));
    }
  }
}
