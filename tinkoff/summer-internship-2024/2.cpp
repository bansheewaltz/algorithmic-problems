#include <bits/stdc++.h>
using namespace std;

static void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int64_t>> mat(n, vector<int64_t>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) 
      cin >> mat[i][j];

  vector<vector<int64_t>> mat_rot(m, vector<int64_t>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) 
      mat_rot[j][n - 1 - i] = mat[i][j];

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j) 
      cout << mat_rot[i][j] << " \n"[j == n - 1];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
