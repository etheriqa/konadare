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
    size_type size_;
    T value_;
    NodePtr left_;
    NodePtr right_;
    Node() {}
    explicit Node(T v): size_(1), value_(v), left_(nullptr), right_(nullptr) {}
    Node(const Node& r): size_(r.size_), value_(r.value_), left_(r.left_), right_(r.right_) {}
  };

  size_type pool_size_;
  size_type pool_offset_;
  NodePtr pool_;
  NodePtr root_;
  std::default_random_engine engine_;
public:
  explicit RBST(size_type pool_size):
    pool_size_(pool_size),
    pool_offset_(0),
    pool_(new Node[pool_size]),
    root_(nullptr),
    engine_(std::random_device()()) {}
  ~RBST() { delete[] pool_; }
  size_type size() const { return size(root_); }
  T at(size_type pos) { return at(root_, pos); }
  void push_back(T v) { gc(); root_ = merge(root_, node(v)); }
private:
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
    for (size_t i = 0; i < xs.size(); i++) push_back(xs[i]);
  }
  size_type size(const NodePtr& x) const { return x ? x->size_ : 0; }
  T at(const NodePtr& x, size_type pos)
  {
    propagate(x);
    if (pos >= size(x)) return T();
    if (pos == size(x->left_)) return x->value_;
    return pos < size(x->left_)
      ? at(x->left_, pos)
      : at(x->right_, pos - size(x->left_) - 1);
  }
  const NodePtr& update(const NodePtr& x) const
  {
    if (!x) return x;
    x->size_ = 1 + size(x->left_) + size(x->right_);
    return x;
  }
  const NodePtr& propagate(const NodePtr& x)
  {
    if (!x) return x;
    if (true) return x;
    if (x->left_) {
      x->left_ = node(*x->left_);
      update(x->left_);
    }
    if (x->right_) {
      x->right_ = node(*x->right_);
      update(x->right_);
    }
    return update(x);
  }
  NodePtr merge(const NodePtr& x, const NodePtr& y)
  {
    if (!propagate(x)) return y;
    if (!propagate(y)) return x;
    if (engine_() % (size(x) + size(y)) < size(x)) {
      NodePtr newx = node(*x);
      newx->right_ = merge(x->right_, y);
      return update(newx);
    } else {
      NodePtr newy = node(*y);
      newy->left_ = merge(x, y->left_);
      return update(newy);
    }
  }
  NodePtrPair split(const NodePtr& x, size_type pos)
  {
    if (!propagate(x)) return std::make_pair(nullptr, nullptr);
    if (pos == 0) return std::make_pair(nullptr, x);
    if (pos >= size(x)) return std::make_pair(x, nullptr);
    NodePtr newx = node(*x);
    if (pos <= size(x->left_)) {
      NodePtrPair xl = split(x->left_, pos);
      newx->left_ = xl.second;
      return std::make_pair(xl.first, update(newx));
    } else {
      NodePtrPair xr = split(x->right_, pos - size(x->left_) - 1);
      newx->right_ = xr.first;
      return std::make_pair(update(newx), xr.second);
    }
  }
};
