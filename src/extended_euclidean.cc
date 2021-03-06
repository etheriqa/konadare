/**
 * Extended Euclidean algorithm
 */

#include <utility>

template <class Arithmetic>
std::pair<Arithmetic, Arithmetic> extended_euclidean(Arithmetic a, Arithmetic b)
{
  if (a < b) {
    auto yx = extended_euclidean(b, a);
    return std::make_pair(yx.second, yx.first);
  }
  if (b == 0) {
    return std::make_pair(1, 0);
  }
  auto xy = extended_euclidean(b, a % b);
  return std::make_pair(xy.second, xy.first - a / b * xy.second);
}
