#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  int v1 = (a + c) * max(b, d);
  int v2 = (a + d) * max(b, c);
  int v3 = (b + c) * max(a, d);
  int v4 = (b + d) * max(a, c);

  int o = min({v1, v2, v3, v4});
  if (o == v1)
    cout << a + c << " " << max(b, d);
  else if (o == v2)
    cout << a + d << " " << max(b, c);
  else if (o == v3)
    cout << b + c << " " << max(a, d);
  else if (o == v4)
    cout << b + d << " " << max(a, c);
  cout << endl;
}
