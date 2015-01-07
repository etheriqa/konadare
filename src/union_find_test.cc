#include <random>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "union_find.cc"

TEST(UnionFind, Small1)
{
  UnionFind<int> uf;
  uf.insert(1);
  ASSERT_TRUE(uf.find(1) == uf.find(1));
  ASSERT_TRUE(uf.isSame(1, 1));
  uf.merge(1, 1);
  ASSERT_TRUE(uf.find(1) == uf.find(1));
  ASSERT_TRUE(uf.isSame(1, 1));
}

TEST(UnionFind, Small2)
{
  UnionFind<int> uf;
  uf.insert(1);
  uf.insert(2);
  ASSERT_FALSE(uf.find(1) == uf.find(2));
  ASSERT_FALSE(uf.isSame(1, 2));
  ASSERT_FALSE(uf.isSame(2, 1));
  uf.merge(1, 2);
  ASSERT_TRUE(uf.find(1) == uf.find(2));
  ASSERT_TRUE(uf.isSame(1, 2));
  ASSERT_TRUE(uf.isSame(2, 1));
}

TEST(UnionFind, Small3)
{
  UnionFind<int> uf;
  uf.insert(1);
  uf.insert(2);
  uf.insert(3);
  uf.merge(1, 2);
  ASSERT_TRUE(uf.isSame(1, 2));
  ASSERT_FALSE(uf.isSame(2, 3));
  ASSERT_FALSE(uf.isSame(3, 1));
  uf.merge(2, 3);
  ASSERT_TRUE(uf.isSame(1, 2));
  ASSERT_TRUE(uf.isSame(2, 3));
  ASSERT_TRUE(uf.isSame(3, 1));
}

TEST(UnionFind, Small4)
{
  UnionFind<std::string> uf;
  uf.insert("a");
  uf.insert("b");
  uf.insert("c");
  uf.insert("d");
  uf.merge("a", "b");
  uf.merge("b", "c");
  ASSERT_TRUE(uf.isSame("a", "b"));
  ASSERT_TRUE(uf.isSame("a", "c"));
  ASSERT_FALSE(uf.isSame("a", "d"));
  ASSERT_TRUE(uf.isSame("b", "c"));
  ASSERT_FALSE(uf.isSame("b", "d"));
  ASSERT_FALSE(uf.isSame("c", "d"));
  uf.merge("d", "a");
  ASSERT_TRUE(uf.isSame("a", "b"));
  ASSERT_TRUE(uf.isSame("a", "c"));
  ASSERT_TRUE(uf.isSame("a", "d"));
  ASSERT_TRUE(uf.isSame("b", "c"));
  ASSERT_TRUE(uf.isSame("b", "d"));
  ASSERT_TRUE(uf.isSame("c", "d"));
}

TEST(UnionFind, LargeRandom)
{
  const size_t n_queries = 1e4;
  const size_t size = 1e4;
  UnionFind<int> uf;
  std::vector<size_t> vec(size);
  std::random_device seed;
  std::default_random_engine engine(seed());

  for (size_t i = 0; i < size; i++) {
    vec[i] = i;
    uf.insert(i);
  }

  size_t a, b, id = size;

  for (size_t i = 0; i < n_queries; i++) {
    a = engine() % size;
    b = engine() % size;
    switch (engine() % 2) {
    case 0:
      uf.merge(a, b);
      for (size_t j = 0; j < size; j++) {
        if (a == j || b == j) continue;
        if (vec[j] == vec[a] || vec[j] == vec[b]) vec[j] = id;
      }
      vec[a] = vec[b] = id++;
      break;
    case 1:
      ASSERT_EQ(vec[a] == vec[b], uf.isSame(a, b));
      break;
    }
  }
}
