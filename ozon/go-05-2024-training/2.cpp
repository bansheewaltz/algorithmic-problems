#include <bits/stdc++.h>
using namespace std;

static void solve() {
  string sticker; cin >> sticker;
  int t; cin >> t;
  while (t--) {
    int a, b; cin >> a >> b;
    string newsticker; cin >> newsticker;
    for (int i = a - 1; i <= b - 1; ++i)
      sticker[i] = newsticker[i - a + 1];
  }
  cout << sticker;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
