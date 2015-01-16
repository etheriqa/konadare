/**
 * Fenwick tree (Binary indexed tree)
 */

#include <vector>

template <class Arithmetic>
class FenwickTree
{
  using size_type = std::size_t;
  std::vector<Arithmetic> ft_;
public:
  FenwickTree(size_type n) :ft_(n) {}
  void add(size_type pos, Arithmetic x)
  {
    for (; pos < ft_.size(); pos |= ((pos + 1) & ~pos)) {
      ft_[pos] += x;
    }
  }
  Arithmetic prefix(size_type n) const
  {
    Arithmetic p = decltype(p)();
    for (size_type pos = n - 1; pos < ft_.size(); pos = ((pos + 1) & pos) - 1) {
      p += ft_[pos];
    }
    return p;
  }
  Arithmetic sum(size_type pos, size_type n) const
  {
    return prefix(pos + n) - prefix(pos);
  }
};
