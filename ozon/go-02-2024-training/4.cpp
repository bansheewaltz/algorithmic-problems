#include <bits/stdc++.h>
using namespace std;
// using ll = long long;

const int ll = 15, rl = 30;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int l = ll, r = rl;
    bool error = false;
    while (n--) {
      string boundary;
      int num;
      cin >> boundary >> num;
      int res = 0;
      if (boundary == ">=") {
        if (l < num) l = num;
        if (num > r) error = true;
      } else {
        if (num < r) r = num;
        if (num < l) error = true;
      }
      if (error) res = -1;
      if (!error) res = l;
      cout << res << "\n";
    }
    if (t) cout << "\n";
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
