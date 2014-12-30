#include <algorithm>
#include <random>
#include <vector>
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

TEST(FenwickTree, LargeRandom)
{
  const size_t size = 1e6;
  const size_t query = 1e4;
  const long long range = 1e6;
  FenwickTree<long long> ft(size);
  std::vector<long long> vec(size);
  std::random_device seed;
  std::default_random_engine engine(seed());

  size_t pos, n;
  long long value;

  for (size_t i = 0; i < size; i++) {
    value = engine() % (2 * range) - range;
    ft.add(i, value);
    vec[i] = value;
  }

  for (size_t i = 0; i < query; i++) {
    switch (engine() % 3) {
    case 0:
      pos = engine() % size;
      value = engine() % (2 * range) - range;
      ft.add(pos, value);
      vec[pos] += value;
      break;
    case 1:
      pos = engine() % size;
      EXPECT_TRUE(ft.prefix(pos) == std::accumulate(vec.begin(), vec.begin() + pos, 0ll));
      break;
    case 2:
      std::pair<size_t, size_t> p = std::minmax(engine() % size, engine() % size);
      pos = p.first;
      n = p.second - p.first;
      EXPECT_TRUE(ft.sum(pos, n) == std::accumulate(vec.begin() + pos, vec.begin() + pos + n, 0ll));
      break;
    }
  }
}
