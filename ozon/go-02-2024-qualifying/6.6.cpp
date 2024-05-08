#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m >> ws;

    vector<string> table(n);
    for (int i = 0; i < n; i++) getline(cin, table[i]);

    struct line_info {
      int idx;
      int s[6] = {};
    };

    auto cmp = [](const line_info &a, const line_info &b) {
      for (int i = 1; i < 5; i++)
        if (a.s[i] != b.s[i]) return a.s[i] > b.s[i];
      return false;
    };

    line_info comb;
    int bi, bj;
    int minr = 5;
    int minc = 5;
    for (int i = 0; i < n; i++) {  // row iter
      int minr_cur = 5;
      for (int j = 0; j < m; j++) {  // row summation
        int val = table[i][j] - '0';
        minr_cur = min(minr_cur, val);
      }
      if (minr_cur < minr) {
        minr = minr_cur;
        bi = i;
        minc = 5;
      }
      if (minr_cur > minr) continue;
      for (int j = 0; j < m; j++) {  // column iter
        int minc_cur = 5;
        for (int k = 0; k < n; k++) {
          if (k == i) continue;
          int val = table[k][j] - '0';
          minc_cur = min(minc_cur, val);
        }
        if (minc_cur < minc) {
          minc = minc_cur;
          bj = j;
        }
      }
    }

    cout << bi + 1 << " " << bj + 1 << "\n";
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
