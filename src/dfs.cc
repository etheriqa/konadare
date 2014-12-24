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
    V s,
    std::function<std::vector<V>(V)> adjs
) {
  std::stack<std::pair<V, V>> sta;
  std::unordered_map<V, V> pred;
  sta.push(std::make_pair(s, s));
  while (!sta.empty()) {
    V t = sta.top().first;
    V u = sta.top().second;
    sta.pop();
    if (pred.count(u)) continue;
    pred[u] = t;
    for (V v : adjs(u)) {
      if (pred.count(v)) continue;
      sta.push(std::make_pair(u, v));
    }
  }
  return pred;
}
