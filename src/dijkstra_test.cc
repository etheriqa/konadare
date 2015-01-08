#include <vector>
#include "gtest/gtest.h"
#include "dijkstra.cc"

TEST(Dijkstra, Small1)
{
  auto pred = dijkstra<int, int>(
    0,
    [](int){ return std::vector<int>(0); },
    [](int, int){ return 1; }
  );
  ASSERT_EQ(1, pred.size());
  ASSERT_EQ(0, pred.at(0));
}

TEST(Dijkstra, Small2)
{
  auto pred = dijkstra<int, int>(
    0,
    [](int){ return std::vector<int>({0, 1}); },
    [](int, int){ return 1; }
  );
  ASSERT_EQ(2, pred.size());
  ASSERT_EQ(0, pred.at(0));
  ASSERT_EQ(0, pred.at(1));
}

TEST(Dijkstra, Small3)
{
  std::vector<std::vector<int>> weight = {
    {    0,     3,     6,    12 ,10000, 10000},
    {10000,     0, 10000,     3 ,10000, 10000},
    {10000, 10000,     0,     6 ,10000, 10000},
    {10000, 10000, 10000,     0 ,10000, 10000},
    {10000, 10000, 10000,     5 ,    0, 10000},
    {10000, 10000, 10000, 10000 ,10000,     0}
  };

  auto pred = dijkstra<int, int>(
    0,
    [&weight](int u){
      std::vector<int> adjs;
      for (int v = 0; v < weight[u].size(); v++) {
        if (weight[u][v] < 10000) adjs.push_back(v);
      }
      return adjs;
    },
    [&weight](int u, int v){
      return weight[u][v];
    }
  );

  EXPECT_EQ(1, pred.count(0));
  EXPECT_EQ(1, pred.count(1));
  EXPECT_EQ(1, pred.count(2));
  EXPECT_EQ(1, pred.count(3));
  EXPECT_EQ(0, pred.count(4));
  EXPECT_EQ(0, pred.count(5));

  EXPECT_EQ(0, pred.at(0));
  EXPECT_EQ(0, pred.at(1));
  EXPECT_EQ(0, pred.at(2));
  EXPECT_EQ(1, pred.at(3));
}
