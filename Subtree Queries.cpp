#include <bits/stdc++.h>
using namespace std;

// Approach

// First use DFS flatenning using euler touring
// then create a fenwick tree to process update and range sum queries,
// in O(logn) time complexity

typedef long long ll;

vector<vector<ll>> g;
vector<ll> tin, tout;
vector<ll> value, flat;
ll timer = 0;

struct Fenwick {
  ll n;
  vector<ll> bit;

  Fenwick(ll n) : n(n), bit(n + 1, 0) {}

  ll query_sum(ll i) {
    ll s = 0;
    while (i > 0) {
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }

  void update(ll i, ll d) {
    while (i <= n) {
      bit[i] += d;
      i += i & -i;
    }
  }

  ll range_query_sum(ll l, ll r) { return query_sum(r) - query_sum(l - 1); }
};

void dfs(ll u, ll p) {
  tin[u] = ++timer;
  flat[timer] = value[u];
  for (ll v : g[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  tout[u] = timer;
}

void print_arr(vector<ll> a) {
  ll n = a.size();
  for (int i = 0; i < n; i++) {
    cout << a[i] << (i == n - 1 ? "\n" : " ");
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, q;
  cin >> n >> q;

  g.resize(n + 1);
  tin.resize(n + 1);
  tout.resize(n + 1);
  value.resize(n + 1);
  flat.resize(n + 1);

  for (int i = 1; i <= n; i++) {
    cin >> value[i];
  }

  for (int i = 0; i < n - 1; i++) {
    ll a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  dfs(1, 0);

  Fenwick fw(n);
  for (int i = 1; i <= n; i++) {
    fw.update(i, flat[i]);
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int u;
      ll x;
      cin >> u >> x;
      ll delta = x - value[u];
      value[u] = x;
      fw.update(tin[u], delta);
    } else {
      int u;
      cin >> u;
      cout << fw.range_query_sum(tin[u], tout[u]) << "\n";
    }
  }

  //   print_arr(flat);
  //   print_arr(fw.bit);
  //   print_arr(value);
  //   print_arr(tin);
  //   print_arr(tout);

  return 0;
}
