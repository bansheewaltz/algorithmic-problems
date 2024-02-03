#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];

  int init = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (a[i] > a[j]) init++;

  ll total = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      // swap(a[i], a[j]);
      ll cur = init;
      for (int k = i + 1; k <= j; k++) {
        if (a[j] > a[k]) cur++;
        if (a[k] > a[i]) cur++;
        if (a[j] < a[k]) cur--;
        if (a[k] < a[i]) cur--;
      }
      total += cur;
      // swap(a[i], a[j]);
    }

  ll npairs = n * (n - 1) / 2;

  ll gcd = std::gcd(total, npairs);
  cout << total / gcd << "/" << npairs / gcd << "\n";
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
