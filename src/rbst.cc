#include <functional>
#include <memory>
#include <random>
#include <utility>

std::default_random_engine rand(std::random_device);

template <class Key>
class RBST
{
  struct Node
  {
    size_t n_nodes = 1;
    Key key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node(Key k) :key(k) {}
    static std::shared_ptr<Node> merge(std::shared_ptr<Node> l, std::shared_ptr<Node> r)
    {
      if (!l) return r;
      if (!r) return l;

      if (rand() % (l->n_nodes + r->n_nodes) < l->n_nodes) {
        l->right = merge(l->right, r);
        return update(l);
      } else {
        r->left = merge(l, r->left);
        return update(r);
      }
    }
    static std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> split(std::shared_ptr<Node> t, Key k, std::function<bool(Key, Key)> compare)
    {
      if (!t) return std::make_pair(nullptr, nullptr);

      if (compare(k, t->key)) {
        auto lr = split(t->left, k, compare);
        t->left = lr.second;
        return std::make_pair(lr.first, update(t));
      } else {
        auto lr = split(t->right, k, compare);
        t->right = lr.first;
        return std::make_pair(update(t), lr.second);
      }
    }
    static std::shared_ptr<Node> update(std::shared_ptr<Node> t)
    {
      t->n_nodes = 1;
      if (t->left) t->n_nodes += t->left->n_nodes;
      if (t->right) t->n_nodes += t->right->n_nodes;
      return t;
    }
    static size_t count(std::shared_ptr<Node> t, Key k)
    {
      if (!t) return 0;

      size_t n = 0;
      if (k == t->key) n++;
      if (k <= t->key) n += count(t->left, k);
      if (k >= t->key) n += count(t->right, k);
      return n;
    }
  };
  std::shared_ptr<Node> root;
public:
  RBST() {}
  ~RBST() {}
  void insert(Key k)
  {
    auto lr = Node::split(root, k, std::less<Key>());
    auto n = std::shared_ptr<Node>(new Node(k));
    root = Node::merge(lr.first, Node::merge(n, lr.second));
  }
  void erase(Key k)
  {
    auto l = Node::split(root, k, std::less_equal<Key>()).first;
    auto r = Node::split(root, k, std::less<Key>()).second;
    root = Node::merge(l, r);
  }
  size_t count(Key k)
  {
    return Node::count(root, k);
  }
};
