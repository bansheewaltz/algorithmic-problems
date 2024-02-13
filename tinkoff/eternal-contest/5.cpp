#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

void solve() {
  ull l, r;
  cin >> l >> r;

  vector<ull> a;
  for (int i = 1; i <= 9; i++) {
    for (ull j = 0; j < r;) {
      j = j * 10 + i;
      if (j >= l && j <= r) a.push_back(j);
    }
  }

  cout << a.size() << "\n";
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
