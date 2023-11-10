#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void solve();

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
  cout << "\n";
}

double xa, ya, xb, yb;

void solve() {
  cin >> xa >> ya >> xb >> yb;

  double ra = sqrt(xa * xa + ya * ya);
  double rb = sqrt(xb * xb + yb * yb);

  double rsm, rbg;
  rsm = min(ra, rb);
  rbg = max(ra, rb);

  double anga = atan2(xa, ya);
  double angb = atan2(xb, yb);
  double angab_1 = abs(anga - angb);
  double angab_2 = 2 * M_PI - angab_1;
  double angab_sm = min(angab_1, angab_2);
  double arc = rsm * angab_sm;

  double arcpath = arc + rbg - rsm;
  double cenpath = ra + rb;
  double shortest = min(arcpath, cenpath);

  cout << fixed << setprecision(12) << shortest;
}
