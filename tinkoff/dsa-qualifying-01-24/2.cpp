#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
  int n;
  string s;
  cin >> n >> s;

  int min = INT_MAX;
  int max = 0;
  int cur = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] != '#') ++cur;
    if (s[i] == '#' || i == n - 1) {
      if (cur > max) max = cur;
      if (cur < min) min = cur;
      cur = 0;
    }
  }
  if (min == 0 && s.find("##") == string::npos) min = max;
  cout << min << " " << max << endl;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
}
