#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  int n;
  cin >> n;
  unordered_set<string> s;
  for (int i = 0; i < n; i++) {
    string n;
    cin >> n >> ws;
    s.insert(n);
    for (int j = 0; j < n.size() - 1; j++) {
      string sn = n;
      swap(sn[j], sn[j + 1]);
      s.insert(sn);
    }
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    string n;
    cin >> n >> ws;
    cout << (s.find(n) != s.end() ? 1 : 0) << "\n";
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
