#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
  int n;
  cin >> n;
  double h[n];
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }

  double avg = 0;
  for (int i = 1; i < n; i++) {
    avg += (h[i] + h[i - 1]) / 2;
  }

  cout << std::setprecision(16) << avg / (n - 1) << endl;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
}
