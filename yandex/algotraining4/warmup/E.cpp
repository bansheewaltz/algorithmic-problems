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

int n;
vector<int> rtg;

void solve() {
  cin >> n;
  rtg.resize(n);
  for (int i = 0; i < n; i++)
    cin >> rtg[i];

  vector<int> pref;
  pref.resize(n + 1);
  pref[0] = 0;
  for (int i = 1; i < n + 1; i++)
    pref[i] = pref[i - 1] + rtg[i - 1];
  int max = pref[n];

  for (int i = 0; i < n; i++) {
    int cur = (i * rtg[i] - pref[i]) + (max - pref[i] - (n - i) * rtg[i]);
    cout << cur << " ";
  }
  cout << "\n";
}
