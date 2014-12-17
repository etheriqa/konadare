#include <functional>
#include <memory>
#include <random>
#include <utility>

std::default_random_engine rand(std::random_device);

template <class Key, class Value>
class RBST
{
  struct Node;
  using NodePtr = std::shared_ptr<Node>;
  using NodePtrPair = std::pair<NodePtr, NodePtr>;
  using Compare = std::function<bool(Key, Key)>;
  struct Node
  {
    size_t size_;
    Key key_;
    Value value_;
    NodePtr left_;
    NodePtr right_;
    Node(Key k, Value v)
      : size_(1),
        key_(k),
        value_(v) {}
    Node(const Node& t)
      : size_(t.size_),
        key_(t.key_),
        value_(t.value_),
        left_(t.left_),
        right_(t.right_) {}
    static size_t size(const NodePtr& t)
    {
      return t ? t->size_ : 0;
    }
    static NodePtr copy(const NodePtr& t)
    {
      return t ? std::make_shared<Node>(*t) : t;
    }
    static const NodePtr& update(const NodePtr& t)
    {
      if (!t) return t;
      t->size_ = 1 + size(t->left_) + size(t->right_);
      return t;
    }
    static NodePtr merge(const NodePtr& l, const NodePtr& r)
    {
      if (!update(l)) return r;
      if (!update(r)) return l;

      if (rand() % (size(l) + size(r)) < size(l)) {
        auto newl = copy(l);
        newl->right_ = merge(newl->right_, r);
        return update(newl);
      } else {
        auto newr = copy(r);
        newr->left_ = merge(l, newr->left_);
        return update(newr);
      }
    }
    static NodePtrPair split(const NodePtr& t, Key k, const Compare& compare)
    {
      if (!update(t)) return std::make_pair(t, t);

      auto newt = copy(t);
      if (compare(k, newt->key_)) {
        auto lr = split(newt->left_, k, compare);
        newt->left_ = lr.second;
        return std::make_pair(lr.first, update(newt));
      } else {
        auto lr = split(newt->right_, k, compare);
        newt->right_ = lr.first;
        return std::make_pair(update(newt), lr.second);
      }
    }
    static const NodePtr& find(const NodePtr& t, Key k)
    {
      if (!update(t)) return t;

      if (k < t->key_) return find(t->left_, k);
      if (k > t->key_) return find(t->right_, k);
      return t;
    }
public:
    Key key() { return key_; }
    Value value() { return value_; }
  };
  NodePtr root;
  Compare less_equal = std::less_equal<Key>();
  Compare less       = std::less<Key>();
public:
  RBST() {}
  ~RBST() {}
  void insert(Key k, Value v)
  {
    auto lkr = Node::split(root, k, less_equal);
    auto kkr = Node::split(lkr.second, k, less);
    auto t = std::make_shared<Node>(k, v);
    root = Node::merge(lkr.first, Node::merge(t, kkr.second));
  }
  void erase(Key k)
  {
    auto lkr = Node::split(root, k, less_equal);
    auto kkr = Node::split(lkr.second, k, less);
    root = Node::merge(lkr.first, kkr.second);
  }
  const NodePtr& find(Key k)
  {
    return Node::find(root, k);
  }
};
