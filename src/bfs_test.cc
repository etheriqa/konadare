#include <map>
#include <vector>
#include "gtest/gtest.h"
#include "bfs.cc"

TEST(BFS, Small)
{
  std::map<int, std::vector<int>> es = {
    {1, {2, 3, 5, 7, 9}},
    {2, {1, 4}},
    {3, {1, 6}},
    {4, {2, 8}},
    {5, {1, 10}},
    {6, {3}},
    {7, {1}},
    {8, {4}},
    {9, {1}},
    {10, {5}}
  };

  auto pred = bfs<int>(
    1,
    [&](int v){
      return es[v];
    }
  );

  EXPECT_EQ(1, pred[1]);
  EXPECT_EQ(1, pred[2]);
  EXPECT_EQ(1, pred[3]);
  EXPECT_EQ(2, pred[4]);
  EXPECT_EQ(1, pred[5]);
  EXPECT_EQ(3, pred[6]);
  EXPECT_EQ(1, pred[7]);
  EXPECT_EQ(4, pred[8]);
  EXPECT_EQ(1, pred[9]);
  EXPECT_EQ(5, pred[10]);
}
