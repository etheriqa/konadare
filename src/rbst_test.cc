#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "rbst.cc"

TEST(RBST, Small)
{
  RBST<int> rbst(10);
  EXPECT_EQ(0, rbst.size());
  rbst.push_back(1);
  EXPECT_EQ(1, rbst.size());
  EXPECT_EQ(1, rbst.at(0));
  rbst.push_back(2);
  EXPECT_EQ(2, rbst.size());
  EXPECT_EQ(2, rbst.at(1));
}

TEST(RBST, Large)
{
  const size_t size = 1e4;
  const size_t query = 1e6;
  const long long range = 1e6;
  RBST<long long> rbst(1e6);
  std::vector<long long> vec;
  std::random_device seed;
  std::default_random_engine engine(seed());

  size_t pos, n;
  long long value;

  for (size_t i = 0; i < size; i++) {
    value = engine() % (2 * range) - range;
    rbst.push_back(value);
    vec.push_back(value);
  }

  for (size_t i = 0; i < query; i++) {
    switch (engine() % 2) {
    case 0:
      pos = engine() % size;
      EXPECT_TRUE(rbst.at(pos) == vec.at(pos));
      break;
    case 1:
      std::pair<size_t, size_t> p = std::minmax(engine() % size, engine() % size);
      pos = p.first;
      n = p.second - p.first;
      value = engine() % (2 * range) - range;
      rbst.add(pos, n, value);
      for (size_t j = 0; j < n; j++) {
        vec[pos + j] += value;
      }
      break;
    }
  }

  /*
  while (in >> query) {
    if (query == "push_back") {
      long long v;
      in >> v;
      rbst.push_back(v);
      vec.push_back(v);
    }
    if (query == "at") {
    }
    if (query == "add") {
      size_t pos, n;
      long long v;
      in >> pos >> n >> v;
      rbst.add(pos, n, v);
      for (size_t i = 0; i < n; i++) {
        vec[pos + i] += v;
      }
    }
  }
  */
}
