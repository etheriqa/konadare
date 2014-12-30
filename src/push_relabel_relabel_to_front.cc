/**
 * Push-relabel algorithm with relabel-to-front selection rule
 */

#include <algorithm>
#include <list>
#include <memory>
#include <unordered_map>

template <class V, class Flow>
class PushRelabel
{
  using size_type     = std::size_t;
  struct Vertex;
  using VertexPtr     = std::shared_ptr<Vertex>;
  using VertexWeakPtr = std::weak_ptr<Vertex>;
  struct Edge;
  using EdgePtr       = std::shared_ptr<Edge>;
  using EdgeWeakPtr   = std::weak_ptr<Edge>;

  struct Vertex
  {
    V u;
    size_type height;
    Flow excess_flow;
    std::list<EdgePtr> edges;
    Vertex(V u)
      : u(u),
        height(0),
        excess_flow(Flow()),
        edges()
    {}
  };

  struct Edge
  {
    VertexWeakPtr u;
    VertexWeakPtr v;
    Flow capacity;
    Flow preflow;
    Edge(VertexWeakPtr u, VertexWeakPtr v, Flow capacity)
      : u(u),
        v(v),
        capacity(capacity),
        preflow(Flow())
    {}
  };

  std::unordered_map<V, VertexPtr> vertices_;
public:
  PushRelabel() {}
  void addVertex(V u)
  {
    vertices_[u] = std::make_shared<Vertex>(u);
  }
  void addEdge(V u, V v, Flow capacity)
  {
    EdgePtr edge = std::make_shared<Edge>(vertices_[u], vertices_[v], capacity);
    vertices_[u]->edges.push_back(edge);
    vertices_[v]->edges.push_back(edge);
  }
  Flow findMaxFlow(V source, V sink)
  {
    VertexPtr& s = vertices_[source];
    VertexPtr& t = vertices_[sink];
    s->height = vertices_.size();
    for (EdgePtr& e : s->edges) {
      if (!isEdge(s, e)) continue;
      e->preflow = e->capacity;
      e->v.lock()->excess_flow = e->capacity;
      s->excess_flow -= e->capacity;
    }

    std::list<VertexPtr> us;
    for (auto& kv : vertices_) {
      if (kv.first != source && kv.first != sink) {
        us.push_back(kv.second);
      }
    }

    auto it = us.begin();
    while (it != us.end()) {
      VertexPtr& u = *it;
      size_type height = u->height;
      discharge(u);
      if (u->height > height) {
        us.push_front(u);
        us.erase(it);
        it = us.begin();
      }
      it++;
    }

    return t->excess_flow;
  }
private:
  static bool isEdge(const VertexPtr& u, const EdgePtr& e)
  {
    return u->u == e->u.lock()->u;
  }
  static bool isResidualEdge(const VertexPtr& u, const EdgePtr& e)
  {
    return residualCapacity(u, e) > Flow();
  }
  static Flow residualCapacity(const VertexPtr& u, const EdgePtr& e)
  {
    return isEdge(u, e) ? e->capacity - e->preflow : e->preflow;
  }
  static VertexPtr neighborVertex(const VertexPtr& u, const EdgePtr& e)
  {
    return (isEdge(u, e) ? e->v : e->u).lock();
  }
  void discharge(const VertexPtr& u)
  {
    auto it = u->edges.begin();
    while (u->excess_flow > Flow()) {
      if (it == u->edges.end()) {
        relabel(u);
        it = u->edges.begin();
        continue;
      }

      EdgePtr& e = *it;
      VertexPtr v = neighborVertex(u, e);
      if (isResidualEdge(u, e) && u->height == v->height + 1) {
        push(u, e);
      }

      it++;
    }
  }
  void push(const VertexPtr& u, const EdgePtr& e)
  {
    Flow delta = std::min(u->excess_flow, residualCapacity(u, e));
    VertexPtr v = neighborVertex(u, e);
    e->preflow += isEdge(u, e) ? delta : -delta;
    u->excess_flow -= delta;
    v->excess_flow += delta;
  }
  void relabel(const VertexPtr& u)
  {
    size_type min_adj_height = u->height;
    for (auto& e : u->edges) {
      if (!isResidualEdge(u, e)) continue;
      min_adj_height = std::min(min_adj_height, e->v.lock()->height);
    }
    u->height = 1 + min_adj_height;
  }
};
