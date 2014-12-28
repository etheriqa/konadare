/**
 * Depth-first search
 */

#include <functional>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

template <class V>
std::unordered_map<V, V> dfs(
    V start,
    std::function<std::vector<V>(V)> adjs
) {
  std::stack<std::pair<V, V>> s;
  std::unordered_map<V, V> pred;
  s.push(std::make_pair(start, start));
  while (!s.empty()) {
    V t = s.top().first;
    V u = s.top().second;
    s.pop();
    if (pred.count(u)) continue;
    pred[u] = t;
    for (V v : adjs(u)) {
      if (pred.count(v)) continue;
      s.push(std::make_pair(u, v));
    }
  }
  return pred;
}
