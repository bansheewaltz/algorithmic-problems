#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> iv;
  for (int t, i = 0; i < n; i++) {
    cin >> t;
    iv.push_back(t);
  }

  sort(iv.begin(), iv.end());
  iv.erase(unique(iv.begin(), iv.end()), iv.end());

  int beg = 0;
  int end = 0;

  while (beg < iv.size()) {
    while (end + 1 < iv.size() && iv[end] + 1 == iv[end + 1]) {
      ++end;
    }

    cout << iv[beg];
    if (end > beg + 1)
      cout << " ... " << iv[end];
    else if (end == beg + 1)
      cout << " " << iv[end];
    if (end != iv.size() - 1) cout << " ";

    ++end;
    beg = end;
  }
  cout << endl;
}

int main() {
#ifdef LOCAL_TESTING
  cout << unitbuf;
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
}
