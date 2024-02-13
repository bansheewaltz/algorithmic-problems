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
  int a, b, c;
  cin >> a >> b >> c;

  if (c < 0) {
    cout << "NO SOLUTION" << endl;
    return 0;
  }
  if (c * c - b == 0 && a == 0) {
    cout << "MANY SOLUTIONS" << endl;
    return 0;
  }
  if (a == 0) {
    cout << "NO SOLUTION" << endl;
    return 0;
  }

  double x = (double)(c * c - b) / a;
  if (abs(x - round(x)) > 1e-6)
    cout << "NO SOLUTION";
  else
    cout << int(x);
  cout << endl;
}
