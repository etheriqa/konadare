#if defined(__GNUG__) && !defined(__clang__)
#include <bits/stdc++.h>
#endif

#define inf(T) (numeric_limits<T>::min())
#define sup(T) (numeric_limits<T>::max())
#define range(c) (c).begin(), (c).end()
#define mp(...) make_pair(__VA_ARGS__)
#define mt(...) make_tuple(__VA_ARGS__)

using namespace std;

using ll = long long;
using ld = long double;

template <class Key>          using uset = unordered_set<Key>;
template <class Key, class T> using umap = unordered_map<Key, T>;

