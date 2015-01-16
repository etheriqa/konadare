/**
 * Fenwick tree (Binary indexed tree)
 */

#include <vector>

template <class Arithmetic>
class FenwickTree
{
  std::vector<Arithmetic> ft_;
public:
  FenwickTree(size_t n) :ft_(n) {}
  void add(size_t pos, Arithmetic x)
  {
    for (; pos < ft_.size(); pos |= ((pos + 1) & ~pos)) {
      ft_[pos] += x;
    }
  }
  Arithmetic prefix(size_t n) const
  {
    Arithmetic p = decltype(p)();
    for (size_t pos = n - 1; pos < ft_.size(); pos = ((pos + 1) & pos) - 1) {
      p += ft_[pos];
    }
    return p;
  }
  Arithmetic sum(size_t pos, size_t n) const
  {
    return prefix(pos + n) - prefix(pos);
  }
};
