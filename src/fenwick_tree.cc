#include <vector>

template <class Arithmetic>
class FenwickTree
{
  std::vector<Arithmetic> ft;
public:
  FenwickTree(size_t n) :ft(n) {}
  void add(size_t pos, Arithmetic x)
  {
    for (; pos < ft.size(); pos |= ((pos + 1) & ~pos)) {
      ft[pos] += x;
    }
  }
  Arithmetic prefix(size_t n)
  {
    Arithmetic p = Arithmetic();
    for (size_t pos = n - 1; pos < ft.size(); pos = ((pos + 1) & pos) - 1) {
      p += ft[pos];
    }
    return p;
  }
  Arithmetic sum(size_t pos, size_t n)
  {
    return prefix(pos + n) - prefix(pos);
  }
};
