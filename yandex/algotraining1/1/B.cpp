#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solve() {
  int a, b, c;
  cin >> a >> b >> c;
  vector<int> v = {a, b, c};

  sort(v.begin(), v.end());
  if (v[0] + v[1] > v[2])
    cout << "YES";
  else
    cout << "NO";
  return 1;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
  cout << endl;
}
