#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    stringstream ss;
    int len = 0;
    int lastc = 0;
    int i = 0;
    for (; i < n - 1; i++) {
      int start = a[i];
      int c = 0;
      if (!c && a[i + 1] - 1 == a[i])
        while (i + 1 < n && a[i + 1] - 1 == a[i]) c++, i++;
      if (!c && a[i + 1] + 1 == a[i])
        while (i + 1 < n && a[i + 1] + 1 == a[i]) c--, i++;
      ss << start << " " << c << (i == n - 1 && c ? "" : " ");
      len += 2;
      lastc = c;
    }
    if (!lastc || i != n) {
      len += 2;
      ss << a[n - 1] << " " << 0;
    }
    cout << len << "\n";
    cout << ss.str() << "\n";
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
