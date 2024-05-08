#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

struct line_info {
  int one = 0;
  int two = 0;
  int three = 0;
  int four = 0;
};

auto cmp = [](const line_info &a, const line_info &b) {
  if (a.one != b.one) return a.one > b.one;
  if (a.two != b.two) return a.two > b.two;
  if (a.three != b.three) return a.three > b.three;
  if (a.four != b.four) return a.four > b.four;
  return false;
};

int find_col(const vector<string> &table, int n, int m, int ignore) {
  int c = 0;
  line_info wc;
  for (int i = 0; i < m; i++) {
    line_info cur;
    for (int j = 0; j < n; j++) {
      if (j == ignore) continue;
      switch (table[j][i]) {
        case '1': cur.one++; break;
        case '2': cur.two++; break;
        case '3': cur.three++; break;
        case '4': cur.four++; break;
      }
    }
    if (cmp(cur, wc)) wc = cur, c = i;
  }
  return c;
}

int find_row(const vector<string> &table, int n, int m, int ignore) {
  int r = 0;
  line_info w;
  for (int i = 0; i < n; i++) {
    line_info cur;
    for (int j = 0; j < m; j++) {
      if (j == ignore) continue;
      switch (table[i][j]) {
        case '1': cur.one++; break;
        case '2': cur.two++; break;
        case '3': cur.three++; break;
        case '4': cur.four++; break;
      }
    }
    if (cmp(cur, w)) w = cur, r = i;
  }
  return r;
}

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m >> ws;

    vector<string> table(n);
    for (int i = 0; i < n; i++) getline(cin, table[i]);

    int r, c;
    if (n >= m) {
      c = find_col(table, n, m, -1);
      r = find_row(table, n, m, c);
    } else {
      r = find_row(table, n, m, -1);
      c = find_col(table, n, m, r);
    }

    cout << r + 1 << " " << c + 1 << "\n";
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
