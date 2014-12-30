#include "gtest/gtest.h"
#include "push_relabel_relabel_to_front.cc"

TEST(PushRelabelRelabelToFront, Small1)
{
  PushRelabel<int, int> pr;
  pr.addVertex(0);
  pr.addVertex(1);
  pr.addEdge(0, 1, 10);
  EXPECT_EQ(10, pr.findMaxFlow(0, 1));
}

TEST(PushRelabelRelabelToFront, Small2)
{
  PushRelabel<int, int> pr;
  pr.addVertex(0);
  pr.addVertex(1);
  pr.addEdge(0, 1, 10);
  EXPECT_EQ(0, pr.findMaxFlow(1, 0));
}

TEST(PushRelabelRelabelToFront, Small3)
{
  PushRelabel<int, int> pr;
  pr.addVertex(0);
  pr.addVertex(1);
  pr.addVertex(2);
  pr.addEdge(0, 1, 10);
  pr.addEdge(1, 2, 5);
  EXPECT_EQ(5, pr.findMaxFlow(0, 2));
}

TEST(PushRelabelRelabelToFront, Small4)
{
  PushRelabel<int, int> pr;
  pr.addVertex(0);
  pr.addVertex(1);
  pr.addVertex(2);
  pr.addVertex(3);
  pr.addEdge(0, 1, 1000000);
  pr.addEdge(0, 2, 1000000);
  pr.addEdge(1, 2, 1);
  pr.addEdge(1, 3, 1000000);
  pr.addEdge(2, 3, 1000000);
  EXPECT_EQ(2000000, pr.findMaxFlow(0, 3));
}

TEST(PushRelabelRelabelToFront, Small5)
{
  PushRelabel<int, int> pr;
  pr.addVertex(0);
  pr.addVertex(1);
  pr.addVertex(2);
  pr.addVertex(3);
  pr.addVertex(4);
  pr.addVertex(5);
  pr.addEdge(0, 1, 16);
  pr.addEdge(0, 2, 13);
  pr.addEdge(1, 3, 12);
  pr.addEdge(2, 1, 4);
  pr.addEdge(2, 4, 14);
  pr.addEdge(3, 2, 9);
  pr.addEdge(3, 5, 20);
  pr.addEdge(4, 3, 7);
  pr.addEdge(4, 5, 4);
  EXPECT_EQ(23, pr.findMaxFlow(0, 5));
}
