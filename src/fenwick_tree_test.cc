#include "gtest/gtest.h"
#include "fenwick_tree.cc"

TEST(FenwickTree, Small)
{
  const size_t n = 10;
  FenwickTree<int> ft(n);
  for (int i = 0; i < n; i++) {
    ft.add(i, i);
  }

  for (int i = 0; i <= n; i++) {
    EXPECT_EQ(i * (i - 1) / 2, ft.prefix(i));
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; i + j <= n; j++) {
      EXPECT_EQ(j * (2 * i + j - 1) / 2, ft.sum(i, j));
    }
  }
}
