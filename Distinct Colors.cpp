// Author: cyberman
// Algorithm: Fenwick tree

// Approach

// Flatten the tree using Eulers tour
// We maintain the occurence of the right most occurence of colors
// since any other occurence will also include the right most occurence
// ending with range r, formally any segment [l, r] must contain i, if l <= i <=
// r we sort the subtree ranges [l, r] by r and use fenwick tree to calculate
// the sum on bit where bit[i] = 1 for last occurence of a color, and make the
// prev occurence 0 if any

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll timer = 0;
vector<ll> tin, flat, st, cols;
vector<vector<ll>> g;

struct Query {
  ll l, r, id;
};

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

  void update(ll i, ll d) {
    while (i <= n) {
      bit[i] += d;
      i += i & -i;
    }
  }

  ll range_sum(ll l, ll r) { return sum(r) - sum(l - 1); }
};

void dfs(ll u, ll p) {
  tin[u] = ++timer;
  flat[timer] = cols[u];
  ll s = 1;
  for (ll adj : g[u]) {
    if (adj != p) {
      dfs(adj, u);
      s += st[adj];
    }
  }
  st[u] = s;
}

int main() {
  ll n;
  cin >> n;

  tin.resize(n + 1);
  flat.resize(n + 1);
  cols.resize(n + 1);
  st.resize(n + 1);

  for (int i = 1; i <= n; i++) {
    cin >> cols[i];
  }

  g.resize(n + 1);
  for (int i = 1; i < n; i++) {
    ll a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  dfs(1, 0);

  vector<Query> q(n);

  for (int i = 1; i <= n; i++) {
    q[i - 1] = {tin[i], tin[i] + st[i] - 1, i};
  }

  sort(q.begin(), q.end(),
       [](const Query &a, const Query &b) { return a.r < b.r; });

  Fenwick fw(n);
  unordered_map<ll, ll> last;

  ll qptr = 0;
  vector<ll> ans(n + 1);

  for (int i = 1; i <= n; i++) {
    ll c = flat[i];
    if (last.count(c)) {
      fw.update(last[c], -1);
    }

    last[c] = i;
    fw.update(i, 1);

    while (qptr < n && q[qptr].r == i) {
      ans[q[qptr].id] = fw.range_sum(q[qptr].l, q[qptr].r);
      qptr++;
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << (i == n ? "\n" : " ");
  }
}
