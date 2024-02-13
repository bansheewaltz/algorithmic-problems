#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  const double eps = 1e-4;
  double x, y;
  cin >> x >> y;

  struct point {
    double x, y;
  };

  point a[4];
  double l = FLT_MAX, r = -FLT_MAX, t = -FLT_MAX, b = FLT_MAX;
  for (int i = 0; i < 4; i++) {
    point p;
    cin >> p.x >> p.y;
    if (p.x < l) l = p.x;
    if (p.x > r) r = p.x;
    if (p.y < b) b = p.y;
    if (p.y > t) t = p.y;
    a[i] = p;
  }
  point o2 = a[0];
  point bx = a[1];
  point by = a[3];

  auto dist = [](point p0, point p1) { return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2)); };
  auto center = [](double a, double b) { return (a + b) / 2; };

  double scale = dist(a[0], a[1]) / dist({0, 0}, {x, 0});
  double angle = atan2(bx.y - o2.y, bx.x - o2.x);

  double yc = center(l, r);
  while (r - l > eps) {
    double xc = center(l, r);
    double xlq = center(l, xc);
    double xrq = center(r, xc);
    point o2xlq = {xlq - o2.x, yc - o2.y};
    point o2xrq = {xrq - o2.x, yc - o2.y};
    double al = atan2(o2xlq.x, o2xlq.y) - angle;
    double ar = atan2(o2xrq.x, o2xrq.y) - angle;
    double newxlq = dist(o2, {xlq, yc}) * cos(al) / scale;
    double newxrq = dist(o2, {xrq, yc}) * cos(ar) / scale;
    double xldist = abs(newxlq - xlq);
    double xrdist = abs(newxrq - xrq);
    if (xldist < xrdist) r = xc;
    if (xrdist < xldist) l = xc;
  }
  double fx = l;  // found x
  while (t - b > eps) {
    double yc = center(b, t);
    double ybq = center(b, yc);
    double ytq = center(t, yc);
    point o2ybq = {fx - o2.x, ybq - o2.y};
    point o2ytq = {fx - o2.x, ytq - o2.y};
    double at = atan2(o2ytq.y, o2ytq.x) - angle;
    double ab = atan2(o2ybq.y, o2ybq.x) - angle;
    double newybq = dist(o2, {fx, ybq}) * sin(ab) / scale;
    double newytq = dist(o2, {fx, ytq}) * sin(at) / scale;
    double ybdist = abs(newybq - ybq);
    double ytdist = abs(newytq - ytq);
    if (ybdist < ytdist) t = yc;
    if (ytdist < ybdist) b = yc;
  }
  cout << l << " " << b << endl;
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
