#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

static void solve() {
  int n; cin >> n;
  constexpr int m = 3;
  vector<vector<int>> rows(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    string row; cin >> row;
    for (int j = 0; j < m; ++j) {
      if (row[j] == 'C') rows[i][j] = +1;
      if (row[j] == 'W') rows[i][j] = -1;
      if (row[j] == '.') rows[i][j] = 0;
    }
  }

  vector<vector<int>> dp(n, vector<int>(m, -1));
  dp[0] = rows[0];
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int dj = -1; dj <= 1; ++dj) {
        if (j + dj < 0 || j + dj >= m) 
          continue;
        if (dp[i - 1][j + dj] != -1 && rows[i][j] != -1)
          dp[i][j] = max(dp[i][j], dp[i - 1][j + dj] + rows[i][j]);
      }
    }
  }
  
  int max = 0;
  for (auto& vec : dp)
    for (int num : vec)
      max = ::max(max, num);
  cout << max << endl;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
