#include <iostream>
#include <vector>
using namespace std;

int solve() {
  int r, c;
  cin >> r >> c;
  string m;
  cin >> m;

  if (m == "auto") return c;
  if (m == "freeze" && r > c) return c;
  if (m == "heat" && r < c) return c;
  return r;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int res = solve();
  cout << res;
  cout << endl;
}
