#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, x;
  cin >> n >> x;
  int r = x;  // remains
  int a[n];
  ll as = 0;
  for (int i = 0; i < n; i++) cin >> a[i], as += a[i];

  struct ivpair {
    int idx;
    double val;
  };

  ivpair b[n];
  for (int i = 0; i < n; i++) b[i] = {i, (double)x * a[i] / as};
  sort(b, b + n, [](auto a, auto b) { return a.val > b.val; });

  vector<int> c(n);
  // array alignment
  for (int i = 0; i < n - 1; i++) {
    int t = min(r, (int)floor(b[i].val - b[n - 1].val));
    b[i].val -= t;
    c[b[i].idx] += t;
    r -= t;
    if (!r) break;
  }
  sort(b, b + n, [](auto a, auto b) { return a.val > b.val; });
  // array shift
  if (r) {
    int m = 0;
    while (r - (m + 1) * n > 0) m++;
    for (int i = 0; i < n; i++) {
      b[i].val -= m;
      c[b[i].idx] += m;
      r -= m;
    }
  }
  // finalization
  if (r) {
    for (int i = 0; i < n; i++) {
      b[i].val--;
      c[b[i].idx]++;
      r--;
      if (!r) break;
    }
  }

  ll cs = 0;
  for (int i = 0; i < n; i++) cs += c[i];
  assert(cs == x);

  for (int i = 0; i < n; i++) {
    cout << c[i] << (i != n - 1 ? " " : "\n");
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
