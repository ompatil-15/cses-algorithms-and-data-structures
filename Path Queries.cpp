// Author: cyberman
// Algorithm: Tree flatenning, Fenwick tree storing difference array

// Approach

// Flatten the tree with tin and tout, Subtree(u) → [tin[u], tout[u]]
// Node u is the ancestor of s, if tin[u] ≤ tin[s] ≤ tout[u]
// The path sum to s is the sum of all values, whose subtree includes tin[s]

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<ll>> g;
vector<ll> tin, tout;
vector<ll> value, flat;
ll timer = 0;

struct Fenwick {
  ll n;
  vector<ll> bit;

  Fenwick(ll n) : n(n), bit(n + 1, 0) {}

  ll sum(ll i) {
    ll s = 0;
    while (i > 0) {
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }

  void add(ll i, ll d) {
    while (i <= n) {
      bit[i] += d;
      i += i & -i;
    }
  }

  ll range_sum(ll l, ll r) { return sum(r) - sum(l - 1); }
};

void dfs(ll u, ll p) {
  tin[u] = ++timer;
  for (ll v : g[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  tout[u] = timer;
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
    fw.add(tin[i], value[i]);
    fw.add(tout[i] + 1, -value[i]);
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
      fw.add(tin[u], delta);
      fw.add(tout[u] + 1, -delta);
    } else {
      int u;
      cin >> u;
      cout << fw.sum(tin[u]) << "\n";
    }
  }

  return 0;
}
