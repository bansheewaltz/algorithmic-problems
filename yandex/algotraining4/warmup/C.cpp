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

  ra < rb ? xsm = xa, ysm = ya, rsm = ra : (xsm = xb, ysm = yb, rsm = rb);
  ra > rb ? xbg = xa, ybg = ya, rbg = ra : (xbg = xb, ybg = yb, rbg = rb);

  double sc = rsm / rbg;
  double xarc = xbg * sc;
  double yarc = ybg * sc;

  double d;
  if (ra == rb)
    d = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
  else
    d = sqrt((xarc - xsm) * (xarc - xsm) + (yarc - ysm) * (yarc - ysm));

  double arc = rsm * acos(1 - (d * d) / (2 * rsm * rsm));
  double arcpath = arc + rbg - rsm;
  double cenpath = ra + rb;
  double shortest = arcpath < cenpath ? arcpath : cenpath;

  cout << fixed << setprecision(12) << shortest;
}
