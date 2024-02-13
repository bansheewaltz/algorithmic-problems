#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m >> ws;
    vector<string> a(n);
    for (int i = 0; i < n; i++) getline(cin, a[i]);

    struct bot {
      int i, j;
      char l, p;
    };

    vector<bot> bv;

    char fl, fp, sl, sp;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char ch = a[i][j];
        if (ch == 'A' || ch == 'B') {
          bv.push_back({i, j, ch, (ch == 'A' ? 'a' : 'b')});
        }
      }
      if (bv.size() == 2) break;
    }
    sort(bv.begin(), bv.end(), [](bot a, bot b) {
      if (a.i + a.j == b.i + b.j) return a.i < b.i;
      return a.i + a.j < b.i + b.j;
    });

    bot f = bv[0];
    while (a[0][0] != f.p && a[0][0] != f.l) {
      while (f.i > 0 && a[f.i - 1][f.j] == '.') f.i--, a[f.i][f.j] = f.p;
      while (f.j > 0 && a[f.i][f.j - 1] == '.') f.j--, a[f.i][f.j] = f.p;
    }
    bot s = bv[1];
    int li = n - 1;
    int lj = m - 1;
    while (a[li][lj] != s.p && a[li][lj] != s.l) {
      while (s.i < li && a[s.i + 1][s.j] == '.') s.i++, a[s.i][s.j] = s.p;
      while (s.j < lj && a[s.i][s.j + 1] == '.') s.j++, a[s.i][s.j] = s.p;
    }

    for (int i = 0; i < n; i++) {
      cout << a[i] << "\n";
    }
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
