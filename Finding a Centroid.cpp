// Author: cyberman
// Algorithm: DFS traversal

// Approach
//
// Calculate the subtree of each node
// Node u with children v and rest = n - sz[u] is the centroid if
// max(all sz[v], rest) <= n/2

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> sz;
vector<vector<ll>> graph;

void dfs1(ll u, ll p) {
  sz[u] = 1;
  for (ll adj : graph[u]) {
    if (adj != p) {
      dfs1(adj, u);
      sz[u] += sz[adj];
    }
  }
}

ll dfs2(ll u, ll p, ll n) {
  ll max_child = 0;

  for (ll adj : graph[u]) {
    if (adj != p) {
      max_child = max(max_child, sz[adj]);
    }
  }

  max_child = max(max_child, n - sz[u]);

  if (max_child <= n / 2) {
    return u;
  }

  for (ll adj : graph[u]) {
    if (adj != p && sz[adj] > n / 2) {
      return dfs2(adj, u, n);
    }
  }

  return u;
}

int main() {
  ll n;
  cin >> n;

  sz.resize(n + 1);
  graph.resize(n + 1);

  for (int i = 0; i < n - 1; i++) {
    ll a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  dfs1(1, 0);
  ll ans = dfs2(1, 0, n);

  cout << ans << endl;
}
