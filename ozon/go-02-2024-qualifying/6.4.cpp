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

      bool operator==(const line_info &o) {
        for (int i = 1; i < 5; i++)
          if (s[i] != o.s[i]) return false;
        return true;
      }
    };

    auto cmp = [](const line_info &a, const line_info &b) {
      for (int i = 1; i < 5; i++)
        if (a.s[i] != b.s[i]) return a.s[i] > b.s[i];
      return false;
    };

    line_info wr;
    line_info total;
    vector<line_info> rows;
    for (int i = 0; i < n; i++) {
      line_info cur;
      cur.idx = i;
      for (int j = 0; j < m; j++) {
        cur.s[table[i][j] - '0']++;
        total.s[table[i][j] - '0']++;
      }
      if (cmp(cur, wr)) {
        wr = cur;
        rows.clear();
        rows.push_back(cur);
      } else if (cur == wr)
        rows.push_back(cur);
    }

    line_info comb;
    int bi, bj;
    for (int i = 0; i < m; i++) {
      for (int k = 0; k < rows.size(); k++) {
        line_info cur;
        for (int j = 0; j < n; j++) {
          if (rows[k].idx == j) continue;
          cur.s[table[j][i] - '0']++;
        }
        for (int j = 1; j < 5; j++) {
          cur.s[j] += rows[k].s[j];
        }
        if (cmp(cur, comb)) {
          comb = cur;
          bi = rows[k].idx;
          bj = i;
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
