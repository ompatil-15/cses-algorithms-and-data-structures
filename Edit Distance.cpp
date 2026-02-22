// Author: cyberman

// Approach
//
// state: dp[i][j] = number of operations required to match first i letter from
// s and first j letters from t
// recurrece:
//     - Add: dp[i][j] = 1 + dp[i][j-1]
//     - Remove: dp[i][j] = 1 + dp[i-1][j]
//     - Update: dp[i][j] = 1 + dp[i-1][j-1]
// base:
//     dp[i >= 0][0] = i
//     dp[0][j >= 0] = j

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  string s, t;
  getline(cin, s);
  getline(cin, t);

  int n = s.size();
  int m = t.size();
  vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));

  // base case
  for (int i = 0; i <= n; i++) {
    dp[i][0] = i;
  }
  for (int i = 0; i <= m; i++) {
    dp[0][i] = i;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i - 1] == t[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
      }
    }
  }

  cout << dp[n][m] << endl;
}
