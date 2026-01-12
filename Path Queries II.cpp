// Author: cyberman
// Algorithm: Heavy Light Decomposition, Segment Trees, Eulers Tour

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<ll>> g;
vector<ll> tin, tout, value, flat, parent, subtree, head, depth;
ll timer = 0;

struct SegmentTree {
  ll n;
  vector<ll> tree;

  SegmentTree(vector<ll> &arr, ll n) : n(n) {
    tree.resize(4 * n + 1);
    build_max(1, 1, n, arr);
  }

  void build_sum(ll ind, ll tl, ll tr, vector<ll> &arr) {
    if (tl == tr) {
      tree[ind] = arr[tl];
      return;
    }
    ll mid = (tl + tr) / 2;
    build_sum(2 * ind, tl, mid, arr);
    build_sum(2 * ind + 1, mid + 1, tr, arr);
    tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
  }

  void build_max(ll ind, ll tl, ll tr, vector<ll> &arr) {
    if (tl == tr) {
      tree[ind] = arr[tl];
      return;
    }
    ll mid = (tl + tr) / 2;
    build_max(2 * ind, tl, mid, arr);
    build_max(2 * ind + 1, mid + 1, tr, arr);
    tree[ind] = max(tree[2 * ind], tree[2 * ind + 1]);
  }

  ll query_sum(ll l, ll r) { return query_sum(1, 1, n, l, r); }

  ll query_max(ll l, ll r) { return query_max(1, 1, n, l, r); }

  ll query_sum(ll ind, ll tl, ll tr, ll l, ll r) {
    if (tr < l || tl > r) {
      return 0;
    }
    if (tl >= l && tr <= r) {
      return tree[ind];
    }
    ll mid = (tl + tr) / 2;
    return query_sum(2 * ind, tl, mid, l, r) +
           query_sum(2 * ind + 1, mid + 1, tr, l, r);
  }

  ll query_max(ll ind, ll tl, ll tr, ll l, ll r) {
    if (tr < l || tl > r) {
      return LLONG_MIN;
    }
    if (tl >= l && tr <= r) {
      return tree[ind];
    }
    ll mid = (tl + tr) / 2;
    return max(query_max(2 * ind, tl, mid, l, r),
               query_max(2 * ind + 1, mid + 1, tr, l, r));
  }

  void update_sum(ll pos, ll val) { update_sum(1, 1, n, pos, val); }

  void update_max(ll pos, ll val) { update_max(1, 1, n, pos, val); }

  void update_sum(ll ind, ll tl, ll tr, ll pos, ll val) {
    if (tl == tr) {
      tree[ind] = val;
      return;
    }
    ll mid = (tl + tr) / 2;
    if (pos <= mid) {
      update_sum(2 * ind, tl, mid, pos, val);
    } else {
      update_sum(2 * ind + 1, mid + 1, tr, pos, val);
    }
    tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
  }

  void update_max(ll ind, ll tl, ll tr, ll pos, ll val) {
    if (tl == tr) {
      tree[ind] = val;
      return;
    }
    ll mid = (tl + tr) / 2;
    if (pos <= mid) {
      update_max(2 * ind, tl, mid, pos, val);
    } else {
      update_max(2 * ind + 1, mid + 1, tr, pos, val);
    }
    tree[ind] = max(tree[2 * ind], tree[2 * ind + 1]);
  }
};

void dfs1(ll u, ll p) {
  parent[u] = p;
  for (ll v : g[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      dfs1(v, u);
      subtree[u] += subtree[v];
    }
  }
}

void dfs2(ll u, ll p) {
  tin[u] = ++timer;
  flat[timer] = value[u];

  ll heavy = -1;
  for (ll v : g[u]) {
    if (v != p && (heavy == -1 || subtree[v] > subtree[heavy])) {
      heavy = v;
    }
  }

  if (heavy != -1) {
    head[heavy] = head[u];
    dfs2(heavy, u);
  }

  for (ll v : g[u]) {
    if (v != p && v != heavy) {
      head[v] = v;
      dfs2(v, u);
    }
  }

  tout[u] = timer;
}

ll query2(ll a, ll b, SegmentTree &st) {
  ll ans = LLONG_MIN;
  while (head[a] != head[b]) {
    if (depth[head[a]] > depth[head[b]]) {
      swap(a, b);
    }
    ans = max(ans, st.query_max(tin[head[b]], tin[b]));
    b = parent[head[b]];
  }
  ans = max(ans, st.query_max(min(tin[a], tin[b]), max(tin[a], tin[b])));
  return ans;
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
  head.resize(n + 1);
  parent.assign(n + 1, 0);
  subtree.assign(n + 1, 1);
  depth.assign(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    cin >> value[i];
  }

  for (int i = 0; i < n - 1; i++) {
    ll a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    head[i] = i;
  }

  dfs1(1, 0);
  dfs2(1, 0);

  SegmentTree st(flat, n);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int u;
      ll x;
      cin >> u >> x;
      value[u] = x;
      st.update_max(tin[u], x);
    } else {
      int a, b;
      cin >> a >> b;
      cout << query2(a, b, st) << " ";
    }
  }

  return 0;
}
