template <
  class Key,
  class Hash = std::hash<Key>,
  class Pred = std::equal_to<Key>,
  class Allocator = std::allocator<Key>>
class UnionFind
{
  std::unordered_map<Key, std::tuple<Key, int>, Hash, Pred, Allocator> uf;
public:
  void insert(const Key& a)
  {
    uf[a] = std::make_tuple(a, 0);
  }
  void merge(const Key& a, const Key& b)
  {
    auto& a_tuple = uf[find(a)];
    auto& b_tuple = uf[find(b)];
    Key& a_root = std::get<0>(a_tuple);
    Key& b_root = std::get<0>(b_tuple);
    size_t& a_rank = std::get<1>(a_tuple);
    size_t& b_rank = std::get<1>(b_tuple);
    if (a_rank > b_rank) {
      b_root = a_root;
    } else if (a_rank < b_rank) {
      a_root = b_root;
    } else if (a_root != b_root) {
      b_root = a_root;
      a_rank++;
    }
  }
  Key find(const Key& a)
  {
    if (a == std::get<0>(uf[a])) {
      return a;
    } else {
      return std::get<0>(uf[a]) = find(std::get<0>(uf[a]));
    }
  }
};
