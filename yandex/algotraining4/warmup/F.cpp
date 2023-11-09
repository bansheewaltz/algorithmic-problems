#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve();

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
  cout << "\n";
}

void solve() {
  ll n, k;
  vector<ll> f;
  cin >> k >> n;
  f.resize(n + 1);
  ll last_fl = 0;
  for (ll i = 1; i < n + 1; i++) {
    cin >> f[i];
    if (f[i]) last_fl = i;
  }

  ll time = 0;
  /* start from top */
  ll i = last_fl;
  while (i > 0) {
    ll free = k;
    time += i * 2;
    /* go down and stop while there is a free space */
    while (free && free >= f[i] && i > 0) {
      if (f[i]) {
        free -= f[i];
        f[i] = 0;
      }
      while (!f[i] && i > 0) i--;
    }
    /* go down */
    if (i == 0 || !free) continue;
    /* return several times */
    f[i] -= free;
    ll times = f[i] / k;
    f[i] -= k * times;
    time += i * 2 * times;
    if (!f[i] && i > 0) i--;
  }
  cout << time;
}
