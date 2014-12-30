/**
 * Union-Find
 */

#include <map>
#include <utility>
#include <vector>

template <class Key>
class UnionFind
{
  using size_type = std::size_t;

  std::map<Key, std::pair<Key, size_type>> uf_;
public:
  void insert(const Key& x)
  {
    uf_[x] = std::make_pair(x, 0);
  }
  void merge(const Key& x, const Key& y)
  {
    Key x_root = find(x);
    Key y_root = find(y);
    if (x == y) { return; }

    auto& px = uf_[x_root];
    auto& py = uf_[y_root];
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
    auto& px = uf_[x];
    if (x == px.first) {
      return x;
    } else {
      return px.first = find(px.first);
    }
  }
  bool isSame(const Key& x, const Key& y)
  {
    return find(x) == find(y);
  }
  std::vector<std::vector<Key>> getFamily()
  {
    std::map<Key, std::vector<Key>> family;
    for (auto& p : uf_) {
      family[find(p.first)].push_back(p.first);
    }
    return family;
  }
};
