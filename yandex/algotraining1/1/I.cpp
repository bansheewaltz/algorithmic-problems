#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int a[3];
  int d, e;
  cin >> a[0] >> a[1] >> a[2] >> d >> e;

  sort(a, a + 3);
  int l = a[0];
  int m = a[1];

  multiset<int> sizes = {d, e};
  auto lb = sizes.lower_bound(l);
  if (lb != sizes.end()) sizes.erase(lb);
  auto mb = sizes.lower_bound(m);
  cout << (lb != sizes.end() && mb != sizes.end() ? "YES\n" : "NO\n");
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
