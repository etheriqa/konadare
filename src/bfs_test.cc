#include <map>
#include <set>
#include "gtest/gtest.h"
#include "bfs.cc"

TEST(BFS, Basic)
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

  std::vector<int> visited;

  bfs<int>(
    1,
    [&](int v){
      visited.push_back(v);
      return es[v];
    }
  );

  EXPECT_EQ(std::vector<int>({1, 2, 3, 5, 7, 9, 4, 6, 10, 8}), visited);
}
