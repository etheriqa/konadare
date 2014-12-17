#include <map>
#include "gtest/gtest.h"
#include "factorize.cc"

TEST(Factorize, Small)
{
  EXPECT_TRUE(factorize(-1).empty());
  EXPECT_TRUE(factorize(0).empty());
  EXPECT_TRUE(factorize(1).empty());

  std::map<long long, std::map<long long, int>> fixtures({
    {2, {{2, 1}}},
    {3, {{3, 1}}},
    {4, {{2, 2}}},
    {5, {{5, 1}}},
    {6, {{2, 1}, {3, 1}}},
    {7, {{7, 1}}},
    {8, {{2, 3}}},
    {9, {{3, 2}}},
    {10, {{2, 1}, {5, 1}}},
    {11, {{11, 1}}},
    {12, {{2, 2}, {3, 1}}},
    {13, {{13, 1}}},
    {14, {{2, 1}, {7, 1}}},
    {15, {{3, 1}, {5, 1}}},
    {16, {{2, 4}}},
    {17, {{17, 1}}},
    {18, {{2, 1}, {3, 2}}},
    {19, {{19, 1}}},
    {20, {{2, 2}, {5, 1}}}
  });

  for (auto f : fixtures) {
    EXPECT_EQ(f.second, factorize(f.first));
  }
}

TEST(Factorize, Large)
{
  std::map<long long, std::map<long long, int>> fixtures({
    {3628800, {{2, 8}, {3, 4}, {5, 2}, {7, 1}}},
    {2432902008176640000ll, {{2, 18}, {3, 8}, {5, 4}, {7, 2}, {11, 1}, {13, 1}, {17, 1}, {19, 1}}}
  });

  for (auto f : fixtures) {
    EXPECT_EQ(f.second, factorize(f.first));
  }
}
