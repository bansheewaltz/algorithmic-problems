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

  double xsm, xbg, ysm, ybg, rsm, rbg;

  ra < rb ? rsm = ra : rsm = rb;
  ra > rb ? rbg = ra : rbg = rb;

  double anga = atan2(xa, ya);
  double angb = atan2(xb, yb);

  double angab_1 = abs(anga - angb);
  double angab_2 = 2 * M_PI - angab_1;
  double angab_sm = angab_1 < angab_2 ? angab_1 : angab_2;
  double arc = rsm * angab_sm;

  double arcpath = arc + rbg - rsm;
  double cenpath = ra + rb;
  double shortest = arcpath < cenpath ? arcpath : cenpath;

  cout << fixed << setprecision(12) << shortest;
}
