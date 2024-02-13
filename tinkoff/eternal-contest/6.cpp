#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int n;
  cin >> n;
  int a[n + 1];
  for (int i = 1; i < n + 1; i++) cin >> a[i];

  iv w;
  int we = 0, wo = 0;
  for (int i = 1; i < n + 1; i++) {
    if ((i & 1) == 1 && (a[i] & 1) == 0) w.push_back(i), wo++;
    if ((i & 1) == 0 && (a[i] & 1) == 1) w.push_back(i), we++;
  }

  if (we == wo && w.size() == 2)
    cout << w[0] << " " << w[1] << "\n";
  else if (w.empty() && n > 2)
    cout << "1 3" << endl;
  else
    cout << "-1 -1" << endl;
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
