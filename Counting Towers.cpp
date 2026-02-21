// Author: cyberman

// Approach
//
// state:
//     - dp[i][0] = number of ways to create tower of height i with top blocks
//     separate
//     - dp[i][1] = number of ways to create tower of height i with top blocks
//     combined
//
// recurrence:
//     - dp[i][0] = 4 * dp[i-1][0] + dp[i-1][1]
//     - dp[i][1] = 2 * dp[i-1][1] + dp[i-1][0]
//
// base: dp[1][0] = dp[1][1] = 1

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
  int t;
  cin >> t;
  ll n = 1e6;
  vector<vector<ll>> dp(n + 1, vector<ll>(2, 0));
  // 0 = separate blocks
  // 1 = combined block
  dp[1][0] = 1;
  dp[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    dp[i][0] = ((((4 * dp[i - 1][0]) % MOD) + dp[i - 1][1]) % MOD) % MOD;
    dp[i][1] = ((((2 * dp[i - 1][1]) % MOD) + dp[i - 1][0]) % MOD) % MOD;
  }
  for (int i = 0; i < t; i++) {
    int x;
    cin >> x;
    cout << (dp[x][0] + dp[x][1]) % MOD << "\n";
  }
}
