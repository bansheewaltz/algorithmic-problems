#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;
using ll = long long;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, p;
    cin >> n >> p;

    ll total = 0;
    for (int i = 0; i < n; i++) {
      ll a;
      cin >> a;
      ll k = a * p;
      ll r = a * p / 100;
      total += k - r * 100;
    }

    cout << fixed << setprecision(2) << double(total) / 100 << "\n";
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
