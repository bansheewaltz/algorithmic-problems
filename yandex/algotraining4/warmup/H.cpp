#include <cmath>
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
}

int a, b, n;

void solve() {
  cin >> a;
  cin >> b;
  cin >> n;

  if (a > b || a > ceil((float)b / n)) {
    cout << "Yes\n";
    return;
  }
  cout << "No\n";
}
