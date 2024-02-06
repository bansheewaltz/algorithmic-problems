#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int bm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void solve() {
  int t;
  cin >> t;
  int d, m, y;
  for (int i = 0; i < t; i++) {
    bool res = true;
    cin >> d >> m >> y;
    int maxd = bm[m - 1];
    if (d > maxd) res = false;
    if (m == 2 && d == 29) {
      bool isleap = (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
      if (isleap) res = true;
    }
    cout << (res == true ? "YES" : "NO") << "\n";
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
