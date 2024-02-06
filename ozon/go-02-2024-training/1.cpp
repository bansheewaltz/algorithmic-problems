#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n;
  cin >> n;
  while (n--) {
    int a[4] = {};
    for (int t, i = 0; i < 10; i++) {
      cin >> t;
      a[t - 1]++;
    }
    if (a[0] == 4 && a[1] == 3 && a[2] == 2 && a[3] == 1)
      cout << "YES\n";
    else
      cout << "NO\n";
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
