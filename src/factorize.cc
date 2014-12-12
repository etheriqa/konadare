#include <cmath>
#include <map>

using factor_t = std::map<long long, int>;

factor_t factorize(long long x)
{
  factor_t factor;
  for (int i = 2; x > 1 && i <= floor(sqrt(x)); i++) {
    while (x % i == 0) {
      x /= i;
      factor[i] += 1;
    }
  }
  if (x > 1) factor[x] += 1;
  return factor;
}
