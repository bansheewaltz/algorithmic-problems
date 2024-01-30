#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

double eval(double x, double y) {
  double r = sqrt(x * x + y * y);
  if (r <= 0.1) return 3;
  if (0.1 < r && r <= 0.8) return 2;
  if (0.8 < r && r <= 1.0) return 1;
  return 0;
}

void solve() {
  double res = 0;
  double x, y;
  for (int i = 0; i < 3; i++) {
    cin >> x >> y;
    res += eval(x, y);
  }
  cout << res << endl;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
}
