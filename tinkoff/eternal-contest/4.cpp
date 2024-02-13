#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, k;
  cin >> n >> k;
  int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];

  ll diff = 0;
  vector<int> diffa;
  for (int num : a) {
    for (int i = 1; num != 0; i *= 10) {
      diffa.push_back((9 - num % 10) * i);
      num /= 10;
    }
  }

  sort(diffa.rbegin(), diffa.rend());
  for (int i = 0; i < k && i < diffa.size(); i++) {
    diff += diffa[i];
  }

  cout << diff << "\n";
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
