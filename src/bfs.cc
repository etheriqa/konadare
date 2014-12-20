/**
 * Breadth-first search
 */

#include <functional>
#include <queue>
#include <set>
#include <vector>

template <class V>
void bfs(V s, std::function<std::vector<V>(V)> adjs)
{
  std::queue<V> q;
  std::set<V> visited;
  for (q.push(s); !q.empty(); q.pop()) {
    V v = q.front();
    if (visited.count(v)) continue;
    visited.insert(v);
    for (V u : adjs(v)) q.push(u);
  }
}
