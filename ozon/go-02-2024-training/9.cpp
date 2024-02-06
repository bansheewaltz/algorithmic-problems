#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    string in;
    iv buf(m, -1);
    iv nd;
    for (int i = 0; i < n; i++) {
      cin >> in;
      for (int j = 0; j < m - 1; j++) {
        while (in[j] == '.') j++;
        if (j < m - 1 && in[j] == '*' && in[j + 1] == '*') {
          int e = j;
          while (in[e + 1] == '*') e++;
          if ((j == 0 && e == m - 1 && buf[j] == -1) ||  // full line
              (j > 0 && buf[j] == buf[j - 1]) ||         // left leaning line
              (e < m - 1 && buf[j] == buf[e + 1]))       // right leaning line
            while (in[j] == '*') buf[j]++, j++;
          else {
            nd.push_back(buf[j]);
            while (in[j] == '*') buf[j]--, j++;
          }
        }
      }
    }
    sort(nd.begin(), nd.end());
    for (int depth : nd) cout << depth << " ";
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
