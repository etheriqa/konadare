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
    V start,
    std::function<std::vector<V>(V)> adjs
) {
  std::queue<std::pair<V, V>> q;
  std::unordered_map<V, V> pred;
  q.push(std::make_pair(start, start));
  while (!q.empty()) {
    V t = q.front().first;
    V u = q.front().second;
    q.pop();
    if (pred.count(u)) continue;
    pred[u] = t;
    for (V v : adjs(u)) {
      if (pred.count(v)) continue;
      q.push(std::make_pair(u, v));
    }
  }
  return pred;
}
