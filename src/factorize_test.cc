#include <limits>
#include <random>
#include "gtest/gtest.h"
#include "factorize.cc"

TEST(Factorize, Small)
{
  EXPECT_TRUE(factorize(-1).empty());
  EXPECT_TRUE(factorize(0).empty());
  EXPECT_TRUE(factorize(1).empty());
  EXPECT_EQ(factor_t({{2, 1}}), factorize(2));
  EXPECT_EQ(factor_t({{3, 1}}), factorize(3));
  EXPECT_EQ(factor_t({{2, 2}}), factorize(4));
  EXPECT_EQ(factor_t({{5, 1}}), factorize(5));
  EXPECT_EQ(factor_t({{2, 1}, {3, 1}}), factorize(6));
  EXPECT_EQ(factor_t({{7, 1}}), factorize(7));
  EXPECT_EQ(factor_t({{2, 3}}), factorize(8));
  EXPECT_EQ(factor_t({{3, 2}}), factorize(9));
  EXPECT_EQ(factor_t({{2, 1}, {5, 1}}), factorize(10));
  EXPECT_EQ(factor_t({{11, 1}}), factorize(11));
  EXPECT_EQ(factor_t({{2, 2}, {3, 1}}), factorize(12));
  EXPECT_EQ(factor_t({{13, 1}}), factorize(13));
  EXPECT_EQ(factor_t({{2, 1}, {7, 1}}), factorize(14));
  EXPECT_EQ(factor_t({{3, 1}, {5, 1}}), factorize(15));
  EXPECT_EQ(factor_t({{2, 4}}), factorize(16));
  EXPECT_EQ(factor_t({{17, 1}}), factorize(17));
  EXPECT_EQ(factor_t({{2, 1}, {3, 2}}), factorize(18));
  EXPECT_EQ(factor_t({{19, 1}}), factorize(19));
  EXPECT_EQ(factor_t({{2, 2}, {5, 1}}), factorize(20));
  EXPECT_EQ(factor_t({{2, 8}, {3, 4}, {5, 2}, {7, 1}}), factorize(3628800));
}

TEST(Factorize, LargeRandom)
{
  const size_t query = 1e4;
  std::random_device seed;
  std::default_random_engine engine(seed());

  for (size_t i = 0; i < query; i++) {
    int n = engine() % std::numeric_limits<int>::max() + 1;
    factor_t f = factorize(n);
    int product = 1;
    for (auto p : f) {
      for (size_t j = 0; j < p.second; j++) {
        product *= p.first;
      }
    }
    ASSERT_EQ(n, product);
  }
}
