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

    int l = 5;
    line_info total;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        total.s[table[i][j] - '0']++;
        if (table[i][j] - '0' < l) l = table[i][j] - '0';
      }
    }

    int kills = 0;
    int bi, bj;
    for (int i = 0; i < n; i++) {  // row iter
      line_info row;
      for (int j = 0; j < m; j++) {  // row summation
        row.s[table[i][j] - '0']++;
      }
      for (int j = 0; j < m; j++) {  // column iter
        line_info rowcol = row;
        for (int k = 0; k < n; k++) {
          if (k == i) continue;
          rowcol.s[table[k][j] - '0']++;
        }
        vector<int> killed(6);
        for (int k = 1; k < 5; k++) {
          if (total.s[k] && total.s[k] - rowcol.s[k] == 0) killed[k]++;
        }
        int curkills = 0;
        for (int k = l; k < 5; k++) {
          if (!killed[l]) break;
          if ((k == l || killed[k - 1] == 1) && killed[k] == 1) curkills++;
        }
        if (curkills > kills) {
          kills = curkills;
          bi = i;
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
