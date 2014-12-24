/**
 * Dijkstra's algorithm
 */

#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

template <class V, class W>
std::unordered_map<V, V> dijkstra(
    V s,
    std::function<std::vector<V>(V)> adjs,
    std::function<W(V, V)> weight
) {
  using item_t = std::tuple<W, V, V>;
  std::priority_queue<item_t, std::vector<item_t>, std::greater<item_t>> pq;
  std::unordered_map<V, V> pred;
  for (pq.push(std::make_tuple(W(), s, s)); !pq.empty(); pq.pop()) {
    W w = std::get<0>(pq.top());
    V t = std::get<1>(pq.top());
    V u = std::get<2>(pq.top());
    if (pred.count(u)) continue;
    pred[u] = t;
    for (V v : adjs(u)) {
      if (pred.count(v)) continue;
      pq.push(std::make_tuple(w + weight(u, v), u, v));
    }
  }
  return pred;
}
