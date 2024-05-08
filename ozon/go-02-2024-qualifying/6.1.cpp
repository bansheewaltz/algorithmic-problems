#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  struct line_info {
    int idx;
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
  };

  int t;

  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<string> table(n);
    for (int i = 0; i < n; i++) {
      string in;
      cin >> in >> ws;
      table[i] = in;
    }

    vector<line_info> rows(n);
    for (int i = 0; i < n; i++) {
      line_info li;
      li.idx = i;
      for (int j = 0; j < m; j++) {
        switch (table[i][j]) {
          case '1': li.one++; break;
          case '2': li.two++; break;
          case '3': li.three++; break;
          case '4': li.four++; break;
        }
      }
      rows[i] = li;
    }

    vector<line_info> cols(m);
    for (int i = 0; i < m; i++) {
      line_info ri;
      ri.idx = i;
      for (int j = 0; j < n; j++) {
        switch (table[j][i]) {
          case '1': ri.one++; break;
          case '2': ri.two++; break;
          case '3': ri.three++; break;
          case '4': ri.four++; break;
        }
      }
      cols[i] = ri;
    }

    auto cmp = [](const line_info &a, const line_info &b) {
      if (a.one && !b.one) return true;
      if (a.one != b.one) return a.one > b.one;
      if (a.two && !b.two) return true;
      if (a.two != b.two) return a.two > b.two;
      if (a.three && !b.three) return true;
      if (a.three != b.three) return a.three > b.three;
      if (a.four && !b.four) return true;
      if (a.four != b.four) return a.four > b.four;
    };
    sort(rows.begin(), rows.end(), cmp);
    int i = rows[0].idx;
    for (int j = 0; j < cols.size(); j++) {
      char num = table[i][j];
      if (num == '1') cols[j].one--;
      if (num == '2') cols[j].two--;
      if (num == '3') cols[j].three--;
      if (num == '4') cols[j].four--;
    }
    sort(cols.begin(), cols.end(), cmp);

    cout << rows[0].idx + 1 << " " << cols[0].idx + 1 << "\n";
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
