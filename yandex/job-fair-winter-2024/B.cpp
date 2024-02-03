#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, t, s;
  cin >> n >> t >> s;
  int v1;
  cin >> v1;

  ll l1 = (ll)v1 * t / s;
  ll r1 = (ll)v1 * t % s;
  ll ot = 0;  // overtakes count
  for (int i = 1; i < n; i++) {
    int v;
    cin >> v;
    if (v >= v1) continue;
    ll l = (ll)v * t / s;
    ll r = (ll)v * t % s;
    ot += l1 - l;
    if (r1 <= r) ot--;
  }

  cout << ot << "\n";
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
