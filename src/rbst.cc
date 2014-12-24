/**
 * Persistent randomized binary search tree (with lazy propagation)
 */

#include <random>
#include <utility>

template <class T>
class RBST
{
  using size_type   = size_t;
  struct Node;
  using NodePtr     = Node*;
  using NodePtrPair = std::pair<NodePtr, NodePtr>;

  struct Node
  {
    const size_type size_;
    const T value_;
    const T lazy_;
    const NodePtr left_;
    const NodePtr right_;
    Node(): size_(0), value_(T()), lazy_(T()), left_(nullptr), right_(nullptr) {}
    explicit Node(T value):
      size_(1),
      value_(value),
      lazy_(T()),
      left_(nullptr),
      right_(nullptr) {}
    Node(T value, T lazy, NodePtr left, NodePtr right):
      size_(1 + size(left) + size(right)),
      value_(value),
      lazy_(lazy),
      left_(left),
      right_(right) {}
  };

  const size_type pool_size_;
  const NodePtr pool_;
  size_type pool_offset_;
  NodePtr root_;
  std::default_random_engine engine_;
public:
  explicit RBST(size_type pool_size):
    pool_size_(pool_size),
    pool_(new Node[pool_size]),
    pool_offset_(0),
    root_(nullptr),
    engine_(std::random_device()()) {}
  ~RBST() { delete[] pool_; }
  size_type size() const { return size(root_); }
  T at(size_type pos)
  {
    gc();
    return at(root_, pos);
  }
  void push_back(T value) {
    gc();
    root_ = merge(root_, node(value));
  }
  void add(size_type pos, size_type n, T value)
  {
    gc();
    NodePtrPair p1 = split(root_, pos);
    NodePtrPair p2 = split(p1.second, n);
    NodePtr target = nullptr;
    if (p2.first) {
      target = node(
        p2.first->value_,
        p2.first->lazy_ + value,
        p2.first->left_,
        p2.first->right_
      );
    }
    root_ = merge(p1.first, merge(target, p2.second));
  }
private:
  static size_type size(NodePtr x) { return x ? x->size_ : 0; }
  static T value(NodePtr x) { return x ? x->value_ + x->lazy_ : T(); }
  NodePtr propagate(NodePtr x)
  {
    if (!x) return x;
    if (x->lazy_ == T()) return x;
    NodePtr left = nullptr, right = nullptr;
    if (x->left_) {
      left = node(
        x->left_->value_,
        x->left_->lazy_ + x->lazy_,
        x->left_->left_,
        x->left_->right_
      );
    }
    if (x->right_) {
      right = node(
        x->right_->value_,
        x->right_->lazy_ + x->lazy_,
        x->right_->left_,
        x->right_->right_
      );
    }
    return node(value(x), T(), left, right);
  }
  T at(NodePtr x, size_type pos)
  {
    if (pos >= size(x)) return T();
    if (pos == size(x->left_)) return value(x);
    return pos < size(x->left_)
      ? x->lazy_ + at(x->left_, pos)
      : x->lazy_ + at(x->right_, pos - size(x->left_) - 1);
  }
  NodePtr merge(NodePtr x, NodePtr y)
  {
    x = propagate(x);
    y = propagate(y);
    if (!x) return y;
    if (!y) return x;
    return engine_() % (size(x) + size(y)) < size(x)
      ? node(x->value_, x->lazy_, x->left_, merge(x->right_, y))
      : node(y->value_, y->lazy_, merge(x, y->left_), y->right_);
  }
  NodePtrPair split(NodePtr x, size_type pos)
  {
    x = propagate(x);
    if (!x) return std::make_pair(nullptr, nullptr);
    if (pos == 0) return std::make_pair(nullptr, x);
    if (pos >= size(x)) return std::make_pair(x, nullptr);
    if (pos <= size(x->left_)) {
      NodePtrPair xl = split(x->left_, pos);
      return std::make_pair(xl.first, node(x->value_, x->lazy_, xl.second, x->right_));
    } else {
      NodePtrPair xr = split(x->right_, pos - size(x->left_) - 1);
      return std::make_pair(node(x->value_, x->lazy_, x->left_, xr.first), xr.second);
    }
  }
  template <class... Args>
  NodePtr node(const Args&... args)
  {
    return new(pool_ + pool_offset_++) Node(args...);
  }
  void gc()
  {
    if (pool_offset_ * 16 < pool_size_ * 15) return;
    std::vector<T> xs(size(root_));
    for (size_t i = 0; i < xs.size(); i++) xs[i] = at(root_, i);
    pool_offset_ = 0;
    root_ = nullptr;
    for (size_t i = 0; i < xs.size(); i++) root_ = merge(root_, node(xs[i]));
  }
};
