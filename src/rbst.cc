#include <functional>
#include <memory>
#include <random>
#include <utility>

std::default_random_engine rand(std::random_device);

template <class Key, class Value>
class RBST
{
  struct Node;
  using NodePtr     = std::shared_ptr<Node>;
  using NodePtrPair = std::pair<NodePtr, NodePtr>;
  using Compare     = std::function<bool(Key, Key)>;
  struct Node
  {
    size_t s;
    Key k;
    Value v;
    NodePtr l;
    NodePtr r;
    Node(Key k, Value v): s(1), k(k), v(v), l(nullptr), r(nullptr) {}
    Node(const Node& t): s(t.s), k(t.k), v(t.v), l(t.l), r(t.r) {}
    Key key() { return k; }
    Value value() { return v; }
    static size_t size(const NodePtr& t) { return t ? t->s : 0; }
    static const NodePtr& update(const NodePtr& t)
    {
      if (!t) return t;
      t->s = 1 + size(t->l) + size(t->r);
      return t;
    }
    static const NodePtr& propagate(const NodePtr& t)
    {
      if (!t) return t;
      if (t->l) {
        t->l = std::make_shared<Node>(*(t->l));
        update(t->l);
      }
      if (t->r) {
        t->r = std::make_shared<Node>(*(t->r));
        update(t->r);
      }
      return t;
    }
    static NodePtr merge(const NodePtr& l, const NodePtr& r)
    {
      if (!l) return r;
      if (!r) return l;
      if (rand() % (size(l) + size(r)) < size(l)) {
        auto newl = std::make_shared<Node>(*propagate(l));
        newl->r = merge(l->r, r);
        return update(newl);
      } else {
        auto newr = std::make_shared<Node>(*propagate(r));
        newr->l = merge(l, r->l);
        return update(newr);
      }
    }
    static NodePtrPair split(const NodePtr& t, Key k, Compare& compare)
    {
      if (!t) return std::make_pair(nullptr, nullptr);
      auto newt = std::make_shared<Node>(*propagate(t));
      if (compare(k, t->k)) {
        auto lkr = split(t->l, k, compare);
        newt->l = lkr.second;
        return std::make_pair(std::move(lkr.first), std::move(update(newt)));
      } else {
        auto lkr = split(t->r, k, compare);
        newt->r = lkr.first;
        return std::make_pair(std::move(update(newt)), std::move(lkr.second));
      }
    }
    static const NodePtr& find(const NodePtr& t, Key k)
    {
      if (!t) return t;
      if (k < t->k) return find(t->l, k);
      if (k > t->k) return find(t->r, k);
      return t;
    }
  };
  NodePtr root;
  Compare less_equal = std::less_equal<Key>();
  Compare less       = std::less<Key>();
public:
  RBST() {}
  ~RBST() {}
  void insert(Key k, Value v)
  {
    auto lk = Node::split(root, k, less_equal).first;
    auto kr = Node::split(root, k, less).second;
    auto t = std::make_shared<Node>(k, v);
    root = Node::merge(lk, Node::merge(t, kr));
  }
  void erase(Key k)
  {
    auto lk = Node::split(root, k, less_equal).first;
    auto kr = Node::split(root, k, less).second;
    root = Node::merge(lk, kr);
  }
  const NodePtr& find(Key k)
  {
    return Node::find(root, k);
  }
};
