/**
 * Union-Find
 */

#include <map>
#include <utility>

template <class Key>
class UnionFind
{
  std::map<Key, std::pair<Key, size_t>> uf;
public:
  void insert(const Key& x)
  {
    uf[x] = std::make_pair(x, 0);
  }
  void merge(const Key& x, const Key& y)
  {
    Key x_root = find(x);
    Key y_root = find(y);
    if (x == y) { return; }

    auto& px = uf[x_root];
    auto& py = uf[y_root];
    if (px.second < py.second) {
      px.first = y_root;
    } else if (px.second > py.second) {
      py.first = x_root;
    } else {
      py.first = x_root;
      px.second++;
    }
  }
  Key find(const Key& x)
  {
    auto& px = uf[x];
    if (x == px.first) {
      return x;
    } else {
      return px.first = find(px.first);
    }
  }
};
