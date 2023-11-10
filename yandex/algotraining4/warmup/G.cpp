#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void solve();

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
  cout << "\n";
}

void solve() {
  int r, c;
  cin >> r >> c;
  vector<vector<int>> f(r, vector<int>(c));

  int max = 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      cin >> f[i][j];
      if (f[i][j] == 1) max = 1;
    }

  for (int i = 1; i < r; i++) {
    for (int j = 1; j < c; j++) {
      if (f[i][j]) {
        int l = f[i][j - 1];
        int t = f[i - 1][j];
        int d = f[i - 1][j - 1];
        if (l && t && d) {
          f[i][j] = min({l, t, d}) + 1;
          if (f[i][j] > max) max = f[i][j];
        }
      }
    }
  }

  cout << max;
}
