#include <algorithm>
#include <random>
#include <vector>
#include "gtest/gtest.h"
#include "fenwick_tree.cc"

TEST(FenwickTree, Small1)
{
  FenwickTree<int> ft(1);

  ft.add(0, 100);
  ASSERT_EQ(0, ft.prefix(0));
  ASSERT_EQ(100, ft.prefix(1));
  ASSERT_EQ(0, ft.sum(0, 0));
  ASSERT_EQ(100, ft.sum(0, 1));

  ft.add(0, 100);
  ASSERT_EQ(0, ft.prefix(0));
  ASSERT_EQ(200, ft.prefix(1));
  ASSERT_EQ(0, ft.sum(0, 0));
  ASSERT_EQ(200, ft.sum(0, 1));
}

TEST(FenwickTree, Small2)
{
  FenwickTree<int> ft(2);

  ft.add(0, 100);
  ft.add(1, 200);
  ASSERT_EQ(0, ft.prefix(0));
  ASSERT_EQ(100, ft.prefix(1));
  ASSERT_EQ(300, ft.prefix(2));
  ASSERT_EQ(0, ft.sum(0, 0));
  ASSERT_EQ(100, ft.sum(0, 1));
  ASSERT_EQ(300, ft.sum(0, 2));
  ASSERT_EQ(0, ft.sum(1, 0));
  ASSERT_EQ(200, ft.sum(1, 1));
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
