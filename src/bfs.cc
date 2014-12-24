/**
 * Breadth-first search
 */

#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

template <class V>
std::unordered_map<V, V> bfs(
    V s,
    std::function<std::vector<V>(V)> adjs
) {
  std::queue<std::pair<V, V>> que;
  std::unordered_map<V, V> pred;
  que.push(std::make_pair(s, s));
  while (!que.empty()) {
    V t = que.front().first;
    V u = que.front().second;
    que.pop();
    if (pred.count(u)) continue;
    pred[u] = t;
    for (V v : adjs(u)) {
      if (pred.count(v)) continue;
      que.push(std::make_pair(u, v));
    }
  }
  return pred;
}
