#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int solve(int n, int a, int b);

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n, a, b;
    cin >> n >> a >> b;
    int res = solve(n, a, b);
    cout << (res ? "YES" : "NO");
    cout << std::endl;
  }
}

int solve(int n, int a, int b) {
  // if (n != 1 && 2 * a > n) return 0;
  if (n > a && n > b && n < 2 * a) return 0;
  if (a == b && n % a != 0) return 0;
  int rem = n % a;
  int quot = n / a;
  if (rem + a <= b)
    return 1;
  else if (rem * (a + 1) + a * (quot - rem) == n)
    return 1;
  else
    return 0;
}
