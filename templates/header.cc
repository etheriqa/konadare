#define inf(T) (numeric_limits<T>::min())
#define sup(T) (numeric_limits<T>::max())
#define rep(i,n) for (int i = 0; i < (n); i++)
#define asc(c) begin(c), end(c)
#define desc(c) reverse_iterator<decltype(c)::iterator>(c.end()), reverse_iterator<decltype(c)::iterator>(c.begin())
#define ascend(l,r) l = max(l, r)
#define descend(l,r) l = min(l, r)
#define mp(...) make_pair(__VA_ARGS__)
#define mt(...) make_tuple(__VA_ARGS__)

using namespace std;

using ll = long long;
using ld = long double;

template <class Key>          using uset = unordered_set<Key>;
template <class Key, class T> using umap = unordered_map<Key, T>;

