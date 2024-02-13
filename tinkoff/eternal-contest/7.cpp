#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int n;
  cin >> n;
  n++;
  int a[n];
  for (int i = 1; i < n; i++) cin >> a[i];

  iv c(n);
  int sc = 0, si = -1;  // self count
  int dc = 0, di = -1;  // duplicate count and index
  for (int i = 1; i < n; i++) {
    if (i == a[i]) {
      sc++, si = i;
      continue;
    }
    c[a[i]]++;
    if (c[i] > 1) dc++, di = i;
  }

  int nc = 0, ni = -1;  // not visited count and index
  for (int i = 1; i < n; i++) {
    if (c[i] == 0) nc++, ni = i;
  }

  if (dc + sc + nc > 2 || !nc) {
    cout << "-1 -1" << endl;
    return;
  } else
    cout << (si == -1 ? di : si) << " " << ni << endl;
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
