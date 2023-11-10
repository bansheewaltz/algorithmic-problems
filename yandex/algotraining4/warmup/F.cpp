#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
// #define int uint64_t;
void solve();

int32_t main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
  cout << "\n";
}

void solve() {
  uint64_t n, k;
  vector<uint64_t> f;
  cin >> k >> n;
  f.resize(n + 1);
  uint64_t last_fl = 0;
  for (uint64_t i = 1; i < n + 1; i++) {
    cin >> f[i];
    if (f[i]) last_fl = i;
  }

  uint64_t time = 0;
  uint64_t free = k;
  for (uint64_t i = last_fl; i > 0; i--) {
    while (!f[i] && i > 1) i--;
    if (free == k) time += i * 2;
    if (f[i] > free) {
      f[i] -= free;
      uint64_t reps = f[i] / k;
      if (f[i] - reps * k) reps++;
      time += reps * i * 2;
      free = k - f[i] % k;
    } else {
      free -= f[i];
    }
    f[i] = 0;
  }
  cout << time;
}
