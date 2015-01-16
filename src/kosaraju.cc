/**
 * Kosaraju's algorithm (using an adjacency list)
 */

#include <algorithm>
#include <functional>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

template <class V>
class Kosaraju
{
  using size_type = std::size_t;
  using Vertex    = std::vector<V>;
  using Edge      = std::unordered_map<V, Vertex>;
  using PredTree  = std::unordered_map<V, V>;
  using SCC       = std::vector<Vertex>;

  Vertex vertices_;
  Edge edges_;
  Edge rev_edges_;
public:
  Kosaraju() {}
  void addVertex(V v)
  {
    vertices_.push_back(v);
    edges_[v] = {};
    rev_edges_[v] = {};
  }
  void addEdge(V from, V to)
  {
    edges_[from].push_back(to);
    rev_edges_[to].push_back(from);
  }
  SCC findSCC()
  {
    SCC scc;
    Vertex first, second;
    {
      PredTree pt;
      for (V v : vertices_) {
        if (pt.count(v)) continue;
        pt[v] = v;
        dfs(v, edges_, pt, first);
      }
    }
    std::reverse(first.begin(), first.end());
    {
      PredTree pt;
      for (V v : first) {
        if (pt.count(v)) continue;
        pt[v] = v;
        dfs(v, rev_edges_, pt, second);
        scc.push_back(std::move(second));
        second.clear();
      }
    }
    return scc;
  }
private:
  void dfs(V u, const Edge& edges, PredTree& pt, std::vector<V>& visited)
  {
    for (auto v : edges.at(u)) {
      if (pt.count(v)) continue;
      pt[v] = u;
      dfs(v, edges, pt, visited);
    }
    visited.push_back(u);
  }
};
