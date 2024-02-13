#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int n, k, m;
  cin >> n >> k >> m;
  int kc = 0;
  int remn = n;
  int remk = k;
  int remt = n;
  int c = 0;
  while (remt > k) {
    kc = n / k;
    remn = n - kc * k;
    c += k / m;
    remk = k - c * m;
    remt = remk * kc + remn;
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
