#include <bits/stdc++.h>
using namespace std;

static void solve() {
  int n; cin >> n;
  vector<int> a(n); for (int& e : a) cin >> e;

  int five_max = -1;
  for (int i = 6; i < n; ++i) {
    int five_cnt = 0;
    bool has_bad = false;
    for (int j = 0; j < 7; ++j) {
      if (a[i - j] == 5) 
        ++five_cnt;
      if (a[i - j] == 2 || a[i - j] == 3) {
        has_bad = true;
        break;
      }
    }
    if (!has_bad)
      five_max = max(five_max, five_cnt);
  }
  cout << five_max << endl;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
