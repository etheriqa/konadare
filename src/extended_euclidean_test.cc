#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include "gtest/gtest.h"
#include "extended_euclidean.cc"

TEST(ExtendedEuclidean, Small)
{
  std::pair<int, int> xy;

  xy = extended_euclidean(1, 0);
  EXPECT_EQ(1, 1 * xy.first + 0 * xy.second);

  xy = extended_euclidean(1, 1);
  EXPECT_EQ(1, 1 * xy.first + 1 * xy.second);

  xy = extended_euclidean(1, 2);
  EXPECT_EQ(1, 1 * xy.first + 2 * xy.second);

  xy = extended_euclidean(2, 3);
  EXPECT_EQ(1, 2 * xy.first + 3 * xy.second);

  xy = extended_euclidean(12, 18);
  EXPECT_EQ(6, 12 * xy.first + 18 * xy.second);
}

TEST(ExtendedEuclidean, LargeRandom)
{
  const size_t n_cases = 1e6;
  const long long supremum = 1e6;
  std::random_device seed;
  std::default_random_engine engine(seed());

  for (size_t i = 0; i < n_cases; i++) {
    long long a = engine() % supremum + 1;
    long long b = engine() % supremum + 1;
    auto xy = extended_euclidean(a, b);
    EXPECT_EQ(std::__gcd(a, b), a * xy.first + b * xy.second);
  }
}
