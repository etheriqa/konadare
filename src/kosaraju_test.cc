#include <utility>
#include <vector>
#include "gtest/gtest.h"
#include "kosaraju.cc"
#include "union_find.cc"

TEST(Kosaraju, Small)
{
  std::vector<char> vertices = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  std::vector<std::pair<char, char>> edges = {
    {'a', 'b'},
    {'b', 'e'},
    {'b', 'f'},
    {'c', 'd'},
    {'c', 'g'},
    {'d', 'c'},
    {'d', 'h'},
    {'e', 'a'},
    {'e', 'f'},
    {'f', 'g'},
    {'g', 'f'},
    {'g', 'h'},
    {'h', 'h'}
  };
  Kosaraju<char> kosaraju;
  for (auto v : vertices) kosaraju.addVertex(v);
  for (auto e : edges) kosaraju.addEdge(e.first, e.second);
  auto scc = kosaraju.findSCC();

  UnionFind<char> uf;
  for (auto v : vertices) uf.insert(v);
  for (auto vs : scc) for (auto v : vs) uf.merge(v, vs.front());
  EXPECT_TRUE(uf.isSame('a', 'b'));
  EXPECT_TRUE(uf.isSame('a', 'e'));
  EXPECT_FALSE(uf.isSame('a', 'c'));
  EXPECT_FALSE(uf.isSame('a', 'f'));
  EXPECT_FALSE(uf.isSame('a', 'h'));
  EXPECT_TRUE(uf.isSame('c', 'd'));
  EXPECT_FALSE(uf.isSame('c', 'f'));
  EXPECT_FALSE(uf.isSame('c', 'h'));
  EXPECT_TRUE(uf.isSame('f', 'g'));
  EXPECT_FALSE(uf.isSame('f', 'h'));
}
